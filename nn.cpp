#include <bits/stdc++.h>
using namespace std;

double v[10][10], w[10],z_in[10],z[10];
double bool1[4]={0,0,1,1},bool2[4]={0,1,0,1};
double y_in,y,t[4]={0,1,1,0},del,del_in[10],alpha=0.2,dw[10],dv[10][10];

void output_layer(int idx);
void backprop(int idx);
void update(int idx);

double activate(double x)
{
	return (1.0/1.0*(1+exp(-x)));
}

double sigmoid(double x)
{
	return x*(1-x);
}

void initialization()
{
	for(int i=0; i<3 ;i++)
	{
		for(int j=1; j<4;j++)
		{
			scanf("%lf",&v[i][j]);
		}
	}
	printf("lmlllll\n");

	for(int i=0; i<3 ;i++)
	{
		for(int j=1; j<4;j++)
		{
			printf("%lf ",v[i][j]);
		}
	}

	printf("lmlllll2\n");
	for(int i=0;i<4;i++)
	{
		if(rand()%2==0)
			w[i]= 1.0*(rand()%10)/1.0*10;
		else
			w[i]= -1.0*(rand()%10)/1.0*10;
	}
	printf("lmlllll\n");
	for(int i=0;i<4;i++)
	{
		printf("%lf ",w[i]);
	}
	printf("lmlllll\n");

}
void hidden_layer(int idx)
{
	printf("asche\n");
	double temp=0;
	
	for(int j=1;j<4;j++)
	{
		temp=0;
		for(int i=1;i<3;i++)
		{
			if(i==1)temp+=bool1[idx]*v[i][j];
			else temp+=bool2[idx]*v[i][j];
		}
		printf("temp = %lf\n",temp);
		z_in[j]=v[0][j]+temp;
		z[j]=activate(z_in[j]);
		for()
	}

	output_layer(idx);
	
}
void output_layer(int idx)
{
	double temp=0;
	for(int j=1;j<4;j++)
	{
		temp+=z[j]*w[j];
	}
	y_in=w[0]+temp;
	y=activate(y_in);

	backprop(idx);
}

void backprop(int idx)
{
	del= (t[idx]-y) * sigmoid(y_in);
	printf("%lf ", abs(t[idx]-y));
	for(int i=1;i<4;i++)
	{
		dw[i]= alpha*del*z[i];
	}
	dw[0]= alpha*del;

	for(int j=1;j<4;j++)
	{
		del_in[j] = del * w[j];
	}

	update(idx);

}

void update(int idx)
{
	for(int i=1;i<3;i++)
	{
		for (int j=1;j<4;j++)/////////////////
		{
			if(i==1)
				dv[i][j]=alpha*del_in[j]*sigmoid(z_in[j])*bool1[idx];
			else
				dv[i][j]=alpha*del_in[j]*sigmoid(z_in[j])*bool2[idx];
		}

	}

	for (int j=1;j<4;j++)
	{
		dv[0][j]=alpha*del_in[j]*sigmoid(z_in[j]);
	}

	for(int i=0;i<4;i++)
	{
		w[i]=w[i]+dw[i];
	}

	for(int i=0; i<3 ;i++)
		for(int j=1; j<4 ; j++)
		{
			v[i][j]=v[i][j]+dv[i][j];
		}


}
main()
{
	initialization();

	while(1)
	{
		for(int idx=0;idx<4;idx++)
		{
			hidden_layer(idx);
		}
	}
}