#include<GL/glut.h>
#include <bits/stdc++.h>

#include <time.h>
#include <math.h>

#define EPS 1e-10
#define PI acos(-1.0)
using namespace std;
double d;


struct point2D{
	int x, y;
	point2D(){}
	point2D(int _x, int _y){
		x=_x;
		y=_y;
	}
};

struct line2D{
	int xi, ymin, ymax;
	double invslope;
		line2D(){}
		line2D(int xp, int yp, int xq, int yq){
			double dx, dy;
			if(yq<yp){
				swap(yp, yq);
				swap(xp, xq);
			}
			dy=yq-yp;
			dx=xq-xp;
			xi=xp;
			ymin=yp;
			ymax=yq;
			if(abs(dy-0.0)>EPS) invslope=(dx/dy);
			else invslope=0;
	}
};

struct activeEdge{
	int ymx;
	double cx;
	double invSlope; 
	activeEdge(){}
	activeEdge(line2D l){
		ymx=l.ymax;
		cx=l.xi;
		invSlope=l.invslope;
	}
	void update(){
		cx+=invSlope;
	}
};
bool cmpEdge(activeEdge a, activeEdge b){
	return a.cx<b.cx;
}
	
bool cmpline(line2D a, line2D b){
	return a.ymin<b.ymin;
}
struct polygon2D{
	point2D ara[105];
	int npoints;
	polygon2D(){}
	polygon2D(int n, point2D tmp[]){
		npoints=n;
		for(int i=0; i<npoints; i++){
			ara[i]=tmp[i];
		}
	}
	
	line2D l[105];
	
	
	
	vector <activeEdge> prev, curr;
	
	
	
	void fill(){
		int n=npoints;
		int limy=-1000000000;
		for(int i=0; i<(n-1); i++){
			l[i]=line2D(ara[i].x, ara[i].y, ara[i+1].x, ara[i+1].y);  
			limy=max(limy, ara[i].y);
		}
		l[n-1]=line2D(ara[n-1].x, ara[n-1].y, ara[0].x, ara[0].y);
		limy=max(limy, ara[n-1].y);
		sort(l, l+n, cmpline);
		int it1=0;
		int cy=l[0].ymin;
		/*printf("The lines are:\n");
		for(int i=0; i<3; i++){
			printf("%d %d %d %f\n", l[i].xi, l[i].ymin, l[i].ymax, l[i].invslope); 
		}*/
		prev.clear();
		while(cy<limy){
			//cout<<"cy="<<cy<<endl;
			while(it1<n && l[it1].ymin==cy){
				curr.push_back(l[it1]);
				//printf("Pushing line no %d\n", it1);
				it1++;
			}
			for(int i=0; i<(int)prev.size(); i++){
				if(prev[i].ymx==cy){
					//printf("Popping line at ymax=%d\n", cy);
					continue;
				}
				curr.push_back(prev[i]);
				curr[curr.size()-1].update();
			}
			sort(curr.begin(), curr.end(), cmpEdge);
			for(unsigned int i=0; (i+1)<(curr.size()); i+=2){
				for(int j=curr[i].cx; j<curr[i+1].cx; j++){
					//printf("%d %d\n", j, cy);
					glBegin(GL_POINTS);
					glColor3f(1.0, 1.0, 1.0);
					glVertex2i((int) j, cy);
					glEnd();
				}
			}
			cy++;
			prev.clear();
			for(unsigned int i=0; i<curr.size(); i++){
				prev.push_back(curr[i]);
			}
			curr.clear();
		}
	}
};

void init(void)
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1200,1200,-1200,1200);
}

void inception()
{
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	point2D temp[105];

    temp[0]=point2D(-100,-100);
    temp[1]=point2D(100,100);
    temp[2]=point2D(0,500);

	polygon2D poly = polygon2D(3, temp);

	poly.fill();
}

int main(int argc, char** argv) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-640)/2, (glutGet(GLUT_SCREEN_HEIGHT)-480)/2);
	//glutInitWindowPosition(800,800);
	glutInitWindowSize(1200,800);
	glutCreateWindow ("Rotate Algo");
	init();
	glutDisplayFunc(inception);
	//glutSpecialFunc( process_Normal_Keys );
	glutMainLoop();

	return 0;
}