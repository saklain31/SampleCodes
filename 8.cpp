#include <bits/stdc++.h>
using namespace std;

int grid[3][3],sol[3][3];
int fin=0,min_move=30;
int p =-1;

int manhutton()
{
    int dis=0, temp=0;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<3; k++)
                for (int l=0; l<3; l++)
                {
                    if(grid[i][j]==sol[k][l] && grid[i][j]!=0)
                    {
                        temp= abs(i-k)+abs(j-l);
                        dis= dis + temp;
                        break;
                    }
                }
    return dis;
}
int l=0;
int func(int flag,int move, bool print)
{
    //printf("%d\n",++l);
    //char ch = getchar();
    //printf("move = %d\n",move);
    int count=0;
    /*if(print==true)
    {
    	printf("******\n");
    	/*for(int i=0;i<3;i++)
    	{
    		for(int j=0;j<3;j++)
    		{
    			printf("%d ",grid[i][j]);
    		}
    		printf("\n");
    	}
    	return 0;
    }*/
    int val= 100;
    int man = manhutton();
    if(move+man > min_move)
        return -1;
    if(man==0)
    {
        //printf("sol %d\n", move );
        if(move<min_move)
            min_move=move;
        p=1;
        return move;
    }
    //move>=min_move) return false;

    int temp, tag=0;
    int t=-1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
        {
            if(grid[i][j]==0)
            {
                if(i<2 && flag!=2)
                {
                    //right
                    temp = grid[i+1][j];
                    grid[i+1][j]=0;
                    grid[i][j]=temp;

                    t = func(1,move+1,false);

                    if(t!=-1)
                    {
                        if(t<val)
                        {
                            //printf("Setting tag=%d, val=%d\n", tag, val);
                            val= t;
                            tag=1;
                        }
                    }

                    temp = grid[i][j];
                    grid[i][j]=0;
                    grid[i+1][j]=temp;

                }
                if(i>0 && flag!=1)
                {
                    temp= grid[i-1][j];
                    grid[i-1][j]=0;
                    grid[i][j]=temp;
                    //left
                    t=func(2,move+1,false);

                    temp= grid[i][j];
                    grid[i][j]=0;
                    grid[i-1][j]=temp;

                    if(t!=-1)
                    {
                        if(t<val)
                        {
                            val= t;
                            tag=2;
                            //printf("Setting tag=%d, val=%d\n", tag, val);
                        }
                    }
                }
                if(j<2 && flag!=4)
                {
                    //bottom
                    temp= grid[i][j+1];
                    grid[i][j+1]=0;
                    grid[i][j]=temp;

                    t=func(3,move+1,false);

                    temp= grid[i][j];
                    grid[i][j]=0;
                    grid[i][j+1]=temp;

                    if(t!=-1)
                    {
                        if(t<val)
                        {
                            val= t;
                            tag=3;
                            //printf("Setting tag=%d, val=%d\n", tag, val);
                        }
                    }

                }
                if(j>0 && flag!=3)
                {
                    //top
                    temp= grid[i][j-1];
                    grid[i][j-1]=0;
                    grid[i][j]=temp;

                    t=func(4,move+1,false);

                    temp = grid[i][j];
                    grid[i][j]=0;
                    grid[i][j-1]=temp;

                    if(t!=-1)
                    {
                        if(t<val)
                        {
                            val= t;
                            tag=4;
                            //printf("Setting tag=%d, val=%d\n", tag, val);
                        }
                    }
                }
            }
        }
    }
    /*
                if(tag==1)
                	printf("right\n");
                else if(tag==2)
                	printf("left\n");
                else if(tag==3)
                	printf("bottom\n");
                else if(tag==4)
                	printf("top\n");
                	*/
                //printf("tag %d \n", tag);
    //printf("val=%d tag=%d\n", val, tag);
    if(print==true)
    {
            printf("******\n");
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    printf("%d ",grid[i][j]);
                }
                printf("\n");
            }
            for(int i=0; i<3; i++)
            {
                    for(int j=0; j<3; j++)
                    {
                        if(grid[i][j]==0)
                        {
                                if(tag==1)
                                {
                                    temp = grid[i+1][j];
                                    grid[i+1][j]=0;
                                    grid[i][j]=temp;
                                    //printf("Going Right\n");
                                    t = func(1,move+1,true);

                                    temp = grid[i][j];
                                    grid[i][j]=0;
                                    grid[i+1][j]=temp;

                                }
                                else if(tag==2)
                                {
                                    temp= grid[i-1][j];
                                    grid[i-1][j]=0;
                                    grid[i][j]=temp;
                                    //left
                                    //printf("Going Left\n");
                                    t=func(2,move+1,true);

                                    temp= grid[i][j];
                                    grid[i][j]=0;
                                    grid[i-1][j]=temp;

                                }
                                else if(tag==3)
                                {
                                    temp= grid[i][j+1];
                                    grid[i][j+1]=0;
                                    grid[i][j]=temp;
                                    //printf("Going Down\n");
                                    t=func(3,move+1,true);

                                    temp= grid[i][j];
                                    grid[i][j]=0;
                                    grid[i][j+1]=temp;

                                }
                                else if(tag==4)
                                {
                                    temp= grid[i][j-1];
                                    grid[i][j-1]=0;
                                    grid[i][j]=temp;
                                    //printf("Going Up\n");
                                    t=func(4,move+1,true);

                                    temp = grid[i][j];
                                    grid[i][j]=0;
                                    grid[i][j-1]=temp;

                                }
                            }
                        }
                    }
        }

                /*if(tag!=0)
                {
                	printf("******\n");
                	/*for(int i=0;i<3;i++)
                	{
                		for(int j=0;j<3;j++)
                		{
                			printf("%d ",grid[i][j]);
                		}
                		printf("\n");
                	}
                }*/
                return move+val;

}

main()
{
    freopen("in.txt", "r", stdin);
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            scanf("%d",&grid[i][j]);
        }
    }
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            scanf("%d",&sol[i][j]);
        }
    }

    printf("allllll\n");
    func(0,0,true);
    //func(0,0,false);
    //func(0,0,true);
    if(p==-1)
        printf("impossible\n");
    else
        printf("%d\n",min_move);
}

