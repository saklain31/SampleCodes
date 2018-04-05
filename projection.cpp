#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265

void inception();
void drawline(int xa, int ya, int xb , int yb);
void drawCube();
int degree=0,degree2=0,degree3=0;
//int line1[4], line2[4], line3[4], line4[4];
int x1,x2,yone,y2;

float cubeX[]={-100.0,100.0,100.0,-100.0,-100.0,100.0,100.0,-100.0};
float cubeY[]={100.0,100.0,-100.0,-100.0,100.0,100.0,-100.0,-100.0};
float initX[]={-100.0,100.0,100.0,-100.0,-100.0,100.0,100.0,-100.0};
float initY[]={100.0,100.0,-100.0,-100.0,100.0,100.0,-100.0,-100.0};
float z1=100.0, z2=-100.0;
float d=-500.0;
void restore()
{
	for(int i=0;i<8;i++)
	{
		cubeX[i]=initX[i];
		cubeY[i]=initY[i];
	}
}



void restoreX()
{
	for(int i=0;i<8;i++)
	{
		cubeX[i]=initX[i];
	}	
}
void restoreY()
{
	for(int i=0;i<8;i++)
	{
		cubeY[i]=initY[i];
	}	
}
void translate()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for(int i=0;i<4;i++)
	{
		cubeX[i]= cubeX[i]*1.0/(1+(z1*1.0/d*1.0));
		cubeY[i]= cubeY[i]*1.0/(1+(z1*1.0/d*1.0));
	}
	for(int i=4;i<8;i++)
	{
		cubeX[i]= cubeX[i]*1.0/(1+(z2*1.0/d*1.0));
		cubeY[i]= cubeY[i]*1.0/(1+(z2*1.0/d*1.0));
	}
	drawCube();
}

void drawCube()
{
	drawline((int)cubeX[0],(int)cubeY[0],(int)cubeX[1],(int)cubeY[1]);
	drawline((int)cubeX[1],(int)cubeY[1],(int)cubeX[2],(int)cubeY[2]);
	drawline((int)cubeX[2],(int)cubeY[2],(int)cubeX[3],(int)cubeY[3]);
	drawline((int)cubeX[3],(int)cubeY[3],(int)cubeX[0],(int)cubeY[0]);
	drawline((int)cubeX[4],(int)cubeY[4],(int)cubeX[5],(int)cubeY[5]);
	drawline((int)cubeX[5],(int)cubeY[5],(int)cubeX[6],(int)cubeY[6]);
	drawline((int)cubeX[6],(int)cubeY[6],(int)cubeX[7],(int)cubeY[7]);
	drawline((int)cubeX[7],(int)cubeY[7],(int)cubeX[4],(int)cubeY[4]);
	drawline((int)cubeX[0],(int)cubeY[0],(int)cubeX[4],(int)cubeY[4]);
	drawline((int)cubeX[1],(int)cubeY[1],(int)cubeX[5],(int)cubeY[5]);
	drawline((int)cubeX[3],(int)cubeY[3],(int)cubeX[7],(int)cubeY[7]);
	drawline((int)cubeX[2],(int)cubeY[2],(int)cubeX[6],(int)cubeY[6]);
	for(int i=0;i<8;i++)
	{
		printf("x y = %f %f\n", cubeX[i],cubeY[i]);
	}
}



int findZone()
{
	int dx = x2-x1;
	int dy=y2-yone;
	if(dx>=0 && dy>=0)
	{
		if(dx>dy) return 0;
		else return 1;
	}
	else if(dx>=0 && dy<0)
	{
		if(abs(dx)>abs(dy)) return 7;
		else return 6;
	}
	else if(dx<0 && dy<0)
	{
		if(abs(dx)>abs(dy)) return 4;
		else return 5;
	}
	else
	{
		if(abs(dx)>abs(dy)) return 3;
		else return 2;
	}
}

void drawpoint(int x,int y)
{
	glBegin(GL_POINTS);
	//printf("x,y = %d %d\n",x,y );
	glVertex2i(x,y);
	glEnd();
}

void drawline0(int zone)
{
	
	int dx = x2-x1;
	int dy = y2-yone;
	int d = 2*dy - dx;
	int dE = 2*dy;
	int dNE = 2 * (dy-dx);

	int x=x1, y=yone;
	//drawpoint(x,y);
	while(x<x2)
	{
		if(d<0) //East
		{
			x++;
			d +=dE;
		}
		else //North-East
		{
			x++;
			y++;
			d+=dNE;
		}
		if(zone==0)
		{	
			drawpoint(x,y); //printf("%d %d\n",x,y );
		}
		else if(zone==1)
		{
			drawpoint(y,x); //printf("%d %d\n",y,x );
		}
		else if(zone==2)
		{
			drawpoint(-y,x); //printf("%d %d\n",-y,x );
		}
		else if(zone==3)
		{	
			drawpoint(-x,y); //printf("%d %d\n",-x,y );
		}
		else if(zone==4)
		{	
			drawpoint(-x,-y); //printf("%d %d\n",-x,-y );
		}
		else if(zone==5)
		{	
			drawpoint(-y,-x); //printf("%d %d\n",-y,-x );
		}
		else if(zone==6)
		{	
			drawpoint(y,-x); //printf("%d %d\n",y,-x );
		}
		else if(zone==7)
		{	
			drawpoint(x,-y); //printf("%d %d\n",x,-y );
		}
	}
}

void draw(void)
{

 	int zone = findZone();

	glBegin(GL_POINTS);
	
	glEnd();
	int temp1,temp2;
	if(zone==0)
	{
		printf("zone=%d\n",0 );
		glVertex2i(x1,yone);
		//glColor3f(0.9,0.7,0.6);
		drawline0(zone);
	}
	else if(zone==1)
	{
		printf("zone=%d\n",1 );
		glVertex2i(x1,yone);
		//glColor3f(0.4,0.3,0.1);
		
		temp1=x1;
		x1=yone;
		yone=temp1;

		temp1=x2;
		x2=y2;
		y2=temp1;		

		drawline0(zone);
	}
	else if(zone==2)
	{
		printf("zone=%d\n",2 );
		glVertex2i(x1,yone);
		//glColor3f(0.5,0.8,0.1);

		temp1=x1;
		x1=yone;
		yone= -temp1;

		temp1=x2;
		x2=y2;
		y2= -temp1;		
		drawline0(zone);
	}
	else if(zone==3)
	{
		printf("zone=%d\n",3 );
		glVertex2i(x1,yone);
		//glColor3f(0.4,0.3,0.7);
		
		x1=-x1;
		x2=-x2;

		drawline0(zone);
	}
	else if(zone==4)
	{
		printf("zone=%d\n",4 );
		glVertex2i(x1,yone);
		//glColor3f(0.6,0.5,0.9);	
		
		x1=-x1;
		yone=-yone;
		x2=-x2;
		y2=-y2;

		drawline0(zone);
	}
	else if(zone==5)
	{
		printf("zone=%d\n",5 );
		glVertex2i(x1,yone);
		//glColor3f(0.9,0.3,0.2);

		temp1=x1;
		x1=-yone;
		yone=-temp1;

		temp1=x2;
		x2=-y2;
		y2=-temp1;		

		drawline0(zone);
	}
	else if(zone==6)
	{
	
		printf("zone=%d\n",6 );
		glVertex2i(x1,yone);
		//glColor3f(0.1,0.1,0.2);

		temp1=x1;
		x1=-yone;
		yone=temp1;

		temp1=x2;
		x2=-y2;
		y2=temp1;

		drawline0(zone);
	}
	else if(zone==7)
	{
		printf("zone=%d\n",7 );
		glVertex2i(x1,yone);
		//glColor3f(0.1,0.3,0.8);
		
		yone=-yone;
		y2=-y2;

		drawline0(zone);
	}

	glFlush();
}
/*
void drawAxis()
{
	glColor3f(0.9,0.7,0.6);
	drawline(0,200,0,-200);
	drawline(200,0,-200,0);
	glColor3f(1,0.5,0.1);
}
*/
void drawline(int xa, int ya, int xb , int yb)
{
	int temp1=x1, temp2=x2, temp3=yone, temp4=y2;
	x1=xa, yone=ya, x2=xb, y2=yb;
	draw();
	x1=temp1, x2=temp2, yone=temp3, y2=temp4;
}

void inception()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glFlush();

	translate();
    /*drawAxis();
	drawline(p1,p2,p1,p4);
	drawline(p1,p2,p3,p2);
	drawline(p3,p2,p3,p4);
	drawline(p3,p4,p1,p4);
	*/
	//drawRandom();
}

void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200,200,-200,200);
}

void d_plus()
{
	restore();
	d+=2;
	printf("d=%f\n",d );
	translate();
}
void d_minus()
{
	restore();
	d-=2;
	printf("d=%f\n",d );
	translate();
}
/*
void x_plus()
{	
	//restoreY();
	for(int i=0;i<8;i++)
	{
		cubeX[i]+=1;
	}
	translate();
}
void x_minus()
{
	//restoreY();
	for(int i=0;i<8;i++)
	{
		cubeX[i]-=1;
	}
	translate();	
}
*/

void helperY(int xa, int ya, int xb, int yb)
{
	float sine = sin((degree2*PI*1.0)/(180*1.0));
    float cosine = cos((degree2*PI*1.0)/(180*1.0));
  
	float x11= xa*cosine;
	float y11= ya;
	float x22= xb*cosine;
	float y22= yb;

	drawline((int)x11,(int)y11,(int)x22,(int)y22);
	

}

void rotateY()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glFlush();

    //drawAxis();
    helperY((int)cubeX[0],(int)cubeY[0],(int)cubeX[1],(int)cubeY[1]);
	helperY((int)cubeX[1],(int)cubeY[1],(int)cubeX[2],(int)cubeY[2]);
	helperY((int)cubeX[2],(int)cubeY[2],(int)cubeX[3],(int)cubeY[3]);
	helperY((int)cubeX[3],(int)cubeY[3],(int)cubeX[0],(int)cubeY[0]);
	helperY((int)cubeX[4],(int)cubeY[4],(int)cubeX[5],(int)cubeY[5]);
	helperY((int)cubeX[5],(int)cubeY[5],(int)cubeX[6],(int)cubeY[6]);
	helperY((int)cubeX[6],(int)cubeY[6],(int)cubeX[7],(int)cubeY[7]);
	helperY((int)cubeX[7],(int)cubeY[7],(int)cubeX[4],(int)cubeY[4]);
	helperY((int)cubeX[0],(int)cubeY[0],(int)cubeX[4],(int)cubeY[4]);
	helperY((int)cubeX[1],(int)cubeY[1],(int)cubeX[5],(int)cubeY[5]);
	helperY((int)cubeX[3],(int)cubeY[3],(int)cubeX[7],(int)cubeY[7]);
	helperY((int)cubeX[2],(int)cubeY[2],(int)cubeX[6],(int)cubeY[6]);
	degree2++;

}
void helperX(int xa, int ya, int xb, int yb)
{
	float sine = sin((degree3*PI*1.0)/(180*1.0));
    float cosine = cos((degree3*PI*1.0)/(180*1.0));
  
	float x11= xa;
	float y11= ya*cosine;
	float x22= xb;
	float y22= yb*cosine;

	drawline((int)x11,(int)y11,(int)x22,(int)y22);
	

}

void rotateX()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();

    //drawAxis();
    helperX((int)cubeX[0],(int)cubeY[0],(int)cubeX[1],(int)cubeY[1]);
	helperX((int)cubeX[1],(int)cubeY[1],(int)cubeX[2],(int)cubeY[2]);
	helperX((int)cubeX[2],(int)cubeY[2],(int)cubeX[3],(int)cubeY[3]);
	helperX((int)cubeX[3],(int)cubeY[3],(int)cubeX[0],(int)cubeY[0]);
	helperX((int)cubeX[4],(int)cubeY[4],(int)cubeX[5],(int)cubeY[5]);
	helperX((int)cubeX[5],(int)cubeY[5],(int)cubeX[6],(int)cubeY[6]);
	helperX((int)cubeX[6],(int)cubeY[6],(int)cubeX[7],(int)cubeY[7]);
	helperX((int)cubeX[7],(int)cubeY[7],(int)cubeX[4],(int)cubeY[4]);
	helperX((int)cubeX[0],(int)cubeY[0],(int)cubeX[4],(int)cubeY[4]);
	helperX((int)cubeX[1],(int)cubeY[1],(int)cubeX[5],(int)cubeY[5]);
	helperX((int)cubeX[3],(int)cubeY[3],(int)cubeX[7],(int)cubeY[7]);
	helperX((int)cubeX[2],(int)cubeY[2],(int)cubeX[6],(int)cubeY[6]);
	degree3++;

}

void process_Normal_Keys(int key, int x, int y) 
{
     switch (key) 
    {    
       case 27 :      break;
       case 100 : printf("GLUT_KEY_LEFT %d\n",key); rotateX();  break;
       case 102 : printf("GLUT_KEY_RIGHT %d\n",key); rotateY() ;  break;
       case 101 : printf("GLUT_KEY_UP %d\n",key); d_minus() ;  break;
       case 103 : printf("GLUT_KEY_DOWN %d\n",key); d_plus();  break;
    }

}


int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2, (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	glutInitWindowSize(640,480);
	glutCreateWindow ("Rotate Algo");
	init();
	glutDisplayFunc(inception);
	glutSpecialFunc( process_Normal_Keys );
	glutMainLoop();

	return 0;
}




		