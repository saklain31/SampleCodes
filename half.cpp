#include <bits/stdc++.h>
using namespace std;
int h,w,color;
int n,m;
string str,str2;
int input[1000][1000],output[1000][1000];


void halftoning(int i,int j,int val)
{
	
	val=val/9;
	//printf("%d\n",val);
	if(val>=25)
	{
		output[i+1][j+1] = 255;
	}
	if(val>=50)
	{
		output[i+1][j+2] = 255;
	}
	if(val>=80)
	{
		output[i+1][j] = 255;
	}
	if(val>=105)
	{
		output[i][j+1] = 255;
	}
	if(val>=130)
	{
		output[i+2][j+2] = 255;
	}
	if(val>=160)
	{
		output[i][j] = 255;
	}
	if(val>=180)
	{
		output[i+2][j] = 255;
	}
	if(val>=210)
	{
		output[i+2][j+1] = 255;
	}
	if(val>=235)
	{
		output[i][j+2] = 255;
	}
}

void takeInput()
{
	freopen("lena.ascii.pgm","r",stdin);
	freopen("output.ascii.pgm","w",stdout);
	getline(cin,str); 
	getline(cin,str2);

	cin>>w>>h>>color;
	n=h%3;
	m=w%3;
	for(int i=0;i<h+n;i++)
	{
		for(int j=0;j<w+m;j++)
		{
			if(i>=h)
			{
				input[i][j]=0;
				continue;
			}
			else if(j>=w)
			{
				input[i][j]=0;
				continue;	
			}
			scanf("%d",&input[i][j]);
		}
	}

	/*for(int i=0;i<h+n;i++)
	{
		for(int j=0;j<w+m;j++)
		{
			output[i][j]=0;
		}
	}*/

	int i,j;
	for(i=0;i<h+n;i+=3)
	{
		
		for(j=0;j<w+m;j+=3)
		{
			int val=0;
			val+=input[i][j];
			//printf("%d\n",input[i][j] );
			val+=input[i][j+1];
			//printf("%d\n", input[i][j+1]);
			val+=input[i][j+2];
			//printf("%d\n",input[i][j+2] );
			val+=input[i+1][j];
			//printf("%d\n", input[i+1][j]);
			val+=input[i+1][j+1];
			//printf("%d\n", input[i+1][j+1]);
			val+=input[i+1][j+2];
			//printf("%d\n", input[i+1][j+2]);
			val+=input[i+2][j];
			//printf("%d\n", input[i+2][j]);
			val+=input[i+2][j+1];
			//printf("%d\n",input[i+2][j+1] );
			val+=input[i+2][j+2];
			//printf("%d\n",input[i+2][j+2] );

			halftoning(i,j,val);
		}
		
		
	}	
}
main()
{
	takeInput();
	cout<<str<<endl;
	cout<<str2<<endl;
	cout<<w<<" "<<h<<endl;
	cout<<color<<endl;
	for(int i=0;i<h;i++) 
	{
		for(int j=0;j<w;j++) 
		{
			cout<<output[i][j]<<" ";
		}
	}
}




















