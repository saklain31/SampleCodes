#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>

void ClipAndDraw();
void clipWindow();
void clip();

int x1,x2,y1,y2;
float teL,teB,teR,teT;
//float xe1,xe2,ye1,ye2,xl1,xl2,yl1,yl2;
float tmax=-100, tmin=100;

float enter, leave;

float xmin=-150, xmax=150, ymin=-100, ymax=100;

//float eL, eR, eT, eB;

int findZone()
{
	int dx = x2-x1;
	int dy=y2-y1;
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
	int dy = y2-y1;
	int d = 2*dy - dx;
	int dE = 2*dy;
	int dNE = 2 * (dy-dx);

	int x=x1, y=y1;
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
		glVertex2i(x1,y1);
		//glColor3f(0.9,0.7,0.6);
		drawline0(zone);
	}
	else if(zone==1)
	{
		printf("zone=%d\n",1 );
		glVertex2i(x1,y1);
		//glColor3f(0.4,0.3,0.1);
		
		temp1=x1;
		x1=y1;
		y1=temp1;

		temp1=x2;
		x2=y2;
		y2=temp1;		

		drawline0(zone);
	}
	else if(zone==2)
	{
		printf("zone=%d\n",2 );
		glVertex2i(x1,y1);
		//glColor3f(0.5,0.8,0.1);

		temp1=x1;
		x1=y1;
		y1= -temp1;

		temp1=x2;
		x2=y2;
		y2= -temp1;		
		drawline0(zone);
	}
	else if(zone==3)
	{
		printf("zone=%d\n",3 );
		glVertex2i(x1,y1);
		//glColor3f(0.4,0.3,0.7);
		
		x1=-x1;
		x2=-x2;

		drawline0(zone);
	}
	else if(zone==4)
	{
		printf("zone=%d\n",4 );
		glVertex2i(x1,y1);
		//glColor3f(0.6,0.5,0.9);	
		
		x1=-x1;
		y1=-y1;
		x2=-x2;
		y2=-y2;

		drawline0(zone);
	}
	else if(zone==5)
	{
		printf("zone=%d\n",5 );
		glVertex2i(x1,y1);
		//glColor3f(0.9,0.3,0.2);

		temp1=x1;
		x1=-y1;
		y1=-temp1;

		temp1=x2;
		x2=-y2;
		y2=-temp1;		

		drawline0(zone);
	}
	else if(zone==6)
	{
	
		printf("zone=%d\n",6 );
		glVertex2i(x1,y1);
		//glColor3f(0.1,0.1,0.2);

		temp1=x1;
		x1=-y1;
		y1=temp1;

		temp1=x2;
		x2=-y2;
		y2=temp1;

		drawline0(zone);
	}
	else if(zone==7)
	{
		printf("zone=%d\n",7 );
		glVertex2i(x1,y1);
		//glColor3f(0.1,0.3,0.8);
		
		y1=-y1;
		y2=-y2;

		drawline0(zone);
	}

	glFlush();
}

void drawRandom()
{
	int p=0;

	srand(time(NULL));   
	int i;
	
	while(p<10)
	{
		x1= rand()%200;
		//x1=0;
		i=rand()%100;
		if(i>50) x1= x1*(-1);
		y1= rand()%500;
		//y1=0;
		i=rand()%100;
		if(i>50) y1= y1*(-1);
		x2= rand()%100;
		i=rand()%100;
		if(i>50) x2= x2*(-1);
		y2= rand()%200;
		i=rand()%100;
		if(i>50) y2= y2*(-1);
		glColor3f(0.4,0.3,0.7);
		int tempx1=x1,tempx2=x2,tempy1=y1,tempy2=y2;
		printf("before %d %d %d %d\n",x1,y1,x2,y2);
		draw();	 
		x1=tempx1,x2=tempx2,y1=tempy1,y2=tempy2;
		glColor3f(0.1,0.6,0.1);
		clip();
		p++;	                                      
	}
}

void clipWindow()
{
	x1=150,y1=100,x2=150,y2=-100;
	draw();
	x1=150,y1=100,x2=-150,y2=100;
	draw();
	x1=-150,y1=100,x2=-150,y2=-100;
	draw();
	x1=-150,y1=-100,x2=150,y2=-100;
	draw();

	
	drawRandom();
}

void clip()
{
	teT= -(((y1-ymax)*1.0)/((y2-y1)*1.0));
	teB= -(((y1-ymin)*1.0)/((y2-y1)*1.0));
	teR= -(((x1-xmax)*1.0)/((x2-x1)*1.0));
	teL= -(((x1-xmin)*1.0)/((x2-x1)*1.0));

	printf("t= %f %f %f %f\n", teT,teB,teL,teR);

	if(y2>=y1)
	{
		enter=teB;
		leave=teT;
	}
	else
	{
		enter=teT;
		leave=teB;
	}

	if(x2>=x1)
	{
		if(teL>enter) enter=teL;
		if(teR<leave) leave=teR;	
	}
	else
	{
		if(teR>enter) enter=teR;
		if(teL<leave) leave=teL;
	}


	if(enter<leave)
	{
		if(enter>1) enter=1.0;
		if(enter<0) enter=0.0;
		if(leave>1) leave=1.0;
		if(leave<0) leave=0.0;

		float t1,t2,t3,t4,t5,t6,t7,t8;
		t1=x1+leave*(x2-x1);
		t2=x1+enter*(x2-x1);
		t3=y1+leave*(y2-y1);
		t4=y1+enter*(y2-y1);

		printf("after %d %d %d %d\n",x1,y1,x2,y2);
		x1=t1,x2=t2,y1=t3,y2=t4;
		printf("clip= %f %f %f %f\n",x1,y1,x2,y2);
		
		draw();

	}
}
void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200,200,-200,200);
}

int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (840, 640);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Line Clipping Algo");
	init();
	glutDisplayFunc(clipWindow);
	glutMainLoop();

	return 0;
}




		