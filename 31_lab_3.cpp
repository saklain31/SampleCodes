#include <bits/stdc++.h>
using namespace std;
int n , max_weight=0, max_val=0, fit=0;
int initial[4][10];
int w[]={14, 26, 19, 45, 5, 25, 34, 18, 30, 12};
int	v[]={20, 24, 18, 70, 14, 23, 50, 17, 41, 21};
int weight, value;

int fitness()
{
	int temp1=0, temp2=0, temp=0, total=0;
	for(int i=0;i<4;i++)
	{
		temp1=0, temp2=0;
		for(int j=0;j<10;j++)
		{
			if(initial[i][j]==1)
			{
				temp1+=w[j];
				temp2+=v[j];
			}
		}

		if(temp1>100)
		{
			temp1=100-temp1;
			total+=temp1;
		}
		else
			total+=temp2;
	}
	
	return total;

}

void crossover(int flag, int r1, int r2, int idx)
{
	//printf("crossover\n");
	int temp;
	if(flag==1)
	{
		for(int i=idx; i<10; i++)
		{
			temp =  initial[r1][idx];
			initial[r1][idx] = initial[r2][idx];
			initial[r2][idx] =temp;
		}
	}
}

void mutation(int flag)
{
	//printf("mutation\n");
	int c;
	if(flag==1)
	{
		for(int r=0;r<4;r++)
		{
			c=rand()%10;
			if(initial[r][c]==0)
				initial[r][c]=1;
			else if(initial[r][c]==1)
				initial[r][c]=0;
		}
	}


}

main()
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			int k= rand()%2;
			initial[i][j]=k;
			//cur[i][j]=k;
		}
	}
	
	

	int p,r1,r2,idx,cnt=0;
	while(1)
	{
		r1= rand()%4;
		r2= rand()%4;
		while(r1==r2)
		{
			r2=rand()%4;
		}
		idx=rand()%10;
		crossover(1,r1,r2,idx);
		//printf("r1 r2 %d %d \n",r1,r2);
		if(r1!=0)
		{
			r1=0;
			if(r2!=1)
				r2=1;
			else if(r2!=2)
				r2=2;
			else if(r2!=3)
				r2=3;
		}
		else if(r1!=1)
		{
			r1=1;
			if(r2!=0)
				r2=0;
			else if(r2!=2)
				r2=2;
			else if(r2!=3)
				r2=3;
		}
		else if(r1!=2)
		{
			r1=2;
			if(r2!=1)
				r2=1;
			else if(r2!=0)
				r2=0;
			else if(r2!=3)
				r2=3;
		}
		else if(r1!=3)
		{
			r1=3;
			if(r2!=1)
				r2=1;
			else if(r2!=2)
				r2=2;
			else if(r2!=0)
				r2=0;
		}
		
		//printf("r1 r2 %d %d \n",r1,r2);
		
		crossover(1,r1,r2,idx);

		mutation(1);
		p=fitness();
		if(p>fit)
		{
			fit=p;
			printf("success=%d\n",fit);
		}
		cnt++;
		printf("Iteration %d , fitness = %d\n",cnt,fit);

	}

}