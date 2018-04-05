#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265

void ClipAndDraw();
void clipWindow();
void clip();
void drawline(int xa, int ya, int xb , int yb);
int line1[4], line2[4], line3[4], line4[4];
float x11,y11,x22,y22;

int x1,x2,yone,y2;
float teL,teB,teR,teT;
int degree=1;
//float xe1,xe2,ye1,ye2,xl1,xl2,yl1,yl2;
float tmax=-100, tmin=100;

float enter, leave;

float xmin=-150, xmax=150, ymin=-100, ymax=100;

//float eL, eR, eT, eB;

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
void drawAxis()
{
	drawline(0,200,0,-200);
	drawline(200,0,-200,0);
}

void drawline(int xa, int ya, int xb , int yb)
{
	int temp1=x1, temp2=x2, temp3=yone, temp4=y2;
	x1=xa, yone=ya, x2=xb, y2=yb;
	draw();
	x1=temp1, x2=temp2, yone=temp3, y2=temp4;
}

void clipWindow()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();

    line1[0]= 75,line1[1]= 50, line1[2]= 75,line1[3]= -50 ;
    line2[0]= 75,line2[1]= 50, line2[2]= -75,line2[3]= 50 ;
    line3[0]= -75,line3[1]= 50, line3[2]= -75,line3[3]= -50 ;
    line4[0]= -75,line4[1]= -50, line4[2]= 75,line4[3]= -50;

    drawAxis();
	drawline(line1[0],line1[1],line1[2],line1[3]);
	drawline(line2[0],line2[1],line2[2],line2[3]);
	drawline(line3[0],line3[1],line3[2],line3[3]);
	drawline(line4[0],line4[1],line4[2],line4[3]);
	
	//drawRandom();
}

void helperLeft(int xa, int ya, int xb, int yb)
{
	float sine = sin((degree*PI*1.0)/(180*1.0));
    float cosine = cos((degree*PI*1.0)/(180*1.0));

	x11= xa*cosine - ya*sine;
	y11= ya*cosine + xa*sine;
	x22= xb*cosine - yb*sine;
	y22= yb*cosine + xb*sine;

	drawline((int)x11,(int)y11,(int)x22,(int)y22);
	


}

void rotateLeft()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();

    drawAxis();
    helperLeft(line1[0],line1[1],line1[2],line1[3]);
    line1[0]=x11,line1[1]=y11,line1[2]=x22,line1[3]=y22;
	helperLeft(line2[0],line2[1],line2[2],line2[3]);
	line2[0]=x11,line2[1]=y11,line2[2]=x22,line2[3]=y22;
	helperLeft(line3[0],line3[1],line3[2],line3[3]);
	line3[0]=x11,line3[1]=y11,line3[2]=x22,line3[3]=y22;
	helperLeft(line4[0],line4[1],line4[2],line4[3]);
	line4[0]=x11,line4[1]=y11,line4[2]=x22,line4[3]=y22;
	//degree++;

}


void helperRight(int xa, int ya, int xb, int yb)
{
	float sine = sin((degree*PI*1.0)/(180*1.0));
    float cosine = cos((degree*PI*1.0)/(180*1.0));

	x11= xa*cosine - ya*sine;
	y11= ya*cosine + xa*sine;
	x22= xb*cosine - yb*sine;
	y22= yb*cosine + xb*sine;

	drawline((int)x11,(int)y11,(int)x22,(int)y22);
	

}

void rotateRight()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();

    drawAxis();
    helperRight(line1[0],line1[1],line1[2],line1[3]);
    line1[0]=x11,line1[1]=y11,line1[2]=x22,line1[3]=y22;
	helperRight(line2[0],line2[1],line2[2],line2[3]);
	line2[0]=x11,line2[1]=y11,line2[2]=x22,line2[3]=y22;
	helperRight(line3[0],line3[1],line3[2],line3[3]);
	line3[0]=x11,line3[1]=y11,line3[2]=x22,line3[3]=y22;
	helperRight(line4[0],line4[1],line4[2],line4[3]);
	line4[0]=x11,line4[1]=y11,line4[2]=x22,line4[3]=y22;
	//degree--;

}
void helperY(int xa, int ya, int xb, int yb)
{
	float sine = sin((degree*PI*1.0)/(180*1.0));
    float cosine = cos((degree*PI*1.0)/(180*1.0));
  
	x11= xa*cosine;
	y11= ya;
	x22= xb*cosine;
	y22= yb;

	drawline((int)x11,(int)y11,(int)x22,(int)y22);
	

}

void rotateY()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();

    drawAxis();
    helperY(line1[0],line1[1],line1[2],line1[3]);
    line1[0]=x11,line1[1]=y11,line1[2]=x22,line1[3]=y22;
	helperY(line2[0],line2[1],line2[2],line2[3]);
	line2[0]=x11,line2[1]=y11,line2[2]=x22,line2[3]=y22;
	helperY(line3[0],line3[1],line3[2],line3[3]);
	line3[0]=x11,line3[1]=y11,line3[2]=x22,line3[3]=y22;
	helperY(line4[0],line4[1],line4[2],line4[3]);
	line4[0]=x11,line4[1]=y11,line4[2]=x22,line4[3]=y22;
	//degree++;

}

void helperX(int xa, int ya, int xb, int yb)
{
	float sine = sin((degree*PI*1.0)/(180*1.0));
    float cosine = cos((degree*PI*1.0)/(180*1.0));
  
	x11= xa;
	y11= ya*cosine;
	x22= xb;
	y22= yb*cosine;

	drawline((int)x11,(int)y11,(int)x22,(int)y22);
	

}

void rotateX()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();

    drawAxis();
    helperX(line1[0],line1[1],line1[2],line1[3]);
    line1[0]=x11,line1[1]=y11,line1[2]=x22,line1[3]=y22;
	helperX(line2[0],line2[1],line2[2],line2[3]);
	line2[0]=x11,line2[1]=y11,line2[2]=x22,line2[3]=y22;
	helperX(line3[0],line3[1],line3[2],line3[3]);
	line3[0]=x11,line3[1]=y11,line3[2]=x22,line3[3]=y22;
	helperX(line4[0],line4[1],line4[2],line4[3]);
	line4[0]=x11,line4[1]=y11,line4[2]=x22,line4[3]=y22;
	//degree++;

}
void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200,200,-200,200);
}

void process_Normal_Keys(int key, int x, int y) 
{
     switch (key) 
    {    
       case 27 :      break;
       case 100 : printf("GLUT_KEY_LEFT %d\n",key); rotateLeft();  break;
       case 102: printf("GLUT_KEY_RIGHT %d\n",key); rotateRight() ;  break;
       case 101   : printf("GLUT_KEY_UP %d\n",key); rotateX() ;  break;
       case 103 : printf("GLUT_KEY_DOWN %d\n",key);  rotateY();  break;
    }

}


int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (840, 640);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Rotate Algo");
	init();
	glutDisplayFunc(clipWindow);
	glutSpecialFunc( process_Normal_Keys );
	glutMainLoop();

	return 0;
}




		