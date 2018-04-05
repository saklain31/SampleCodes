#include <bits/stdc++.h>
#include <time.h>
#include <math.h>

using namespace std;
struct nonTerminal 
{
	char ch;
	vector<char> first,follow;
	vector<char> rhs[10]; 
	vector<char> table[10];
	int count;
	int tablecnt;
};
nonTerminal nonTerm[100];
int cycle[100];
int nonTermcnt=0;
int tag[100];
int cnt=0;
int copyId[10][10];
vector<char> stck;
char st[100];
int gram=0;
int makeNonTerm(char t)
{
	for(int i=0;i<nonTermcnt;i++)
	{
		if(nonTerm[i].ch == t)
			return i;
	}
	return -1;
}

void input()
{
	int n,flag=0, idx=0;
	char ar[100];
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		flag=0;
		scanf("%s",ar);
		for(int j=0;ar[j]!='\0';j++)
		{
			if(flag==0)
			{
				idx = makeNonTerm(ar[j]);
				if(idx==-1)
				{
					nonTerm[nonTermcnt].ch = ar[j];
					idx=nonTermcnt;
					nonTermcnt++;
				}
				flag=1;
			}
			else if(flag==1)
			{
				if(ar[j]=='-')
				{
					j++;
					if(ar[j]!='>')
					{
						printf("err1\n");
						break;
					}

				}
				else
				{
					printf("err2\n");
					break;
				}
				flag=2;
			}
			else if(flag==2)
			{
				nonTerm[idx].rhs[nonTerm[idx].count].push_back(ar[j]);
			}

		}
		nonTerm[idx].count+=1;
	}	
}
int computeIndex(char t)
{
	for(int i=0;i<nonTermcnt;i++)
	{
		if(nonTerm[i].ch==t) return i;
	}
	return -1;
}

void computeFirst(char t)
{
	int flag=0, incflag;
	int id=computeIndex(t);

	if(cycle[id]==1)
	{
		printf("CYCLE\n");
		gram=1;
		return;
	}
	cycle[id]=1;

	for(int i=0;i<nonTerm[id].count;i++)
	{
		int j=0;
		do
		{
			if(j==nonTerm[id].rhs[i].size())
			{
				nonTerm[id].first.push_back('#');
				break;
			}
			flag=0;
			if(nonTerm[id].rhs[i][j]>=65 && nonTerm[id].rhs[i][j]<=90)
			{
				int id2= computeIndex(nonTerm[id].rhs[i][j]);
				computeFirst(nonTerm[id].rhs[i][j]);
				incflag=0;
				for(int k=0;k<nonTerm[id2].first.size();k++)
				{
					if(nonTerm[id2].first[k]!='#')
					{
						nonTerm[id].first.push_back(nonTerm[id2].first[k]);
					}
					else
					{
               	        flag=1;
               	        if(incflag==0){
               	        	j++;
                    		incflag=1;
                    	}
                    }
				}
			}
			else
			{
				//printf("pushing %c to %c Term\n",nonTerm[id].rhs[i][j],nonTerm[id].ch);	
				nonTerm[id].first.push_back(nonTerm[id].rhs[i][j]);	
			}

			//printf("flag %c\n", nonTerm[id].ch);
		}while(flag);
	}
	//printf("Returning from %c\n", nonTerm[id].ch);
	cycle[id]=2;
}

void duplication()
{
	for(int i=0;i<nonTermcnt;i++)
	{
		sort(nonTerm[i].first.begin(),nonTerm[i].first.end());
		nonTerm[i].first.erase(std::unique(nonTerm[i].first.begin(), nonTerm[i].first.end()), nonTerm[i].first.end());
	}
}
void duplication2()
{
	for(int i=0;i<nonTermcnt;i++)
	{
		sort(nonTerm[i].follow.begin(),nonTerm[i].follow.end());
		nonTerm[i].follow.erase(std::unique(nonTerm[i].follow.begin(), nonTerm[i].follow.end()), nonTerm[i].follow.end());
	}
}


void computeFollow(int id)
{
	if(!nonTerm[id].follow.empty() || tag[id])
		return;
	else if(id==0)
		nonTerm[0].follow.push_back('$');

	tag[id]=1;
	int flag=0;
	char val = nonTerm[id].ch;
	for(int i=0;i<nonTermcnt;i++)
	{
		for(int j=0;j<nonTerm[i].count;j++)
		{
			for(int k=0;k<nonTerm[i].rhs[j].size();k++)
			{
				if(nonTerm[i].rhs[j][k]==val)
				{
					flag=0;
					do
					{
						flag=0;
						if((k+1)!=nonTerm[i].rhs[j].size())
						{
							k++;
							if(nonTerm[i].rhs[j][k]>=65 && nonTerm[i].rhs[j][k]<=90)
							{
								int id2=computeIndex(nonTerm[i].rhs[j][k]);
								for(int m=0;m<nonTerm[id2].first.size();m++)
								{
									if(nonTerm[id2].first[m]!='#')
									{
										nonTerm[id].follow.push_back(nonTerm[id2].first[m]);
									}
									else
									{
										flag=1;
									}
								}
							}
							else
							{
								nonTerm[id].follow.push_back(nonTerm[i].rhs[j][k]);
							}
						}
						else
						{
							computeFollow(computeIndex(nonTerm[i].ch));
							if(nonTerm[id].ch!=nonTerm[i].ch)
							for(int l=0;l<nonTerm[i].follow.size();l++)
							{
								nonTerm[id].follow.push_back(nonTerm[i].follow[l]);
							}
						}
					}while(flag==1);
				}
			}
		}
	}
}

void computeTable()
{	
	int flag=0;
	for(int i=0;i<nonTermcnt;i++)
	{
		for(int j=0;j<nonTerm[i].count;j++)
		{
			int k=0;
			do
			{
				flag=0;
				if(k==nonTerm[i].rhs[j].size() || nonTerm[i].rhs[j][k]=='#')
				{
					for(int l=0;l<nonTerm[i].follow.size();l++)
					{
						//printf("follow Table\n");
						//printf("pushing %c\n",nonTerm[i].follow[l]);
						nonTerm[i].table[nonTerm[i].tablecnt].push_back(nonTerm[i].follow[l]);
						for(int z=0;z<nonTerm[i].rhs[j].size();z++)
						{
                        	nonTerm[i].table[nonTerm[i].tablecnt].push_back(nonTerm[i].rhs[j][z]);
                        	//printf("pushing %c\n",nonTerm[i].rhs[j][z] );
						}
						nonTerm[i].tablecnt++;
					}


				}
              	else if(nonTerm[i].rhs[j][k]>=65 && nonTerm[i].rhs[j][k]<=90)
                {
                	//printf("nonTerm Table\n");
                	int pd = computeIndex(nonTerm[i].rhs[j][k]);
	                for(int u=0;u<nonTerm[pd].first.size();u++)
	                {
	                	if(nonTerm[pd].first[u]=='#')
	                	{
	                		flag=1;
	                		k++;
	                		continue;
	                	}
	                	//printf("pushing %c\n",nonTerm[pd].first[u]);
	                	nonTerm[i].table[nonTerm[i].tablecnt].push_back(nonTerm[pd].first[u]);
	                	for(int x=0;x<nonTerm[i].rhs[j].size();x++)
	                	{
	                		nonTerm[i].table[nonTerm[i].tablecnt].push_back(nonTerm[i].rhs[j][x]);
	                		//printf("pushing %c\n",nonTerm[i].rhs[j][x]);
	                	}
	                	
	                	nonTerm[i].tablecnt++;
	                }
                }
                else
                {
                	//printf("term table\n");
                	//printf("pushing %c\n", nonTerm[i].rhs[j][k]);
                	nonTerm[i].table[nonTerm[i].tablecnt].push_back(nonTerm[i].rhs[j][k]);

                	for(int z=0;z<nonTerm[i].rhs[j].size();z++)
                	{
                		//printf("pushing %c\n", nonTerm[i].rhs[j][z]);
                		nonTerm[i].table[nonTerm[i].tablecnt].push_back(nonTerm[i].rhs[j][z]);
                	}
                	
                	nonTerm[i].tablecnt++;
                }
			}while(flag);
		}
	}
}
void derivation()
{
	strcat(st,"$");
	stck.push_back('$');
	stck.push_back(nonTerm[0].ch);
	int index=0;

	while(!stck.empty() && index<strlen(st))
	{
		/*for(int p=0;p<stck.size();p++)
		{
			printf("%c ",stck[p]);
		}
		printf("\n");
		*/

		//printf("index=%d char=%c\n",index,st[index]);
		if(stck.back()>='A' && stck.back()<='Z')
		{
			bool check=false;
			int idx= computeIndex(stck.back());
			int i=idx;

			for(int j=0;j<nonTerm[i].tablecnt;j++)
			{
				//printf("%c\n",nonTerm[i].table[j][0] );
				if(nonTerm[i].table[j][0]==st[index])
				{
					check=true;
					printf("%c->",nonTerm[i].ch );
					for(int k=1;k<nonTerm[i].table[j].size();k++)
					{
						printf("%c",nonTerm[i].table[j][k]);
					}
					printf("\n");

					stck.pop_back();

					if(nonTerm[i].table[j][1]!='#')
					{
						for(int k=nonTerm[i].table[j].size()-1;k>0;k--)
						{
							stck.push_back(nonTerm[i].table[j][k]);
						}
					}
					continue;
				}
			}
			
			
			if(check==false)
			{
				printf("Derivation Error 1\n");
				return;
			}
		}
		else
		{
			if(stck.back()==st[index])
			{
				stck.pop_back();
				index++;
			}
			else
			{
				printf("Derivation Error 1\n");
				return;
			}
		}
	}

}	
main()
{
	input();
	printf("%d\n",nonTermcnt);
	/*for(int i=0;i<nonTermcnt;i++)
	{
		//printf("%d %d %c\n",i,nonTerm[i].count,nonTerm[i].ch);
		for(int j=0;j<nonTerm[i].count;j++)
		{
			printf("%c->",nonTerm[i].ch);
			for(int k=0;k<nonTerm[i].rhs[j].size();k++)
			{
				printf("%c",nonTerm[i].rhs[j][k]);
			}
			printf("\n");
		}
	}*/
	
	for(int i=0;i<nonTermcnt;i++)
	{
		computeFirst(nonTerm[i].ch);
	}
	duplication();
	if(gram==1)
	{
		printf("NOT LL(1) GRAMMAR\n");
		exit(0);
	}
	printf("\nLIST OF FIRST\n");
	for(int i=0;i<nonTermcnt;i++)
	{
		printf("First of %c :",nonTerm[i].ch);
		for(int j=0;j<nonTerm[i].first.size();j++)
		{
			printf("%c ", nonTerm[i].first[j]);
		}
		printf("\n");
	}

	for(int i=0;i<nonTermcnt;i++)
	{
		computeFollow(i);
		nonTerm[i].tablecnt=0;
	}
	duplication2();
	printf("\nLIST OF FOLLOW\n");
	for(int i=0;i<nonTermcnt;i++)
	{
		printf("Follow of %c :",nonTerm[i].ch);
		for(int j=0;j<nonTerm[i].follow.size();j++)
		{
			printf("%c ", nonTerm[i].follow[j]);
		}
		printf("\n");
	}
	printf("\nLL(1) PARSING TABLE:\n");
	computeTable();
	for(int i=0;i<nonTermcnt;i++)
	{
		for(int j=0; j<nonTerm[i].tablecnt;j++)
		{
			for(int k=0;k<nonTerm[i].table[j].size();k++)
			{
				if(k==0)
				{
					printf("%c on %c use production %c->",nonTerm[i].ch,nonTerm[i].table[j][k],nonTerm[i].ch);
				}
				else
				{
					printf("%c",nonTerm[i].table[j][k]);
				}
			}
			printf("\n");
		}
	}
	printf("\nENTER STRING:\n");
	scanf("%s", &st);
	derivation();
}