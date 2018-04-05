#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

float x1,x2,y1,y2;

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

void drawline(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void line0(float m)
{
	float x,y;
	x=x1,y=y1;
	for(x=x1;x<=x2;x++)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		y=y+m;
	}
}
void line1(float m)
{
	float x,y;
	x=x1,y=y1;
	for(y=y1;y<=y2;y++)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		x= x+ 1.0/(m*1.0);
	}
}
void line2(float m)
{
	float x,y;
	x=x1,y=y1;
	for(y=y1;y<=y2;y++)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		x= x - 1.0/(m*1.0);
	}
}
void line3(float m)
{
	float x,y;
	x=x1,y=y1;
	printf("%f\n", m);
	for(x=x1;x>=x2;x--)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		y=y+m;
	}
}
void line4(float m)
{
	float x,y;
	x=x1,y=y1;
	for(x=x1;x>=x2;x--)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		y=y-m;
	}
}
void line5(float m)
{
	float x,y;
	x=x1,y=y1;
	for(y=y1;y>=y2;y--)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		x= x - 1.0/(m*1.0);
	}
}
void line6(float m)
{
	float x,y;
	x=x1,y=y1;
	for(y=y1;y>=y2;y--)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		x= x + 1.0/(m*1.0);
	}
}
void line7(float m)
{
	float x,y;
	x=x1,y=y1;
	printf("%f\n", m);
	for(x=x1;x<=x2;x++)
	{
		drawline((int)(x+0.5),(int)(y+0.5));
		y=y-m;
		printf("%f %f\n",x,y );
	}
}
void draw(void)
{
	
 	int zone = findZone();

 	int dx = x2-x1;
	int dy=y2-y1;
	float m = dy*1.0/dx;
    printf("jklh %f\n",m );
	glBegin(GL_POINTS);
	glVertex2i(x1,y1);
	glEnd();

    if(m<0) m=m*(-1);

 	printf("jksdflh %f\n",m );
	if(zone==0)
	{
		printf("zone=%d\n",0 );
		line0(m);
	}
	else if(zone==1)
	{
		printf("zone=%d\n",1 );
		line1(m);
	}
	else if(zone==2)
	{
		printf("zone=%d\n",2 );
		line2(m);
	}
	else if(zone==3)
	{
		printf("zone=%d\n",3 );
		line3(m);
		//printf("sadasdasd\n");
	}
	else if(zone==4)
	{
		printf("zone=%d\n",4 );
		line4(m);
	}
	else if(zone==5)
	{
		printf("zone=%d\n",5 );
		line5(m);
	}
	else if(zone==6)
	{
		printf("zone=%d\n",6 );
		line6(m);
	}
	else if(zone==7)
	{
		printf("zone=%d\n",7 );
		line7(m);
	}

	glFlush();
}

void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100,100,-100,100);
}

int main(int argc, char** argv) {
	printf("Enter the value of x1 : ");
	scanf("%f",&x1);
	printf("Enter the value of y1 : ");
	scanf("%f",&y1);
	printf("Enter the value of x2 : ");
	scanf("%f",&x2);
	printf("Enter the value of y2 : ");
	scanf("%f",&y2);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (840, 640);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("DDA Line Algo");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();

	return 0;
}