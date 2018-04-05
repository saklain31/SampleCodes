#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265

void inception();
void drawline(int xa, int ya, int xb , int yb);
void drawFigure();
int degree=0,degree2=0,degree3=0;
int edge[6000][10];
//int line1[4], line2[4], line3[4], line4[4];
int x1,x2,yone,y2;
int n=0,m=0;
float X[6000],Y[6000],Z[6000];
float initX[6000];
float initY[6000];
float initZ[6000];

float d=2500.0,l=1500.0;
void restore()
{
	for(int i=0;i<8;i++)
	{
		X[i]=initX[i];
		Y[i]=initY[i];
	}
}



void restoreX()
{
	for(int i=0;i<8;i++)
	{
		X[i]=initX[i];
	}	
}
void restoreY()
{
	for(int i=0;i<8;i++)
	{
		Y[i]=initY[i];
	}	
}
void translate()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for(int i=0;i<n;i++)
	{
		X[i]=X[i]*1.0/(1+((Z[i]+l)*1.0/d*1.0));
		Y[i]=Y[i]*1.0/(1+((Z[i]+l)*1.0/d*1.0));
		
	}

	drawFigure();
}

void drawFigure()
{
	int k=0;
	for(int i=0; i<m;i++)
	{
		for(k=1;k<edge[i][0];k++)
		{
			drawline((int)X[edge[i][k]],(int)Y[edge[i][k]],(int)X[edge[i][k+1]],(int)Y[edge[i][k+1]]);
		}
		drawline((int)X[edge[i][k+1]],(int)Y[edge[i][k+1]],(int)X[edge[i][0]],(int)Y[edge[i][0]]);
		
	}
	for(int i=0; i<m;i++)
	{
		for(k=1;k<edge[i][0];k++)
		{
			//drawline((int)X[edge[i][k]],(int)Y[edge[i][k]],(int)X[edge[i][k+1]],(int)Y[edge[i][k+1]]);
			X[edge[i][k]]=initX[edge[i][k]];
			Y[edge[i][k]]=initY[edge[i][k]];
			X[edge[i][k+1]]=initX[edge[i][k+1]];
			Y[edge[i][k+1]]=initY[edge[i][k+1]];
		}
		//drawline((int)X[edge[i][k+1]],(int)Y[edge[i][k+1]],(int)X[edge[i][0]],(int)Y[edge[i][0]]);
		X[edge[i][k+1]]=initX[edge[i][k+1]];
		Y[edge[i][k+1]]=initY[edge[i][k+1]];
		X[edge[i][0]]=initX[edge[i][0]];
		Y[edge[i][0]]=initY[edge[i][0]];
	}
	glFlush();
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
	glColor3f(1.0,1.0,1.0);
	//printf("x,y = %d %d\n",x,y );
	glVertex2i((int)x,(int)y);
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
			drawpoint(x,y); ////printf("%d %d\n",x,y );
		}
		else if(zone==1)
		{
			drawpoint(y,x); ////printf("%d %d\n",y,x );
		}
		else if(zone==2)
		{
			drawpoint(-y,x); ////printf("%d %d\n",-y,x );
		}
		else if(zone==3)
		{	
			drawpoint(-x,y); ////printf("%d %d\n",-x,y );
		}
		else if(zone==4)
		{	
			drawpoint(-x,-y); ////printf("%d %d\n",-x,-y );
		}
		else if(zone==5)
		{	
			drawpoint(-y,-x); ////printf("%d %d\n",-y,-x );
		}
		else if(zone==6)
		{	
			drawpoint(y,-x); ////printf("%d %d\n",y,-x );
		}
		else if(zone==7)
		{	
			drawpoint(x,-y); ////printf("%d %d\n",x,-y );
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
		//printf("zone=%d\n",0 );
		glVertex2i(x1,yone);
		//glColor3f(0.9,0.7,0.6);
		drawline0(zone);
	}
	else if(zone==1)
	{
		//printf("zone=%d\n",1 );
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
		//printf("zone=%d\n",2 );
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
		//printf("zone=%d\n",3 );
		glVertex2i(x1,yone);
		//glColor3f(0.4,0.3,0.7);
		
		x1=-x1;
		x2=-x2;

		drawline0(zone);
	}
	else if(zone==4)
	{
		//printf("zone=%d\n",4 );
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
		//printf("zone=%d\n",5 );
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
	
		//printf("zone=%d\n",6 );
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
		//printf("zone=%d\n",7 );
		glVertex2i(x1,yone);
		//glColor3f(0.1,0.3,0.8);
		
		yone=-yone;
		y2=-y2;

		drawline0(zone);
	}

	//glFlush();
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
	//printf("%d %d %d %d\n",xa,ya,xb,yb);
	int temp1=x1, temp2=x2, temp3=yone, temp4=y2;
	x1=xa, yone=ya, x2=xb, y2=yb;
	draw();
	x1=temp1, x2=temp2, yone=temp3, y2=temp4;
}

void inception()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();
    int t;
    FILE *fp;
    //scanf("%d",&t);
    //if(t==1)
		fp = fopen("cow.ply", "r");
	

	int cnt=0;
	
	//scanf("%d %d",&n,&m);
	//n=1335,m=2452;
	n=2903,m=5804;
	for(int i=0;i<n;i++)
	{
		fscanf(fp,"%f %f %f",&X[i],&Y[i],&Z[i]);
		X[i]*=200;
		Y[i]*=200;
		Z[i]*=200;

		initX[i]=X[i];
		initY[i]=Y[i];
		initZ[i]=Z[i];
	}
	for(int i=0;i<m;i++)
	{
		fscanf(fp,"%d %d %d %d",&edge[i][0],&edge[i][1],&edge[i][2],&edge[i][3]);
	}

	for(int i=0;i<m;i++)
	{
		//printf("%d %d %d %d\n",edge[i][0],edge[i][1],edge[i][2],edge[i][3]);
	}

	//drawline(10,-10,200,200);
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
	gluOrtho2D(-1200,1200,-1200,1200);
}
/*
void d_plus()
{
	restore();
	d+=2;
	//printf("d=%f\n",d );
	translate();
}
void d_minus()
{
	restore();
	d-=2;
	//printf("d=%f\n",d );
	translate();
}

void x_plus()
{	
	//restoreY();
	for(int i=0;i<8;i++)
	{
		X[i]+=1;
	}
	translate();
}
void x_minus()
{
	//restoreY();
	for(int i=0;i<8;i++)
	{
		X[i]-=1;
	}
	translate();	
}
*/
void helperZ(int a, int b)
{
	float sine = sin((degree3*PI*1.0)/(180*1.0));
    float cosine = cos((degree3*PI*1.0)/(180*1.0));
  
	 X[a] =  initX[a]*cosine + initY[a]*(-1.0*sine);
	 Y[a] =  initX[a]*sine + initY[a]*cosine;

	 X[b] =  initX[b]*cosine + initY[b]*(-1.0*sine);
	 Y[b] =  initX[b]*sine + initY[b]*cosine;
	 

	 X[a]=X[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 Y[a]=Y[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 X[b]=X[b]*1.0/(1+((Z[b]+l)*1.0/d*1.0));
	 Y[b]=Y[b]*1.0/(1+((Z[b]+l)*1.0/d*1.0));

	drawline((int) X[a],(int) Y[a],(int) X[b],(int) Y[b]);

	 X[a]=initX[a];
	 Y[a]=initY[a];
	 Z[a]=initZ[a];

	 X[b]=initX[b];
	 Y[b]=initY[b];
	 Z[b]=initZ[b];

	//printf("eikhane\n");
	

}

void rotateZ()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    

    //drawAxis();
	int k=0;
	for(int i=0; i<m;i++)
	{
		for(k=1;k<edge[i][0];k++)
		{
			helperZ(edge[i][k],edge[i][k+1]);
		}
		helperZ(edge[i][k+1],edge[i][0]);
	}
	glFlush();
	degree3--;

}
void helperY(int a, int b)
{
	float sine = sin((degree2*PI*1.0)/(180*1.0));
    float cosine = cos((degree2*PI*1.0)/(180*1.0));
  
	 X[a] =  initX[a]*cosine +  initZ[a]*sine;
	 Y[a] =  initY[a];
	 Z[a] =  initX[a]*(-1.0*sine) +  initZ[a]*cosine;
	 X[b] =  initX[b]*cosine +  initZ[b]*sine;;
	 Y[b] =  initY[b];
	 Z[b] =  initX[b]*(-1.0*sine)+  initZ[b]*cosine;

	 X[a]=X[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 Y[a]=Y[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 X[b]=X[b]*1.0/(1+((Z[b]+l)*1.0/d*1.0));
	 Y[b]=Y[b]*1.0/(1+((Z[b]+l)*1.0/d*1.0));

	drawline((int) X[a],(int) Y[a],(int) X[b],(int) Y[b]);
	 X[a]=initX[a];
	 Y[a]=initY[a];
	 Z[a]=initZ[a];

	 X[b]=initX[b];
	 Y[b]=initY[b];
	 Z[b]=initZ[b];

	//printf("eikhane\n");
	

}

void rotateY()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    

    //drawAxis();
	int k=0;
	for(int i=0; i<m;i++)
	{
		for(k=1;k<edge[i][0];k++)
		{

			helperY(edge[i][k],edge[i][k+1]);

			//drawline((int)X[edge[i][k]],(int)Y[edge[i][k]],(int)X[edge[i][k+1]],(int)Y[edge[i][k+1]]);
		}
		helperY(edge[i][k+1],edge[i][0]);
		//drawline((int)X[edge[i][k+1]],(int)Y[edge[i][k+1]],(int)X[edge[i][0]];,(int)Y[edge[i][0]]);
	}
	glFlush();
	degree2++;

}
void helperX(int a, int b)
{
	float sine = sin((degree3*PI*1.0)/(180*1.0));
    float cosine = cos((degree3*PI*1.0)/(180*1.0));
  
	 X[a] =  initX[a];
	 Y[a] =  initY[a]*cosine- initZ[a]*sine;
	 Z[a] =  initY[a]*sine- initZ[a]*cosine;

	 X[b] =  initX[b];
	 Y[b] =  initY[b]*cosine- initZ[b]*sine;
	 Z[b] =  initY[b]*sine- initZ[b]*cosine;

	 X[a]=X[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 Y[a]=Y[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 X[b]=X[b]*1.0/(1+((Z[b]+l)*1.0/d*1.0));
	 Y[b]=Y[b]*1.0/(1+((Z[b]+l)*1.0/d*1.0));

	drawline((int) X[a],(int) Y[a],(int) X[b],(int) Y[b]);

	 X[a]=initX[a];
	 Y[a]=initY[a];
	 Z[a]=initZ[a];

	 X[b]=initX[b];
	 Y[b]=initY[b];
	 Z[b]=initZ[b];


}

void rotateX()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ////glflush();

    //drawAxis();
	int k=0;
	for(int i=0; i<m;i++)
	{
		for(k=1;k<edge[i][0];k++)
		{

			helperX(edge[i][k],edge[i][k+1]);

			//drawline((int)X[edge[i][k]],(int)Y[edge[i][k]],(int)X[edge[i][k+1]],(int)Y[edge[i][k+1]]);
		}
		helperX(edge[i][k+1],edge[i][0]);
		//drawline((int)X[edge[i][k+1]],(int)Y[edge[i][k+1]],(int)X[edge[i][0]];,(int)Y[edge[i][0]]);
	}
	degree3++;
	glFlush();

}


void process_Normal_Keys(int key, int x, int y) 
{
     switch (key) 
    {    
       case 27 :      break;
       case 100 : rotateX();  break;
       case 102 : rotateY(); break;
       case 101 : rotateZ() ;  break;
       //case 103 : //printf("GLUT_KEY_DOWN %d\n",key); d_plus();  break;
    }

}


int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2, (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	glutInitWindowPosition(2400,2400);
	glutInitWindowSize(2400,2400);
	glutCreateWindow ("Rotate Algo");
	init();
	glutDisplayFunc(inception);
	glutSpecialFunc( process_Normal_Keys );
	glutMainLoop();

	return 0;
}




		