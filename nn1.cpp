#include <bits/stdc++.h>
using namespace std;


 
double V[3]={0.4,-0.3,-0.5}, W[3]={0.2,-0.4,0.2},z_in=0,z=0,t[2]={1.0,0.0};
double bool1[2]={0.0,1.0},bool2[3]={1.0,0.0};
double y_in,y,del=0.0,del_in=0.0,alpha=0.2,dW[10],dV[10];
int flag=0;

void output_layer(int idx);
void backprop(int idx);
void update(int idx);

double activate(double x)
{
	//printf("%lf\n",x);
	printf("active %lf\n",(1.0+exp(-1.0*x)) );
	double m=(1.0+exp(-1.0*x));
	return 1.0/m*1.0;
}

double sigmoid(double x)
{
	//printf("%lf\n",x);
	return x*(1-x);
}

void hidden_layer(int idx)
{
	printf("%lf %lf %lf %lf %lf\n",V[0],V[1],V[2],bool1[idx],bool2[idx]);
	//z_in= V[0]+ bool1[idx]*V[1] + bool2[idx]*V[2]; 

	//printf("z_in=%lf\n",z_in);
	z= activate(z_in);
	//printf("z %lf\n",z);

	output_layer(idx);	
}

void output_layer(int idx)
{

	
	y_in=W[0]+z*W[1];
	y=activate(y_in);

	//printf("y %lf\n", y);
	//printf("y_in %lf\n",y_in);

	backprop(idx);
}

void backprop(int idx)
{
	del= (t[idx]-y) * sigmoid(y_in);

	//printf("del2 %lf %lf %lf %lf\n",del ,(t[idx]-y), y_in,sigmoid(y_in));

	printf("err = %lf \n", abs(t[idx]-y));
	if(abs(t[idx]-y)<.001) flag=1;
	
	dW[1]= alpha*del*z;
	dW[2]= alpha*del*bool2[idx];
	dW[0]= alpha*del;

	del_in = del*W[1];

	update(idx);

}

void update(int idx)
{

	dV[1] = alpha*del_in*sigmoid(z_in)*bool1[idx];
	dV[2] = alpha*del_in*sigmoid(z_in)*bool2[idx];
	dV[0] = alpha*del_in*sigmoid(z_in);

	//printf("del %lf\n",del );
	//printf("dV %lf %lf %lf\n",dV[0],dV[1],dV[2]);

	for(int i=0;i<3;i++)
	{
		W[i]=W[i]+dW[i];
	}

	for(int i=0; i<3 ;i++)
	{
		V[i]=V[i]+dV[i];
	}
	//printf("%lf %lf %lf\n",V[0],V[1],V[2]);
}

main()
{

	while(1)
	{
		for(int idx=0;idx<2;idx++)
		{
			hidden_layer(idx);
		}
		//if(flag==1) break;
	}
}