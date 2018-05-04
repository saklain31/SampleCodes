#include<GL/glut.h>
#include <bits/stdc++.h>
#include <time.h>
#include <math.h>

using namespace std;

#define PI 3.14159265
#define ZERO .00000001

void inception();
void drawline(int xa, int ya, int xb , int yb);
void drawFigure();
int degree=0,degree2=0,degree3=0;
int u1=0,u2=0,u3=-3000;
int edge[6000][10];
double shadeVal=1.0;
vector<double> src;

int x1,x2,yone,y2;
int n=0,m=0;
double X[6000],Y[6000],Z[6000];
double initX[6000];
double initY[6000];
double initZ[6000];

double d=2500.0,l=1500.0;

struct vertex{
	int x, y;
	vertex(){}
	vertex(int a, int b){
		x=a;
		y=b;
	}
};

struct polyEdge{
	int xinit, ymin, ymax;
	double slopeInverse;
		polyEdge(){}
		polyEdge(int x1, int y1, int x2, int y2){
			double dx, dy;
			if(y2<y1){
				swap(y1, y2);
				swap(x1, x2);
			}
			dy=y2-y1;
			dx=x2-x1;
			xinit=x1;
			ymin=y1;
			ymax=y2;
			if(abs(dy-0.0)>ZERO) slopeInverse=(dx/dy);
			else slopeInverse=0;
	}
};

struct active
{
	int  ymax;
	double inx, slopeInverse;
	active(){};
	active(polyEdge line)
	{
		inx=line.xinit;
		ymax=line.ymax;
		slopeInverse=line.slopeInverse;
	}
};

bool compareline(polyEdge a,polyEdge b)
{
	if(a.ymin<b.ymin) return true;
	else return false;
}

bool sortLine(active a,active b)
{
	if(a.inx<b.inx) return true;
	else return false;
}
struct polygon
{
	polyEdge line[10];
	int currY;
	int lineCount;
	polygon(){};
	polygon(int n,vertex p[])
	{
		for(int i=0;i<n;i++)
		{
			line[i]=polyEdge(p[i].x,p[i].y,p[(i+1)%n].x,p[(i+1)%n].y);
		}
		lineCount=n;
	}

	void color()
	{
		sort(line,line+lineCount,compareline);
		int ymax=-10000;
		for(int i=0;i<lineCount;i++)
		{
			if(line[i].ymax>ymax) ymax=line[i].ymax;
		}

		currY = line[0].ymin;
		active cList[10],pList[10];
		int pSize=0,cSize=0;
		for(int i=currY;i<=ymax;i++)
		{
			for(int k=0 ;k<lineCount;k++)
			{
				if(i==line[k].ymin)
				{
					cList[cSize]=active(line[k]);
					cSize++;
				}
			}
			for(int j=0;j<pSize;j++)
			{
				if(i!=pList[j].ymax) 
				{
					cList[cSize]=pList[j];
					cList[cSize].inx+=cList[cSize].slopeInverse;
					cSize++;
				}
			}

			sort(cList,cList+cSize,sortLine);
			for(int j=0;(j+1)<cSize;j+=2)
			{
				drawline(cList[j].inx,i,cList[j+1].inx,i);
			}
			pSize=0;
			for(int j=0;j<cSize;j++)
			{
				pList[j]=cList[j];
				pSize++;
			}
			cSize=0;
		}


	}
};

polygon poly;
vertex points[10];


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
			X[edge[i][k]]=initX[edge[i][k]];
			Y[edge[i][k]]=initY[edge[i][k]];
			X[edge[i][k+1]]=initX[edge[i][k+1]];
			Y[edge[i][k+1]]=initY[edge[i][k+1]];
		}
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
	if(shadeVal>0)
		glColor3f(1.0*shadeVal,1.0*shadeVal,1.0*shadeVal);
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
}

void drawline(int xa, int ya, int xb , int yb)
{
	//printf("%d %d %d %d\n",xa,ya,xb,yb);
	int temp1=x1, temp2=x2, temp3=yone, temp4=y2;
	x1=xa, yone=ya, x2=xb, y2=yb;
	draw();
	x1=temp1, x2=temp2, yone=temp3, y2=temp4;
}

void inception2()
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	vertex temp[105];

    temp[0]=vertex(-100,-100);
    temp[1]=vertex(100,100);
    temp[2]=vertex(0,500);

	polygon poly = polygon(3, temp);

	poly.color();
}
void inception()
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();
    int t;

    src.push_back(u1);
    src.push_back(u2);
    src.push_back(u3);

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
		fscanf(fp,"%lf %lf %lf",&X[i],&Y[i],&Z[i]);
		X[i]*=300;
		Y[i]*=300;
		Z[i]*=300;
		
		initX[i]=X[i];
		initY[i]=Y[i];
		initZ[i]=Z[i];
	}
	for(int i=0;i<m;i++)
	{
		fscanf(fp,"%d %d %d %d",&edge[i][0],&edge[i][1],&edge[i][2],&edge[i][3]);
	}
	translate();
}

void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1200,1200,-1200,1200);
}


vector<double> tempVal[100];
int cnt=0;
vector<double> cross;

struct hidden
{
	double x[10],y[10],z[10];
	int idx[10]; 
	hidden(){}
	hidden(int i,double a, double b, double c,int id)
	{
		x[i] = a;
		y[i] = b;
		z[i] = c;
		idx[i]=id;
	}
};

hidden hd[6000];

double minSort(hidden a)
{
	double zd=100000;
	for(int i=0;i<3;i++)
	{	
		if(a.z[i]<zd)
		{
			zd=a.z[i];
		}
	}
	return zd;
}

bool hiddenSort(hidden a,hidden b)
{
	double zd1=minSort(a);
	double zd2=minSort(b);
	if(zd1>zd2) return true;
	else return false;
}

void crossProduct(vector<double> line1,vector<double> line2)
{
	double a=-(line1[1]*line2[2]-line2[1]*line1[2]);
	double b=-(line1[2]*line2[0]-line2[2]*line1[0]);
	double c=line1[0]*line2[1]-line2[0]*line1[1];

	double val = a*a+b*b+c*c;
	val=sqrt(val);

	cross.push_back(a/val*1.0);
	cross.push_back(b/val*1.0);
	cross.push_back(c/val*1.0);
}

void calculateShadeVal(int count)
{
	double p=0,q=0,r=0;
	for(int i=0;i<count;i++)
	{
		p+=tempVal[i][0];
		q+=tempVal[i][1];
		r+=tempVal[i][2];
	}
	p=p/count;
	q=q/count;
	r=r/count;

	p = src[0] - p;
	q = src[1] - q;
	r = src[2] - r;

	double val = p*p+q*q+r*r;
	val= sqrt(val);

	p= p/val;
	q= q/val;
	r= r/val;

	double sh = p*cross[0] + q*cross[1] + r*cross[2];

	shadeVal = sh;
}

void shade(int count)
{
	vector<double> line1,line2;
	
	line1.push_back(tempVal[1][0]-tempVal[0][0]);
	line1.push_back(tempVal[1][1]-tempVal[0][1]);
	line1.push_back(tempVal[1][2]-tempVal[0][2]);

	line2.push_back(tempVal[2][0]-tempVal[1][0]);
	line2.push_back(tempVal[2][1]-tempVal[1][1]);
	line2.push_back(tempVal[2][2]-tempVal[1][2]);

	crossProduct(line1,line2);
	
	line1.clear();
	line2.clear();

	calculateShadeVal(count);

	cross.clear();
}

double new_x,new_y,new_z; 

void helperZ(int a, int idx)
{
	double sine = sin((degree3*PI*1.0)/(180*1.0));
    double cosine = cos((degree3*PI*1.0)/(180*1.0));
  
	X[a] =  initX[a]*cosine + initY[a]*(-1.0*sine);
	Y[a] =  initX[a]*sine + initY[a]*cosine;

	X[a]=X[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	Y[a]=Y[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));

	new_x = X[a];
	new_y = Y[a];
	new_z = Z[a]; 

	X[a]=initX[a];
	Y[a]=initY[a];
	Z[a]=initZ[a];
}

void rotateZ()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	int k=0;
	int i;
	for(i=0; i<m;i++)
	{
		for(k=1;k<=edge[i][0];k++)
		{
			helperZ(edge[i][k],k-1);
			hd[i]=hidden(k-1,new_x,new_y,new_z,k-1);
		}
	}

	sort(hd,hd+m,hiddenSort);

	for(i=0;i<m;i++)
	{
		int cnt=0;
		for(int k=0;k<3;k++)
		{
			tempVal[cnt].push_back(hd[i].x[k]);
			tempVal[cnt].push_back(hd[i].y[k]);
			tempVal[cnt].push_back(hd[i].z[k]);
			points[hd[i].idx[k]] = vertex((int)hd[i].x[k],(int)hd[i].y[k]);
			cnt++;

		}

		shade(cnt);

		for(int k=0;k<3;k++)
		{
			tempVal[k].clear();
		}

		cnt=0;

		poly=polygon(3,points);
		poly.color();
		
	}

	glFlush();
	degree3--;
}
void helperY(int a,int idx)
{
	double sine = sin((degree2*PI*1.0)/(180*1.0));
    double cosine = cos((degree2*PI*1.0)/(180*1.0));
  
	 X[a] =  initX[a]*cosine +  initZ[a]*sine;
	 Y[a] =  initY[a];
	 Z[a] =  initX[a]*(-1.0*sine) +  initZ[a]*cosine;

	 X[a]=X[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 Y[a]=Y[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));

	new_x = X[a];
	new_y = Y[a];
	new_z = Z[a];

	 X[a]=initX[a];
	 Y[a]=initY[a];
	 Z[a]=initZ[a];
}

void rotateY()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
	int k=0;
	int i;
	for(i=0; i<m;i++)
	{
		for(k=1;k<=edge[i][0];k++)
		{
			helperY(edge[i][k],k-1);
			hd[i]=hidden(k-1,new_x,new_y,new_z,k-1);	
		}
	}
	sort(hd,hd+m,hiddenSort);

	for(i=0;i<m;i++)
	{
		int cnt=0;
		for(int k=0;k<3;k++)
		{
			tempVal[cnt].push_back(hd[i].x[k]);
			tempVal[cnt].push_back(hd[i].y[k]);
			tempVal[cnt].push_back(hd[i].z[k]);
			points[hd[i].idx[k]] = vertex((int)hd[i].x[k],(int)hd[i].y[k]);
			cnt++;

		}
		shade(cnt);

		for(int k=0;k<3;k++)
		{
			tempVal[k].clear();
		}

		cnt=0;
		//printf("ksa\n");

		poly=polygon(3,points);
		poly.color();
		
	}
	glFlush();
	degree2++;

}
void helperX(int a, int idx)
{
	double sine = sin((degree3*PI*1.0)/(180*1.0));
    double cosine = cos((degree3*PI*1.0)/(180*1.0));
  
	 X[a] =  initX[a];
	 Y[a] =  initY[a]*cosine- initZ[a]*sine;
	 Z[a] =  initY[a]*sine + initZ[a]*cosine;

	 X[a]=X[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));
	 Y[a]=Y[a]*1.0/(1+((Z[a]+l)*1.0/d*1.0));

	 //points[idx]= vertex((int)X[a],(int)Y[a]);
	new_x = X[a];
	new_y = Y[a];
	new_z = Z[a];

	 X[a]=initX[a];
	 Y[a]=initY[a];
	 Z[a]=initZ[a];
}

void rotateX()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	int k=0;
	int i;

	for(i=0; i<m;i++)
	{
		for(k=1;k<=edge[i][0];k++)
		{
			helperX(edge[i][k],k-1);
			hd[i]=hidden(k-1,new_x,new_y,new_z,k-1);
		}
		//poly = polygon(edge[i][0],points);
		//poly.color();
	}
	sort(hd,hd+m,hiddenSort);
	/*for(i=0;i<m;i++){
		cout<<" "<<hd[i].z[0]<<" "<<hd[i].z[1]<<" "<<hd[i].z[2] << endl;
	}*/

	for(i=0;i<m;i++)
	{
		int cnt=0;
		for(int k=0;k<3;k++)
		{
			tempVal[cnt].push_back(hd[i].x[k]);
			tempVal[cnt].push_back(hd[i].y[k]);
			tempVal[cnt].push_back(hd[i].z[k]);
			points[hd[i].idx[k]] = vertex((int)hd[i].x[k],(int)hd[i].y[k]);
			cnt++;

		}

		shade(cnt);

		for(int k=0;k<3;k++)
		{
			tempVal[k].clear();
		}

		cnt=0;
		poly=polygon(3,points);
		poly.color();
		
	}

	degree3++;
	glFlush();
}

void incX()
{
	//printf("akuhd\n");
	src.clear();
	u1+=100;
	if(u1>1200) u1=0;
	printf("%d\n",u1);
	src.push_back(u1);
	src.push_back(u2);
	src.push_back(u3);
}
void incY()
{
	src.clear();
	u2+=10;
	src.push_back(u1);
	src.push_back(u2);
	src.push_back(u3);
}
void incZ()
{
	src.clear();
	u3+=10;
	if(u3==-2000) u3=-3000;
	src.push_back(u1);
	src.push_back(u2);
	src.push_back(u3);
}


void process_Normal_Keys(int key, int x, int y) 
{
	printf("key %d\n",key );
     switch (key) 
    {    
       case 27 :      break;
       case 100 : rotateX();  break;
       case 102 : rotateY(); break;
       case 101 : rotateZ() ;  break;
       //case 107 : incX() ; break;
       //case GLUT_KEY_F10 : incY() ; break;
       case 3 : incX() ; break;
       case 1 : incY(); break;
       case 2:	incZ(); break;

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




		