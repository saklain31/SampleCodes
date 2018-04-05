#include <stdio.h>
#include <math.h>

double v[3]={0,0,0}, w[3]={0,0,0},z_in=0,z=0;
double bool1[2],bool2[2];
double y_in=0,y=0,del=0,del_in=0,alpha=1.0,dw[3]={0,0,0},dv[3]={0,0,0},t[2],flag=0;

void output_layer(int idx);
void backprop(int idx);
void update(int idx);

double activate(double x)
{
	return (1.0/(1.0*(1+exp(-x))));
}

double sigmoid(double x)
{
	return x*(1-x);
}

void initialization()
{
	bool1[0]=0;
	bool1[1]=1;
	bool2[0]=1;
	bool2[1]=0;
	t[0]=1;
	t[1]=0;

	for(int i=0; i<3 ;i++)
	{
		scanf("%lf",&v[i]);
	}
	printf("lmlllll\n");

	for(int i=0; i<3 ;i++)
	{
		printf("%lf ",v[i]);
	}

	printf("lmlllll2\n");
	for(int i=0;i<3;i++)
	{
		if(rand()%2==0)
			w[i]= 1.0*(rand()%10)/1.0*10;
		else
			w[i]= -1.0*(rand()%10)/1.0*10;
	}
	printf("lmlllll\n");
	for(int i=0;i<3;i++)
	{
		printf("%lf ",w[i]);
	}
	printf("lmlllll\n");

}

void hidden_layer(int idx)
{
	//printf("asche\n");

	z_in= v[0]+ bool1[idx]*v[1] + bool2[idx]*v[2]; 
	z= activate(z_in);

	output_layer(idx);
	
}

void output_layer(int idx)
{
	
	y_in=w[0]+z*w[1];
	y=activate(y_in);

	backprop(idx);
}

void backprop(int idx)
{
	del= (t[idx]-y) * sigmoid(y_in);

	printf("%lf ", abs(t[idx]-y));
	if(abs(t[idx]-y)<.001) flag=1;
	
	dw[1]= alpha*del*z;
	dw[2]= alpha*del*bool2[idx];
	dw[0]= alpha*del;

	del_in = del*w[1];

	update(idx);

}

void update(int idx)
{

	dv[1] = alpha*del_in*sigmoid(z_in)*bool1[idx];
	dv[2] = alpha*del_in*sigmoid(z_in)*bool2[idx];
	dv[0] = alpha*del_in*sigmoid(z_in);

	for(int i=0;i<3;i++)
	{
		w[i]=w[i]+dw[i];
	}

	for(int i=0; i<3 ;i++)
	{
		v[i]=v[i]+dv[i];
	}
}

main()
{
	initialization();

	while(1)
	{
		for(int idx=0;idx<3;idx++)
		{
			hidden_layer(idx);
		}
		//if(flag==1) break;
	}
}