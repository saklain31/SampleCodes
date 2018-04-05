#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>


int x1,x2,y1,y2;
int x11,x22,y11,y22;

int findZone()
{
	int dx = x2-x1;
	int dy=y2-y1;
	if(dx>=0 && dy>=0)
	{
		if(dx>dy) return 0;
		else return 1;
	}
	else if(dx>0 && dy<0)
	{
		if(abs(dx)>abs(dy)) return 7;
		else return 6;
	}
	else if(dx<=0 && dy<=0)
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
			drawpoint(x,y); printf("%d %d\n",x,y );
		}
		else if(zone==1)
		{
			drawpoint(y,x); //printf("%d %d\n",y,x );
		}
		else if(zone==2)
		{
			drawpoint(-y,x); printf("%d %d\n",-y,x );
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
			drawpoint(x,-y); printf("%d %d\n",x,-y );
		}
	}
}

void draw()
{

 	int zone = findZone();

	glBegin(GL_POINTS);
	
	glEnd();
	int temp1,temp2;
	if(zone==0)
	{
		printf("zone=%d\n",0 );
		glVertex2i(x1,y1);
		glColor3f(0.9,0.7,0.6);
		drawline0(zone);
	}
	else if(zone==1)
	{
		printf("zone=%d\n",1 );
		glVertex2i(x1,y1);
		glColor3f(0.4,0.3,0.1);
		
		temp1=x1;
		x1=y1;
		y1=temp1;

		temp1=x2;
		x2=y2;
		y2=temp1;		

		//drawline0(val);
	}
	else if(zone==2)
	{
		printf("zone=%d\n",2 );
		glVertex2i(x1,y1);
		glColor3f(0.5,0.8,0.1);

		temp1=x1;
		x1=y1;
		y1= -temp1;

		temp1=x2;
		x2=y2;
		y2= -temp1;		
		//drawline0(zone);
	}
	else if(zone==3)
	{
		printf("zone=%d\n",3 );
		glVertex2i(x1,y1);
		glColor3f(0.4,0.3,0.7);
		
		x1=-x1;
		x2=-x2;

		//drawline0(zone);
	}
	else if(zone==4)
	{
		printf("zone=%d\n",4 );
		glVertex2i(x1,y1);
		glColor3f(0.6,0.5,0.9);	
		
		x1=-x1;
		y1=-y1;
		x2=-x2;
		y2=-y2;

		//drawline0(zone);
	}
	else if(zone==5)
	{
		printf("zone=%d\n",5 );
		glVertex2i(x1,y1);
		glColor3f(0.9,0.3,0.2);

		temp1=x1;
		x1=-y1;
		y1=-temp1;

		temp1=x2;
		x2=-y2;
		y2=-temp1;		

		//drawline0(zone);
	}
	else if(zone==6)
	{
	
		printf("zone=%d\n",6 );
		glVertex2i(x1,y1);
		glColor3f(0.1,0.1,0.2);

		temp1=x1;
		x1=-y1;
		y1=temp1;

		temp1=x2;
		x2=-y2;
		y2=temp1;

		//drawline0(zone);
	}
	else if(zone==7)
	{
		printf("zone=%d\n",7 );
		glVertex2i(x1,y1);
		glColor3f(0.1,0.3,0.8);
		
		y1=-y1;
		y2=-y2;

		//drawline0(zone);
	}
	drawline0(zone);
	glFlush();
}
void changeZone(int change_val)
{
	int temp;
	if(change_val==0 || change_val==1)
	{
		if(x11>x22)
		{
			temp=x11;
			x11=x22;
			x22=temp;
		}
		if(y11>y22)
		{
			temp=y11;
			y11=y22;
			y22=temp;
		}
	}
	else if(change_val==4 ||change_val==5)
	{
		if(x22>x11)
		{
			temp=x11;
			x11=x22;
			x22=temp;	
		}
		if(y22>y11)
		{
			temp=y11;
			y11=y22;
			y22=temp;	
		}
	}
}

void drawRandom()
{
	int p=0;
	x1= -315; y1= 150; x2= -15; y2=150;
	draw();
	x1= -315; y1=150; x2= -315; y2=-150;
	draw();
	x1= -315; y1=-150; x2= -15; y2= -150;
	draw();
	x1=-15; y1= -150; x2= -15; y2= 150;
	draw();

	x1= 315; y1= 150; x2= 15; y2=150;
	draw();
	x1= 315; y1=150; x2= 315; y2=-150;
	draw();
	x1= 315; y1=-150; x2= 15; y2= -150;
	draw();
	x1= 15; y1= -150; x2= 15; y2= 150;
	draw();

	int i,j;
	//3rd block 1st sqr
	x11=-115;
	x22=-15;
	y11= 50;
	y22=150;

	/*
	changeZone(1);
	printf("%d %d %d %d\n",x11,y11,x22,y22);

	for(i=x11;i<x22;i++)
	{
		x1=i;
		x2=i;
		y1=y11;
		y2=y22;
		printf("%d %d %d %d\n",x1,y1,x2,y2);
		draw();
	}
	*/
	//5th block
	x11=-215;
	x22=-115;
	y11=50;
	y22=-50;

	changeZone(4);
	printf("%d %d %d %d\n",x11,y11,x22,y22);

	for(j=y11;j>y22;j--)
	{
		x1=x11;
		x2=x22;
		y1=j;
		y2=j;
		draw();
	}
	
	x11=-215;
	x22=-315;
	y11=-150;
	y22=-50;

	changeZone(5);
	for (i=x11;i>x22;i--)
	{
		x1=i;
		x2=i;
		y1=y11;
		y2=y22;
		draw();
	}
	


}
void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320,320,-160,160);
}

int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (640, 320);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("BOX");
	init();
	glutDisplayFunc(drawRandom);
	glutMainLoop();

	return 0;
}




		