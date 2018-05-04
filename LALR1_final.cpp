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

vector<char> termlist;

struct production
{
	vector<char> prod;
	int dot;
	long long int hashVal=-1;
	set <char> lookahead;
	bool operator == (const production &p)const
	{
		if(prod.size()!=p.prod.size())
		{
			return false;
		}
		else
		{
			for(int i=0;i<p.prod.size();i++)
			{
				if(p.prod[i]!=prod[i]) return false;
			}
		}

		set <char> :: iterator iter1,iter2;
		if(dot != p.dot) return false;
		if(lookahead.size()!=p.lookahead.size())
		{
			return false;
		}
		else
		{
			for(iter1=lookahead.begin(),iter2=p.lookahead.begin(); iter1!=lookahead.end() ; iter1++,iter2++)
			{
				if((*iter1)!=(*iter2)) return false;
			}
		}
		return true;
	}


	bool isEqualwithoutLookahead(production p)
	{
		if(prod.size()!=p.prod.size())
		{
			return false;
		}
		else
		{
			for(int i=0;i<p.prod.size();i++)
			{
				if(p.prod[i]!=prod[i]) return false;
			}
		}

		if(dot != p.dot) return false;
		
		return true;
	}



	long long int hash()
	{
		long long val=0;
		for(int i=0;i<prod.size();i++)
		{
			if(i==0)
			{
				val=(int)prod[i];
			}
			else
			{
				val=(val*300+(int)prod[i])%500000003;
			}	
		}
		val= (val*300+dot)%500000003;

		set<char>:: iterator iter;
		for(iter=lookahead.begin();iter!=lookahead.end();iter++)
		{
			val=(val*300+ (int)(*iter))%500000003;
		}
		hashVal=val;
		return val;
	}

	bool operator < (const production &pd)const
	{
		assert(hashVal!=-1);
		assert(pd.hashVal!=-1);
		return hashVal < pd.hashVal;
	}


};

struct canItem
{
	set <production> prodItems;
	bool operator == (canItem c)
	{
		set<production> :: iterator iter1,iter2;
		if(prodItems.size()!=c.prodItems.size())
			return false;
		else
		{
			for(iter1=prodItems.begin(),iter2=c.prodItems.begin();iter1!=prodItems.end();iter1++,iter2++)
			{
				
				if((*iter1).hashVal!=(*iter2).hashVal)
					return false;
			}
		}
		return true;
	}

	bool isEqualwithoutLookahead(canItem c)
	{
		int itcnt=0;
		set<production> :: iterator iter1,iter2;

		if(prodItems.size()!=c.prodItems.size())
			return false;
		else
		{
			for(iter1=prodItems.begin();iter1!=prodItems.end();iter1++)	
			{
				for(iter2=c.prodItems.begin();iter2!=c.prodItems.end();iter2++)
				{
					production p,q;
					p=*iter1;
					q=*iter2;
					if(p.isEqualwithoutLookahead(q))
					{

						itcnt++;
						break;
					}
				}
			}
		}
		if(itcnt==prodItems.size())
			return true;
		else
			return false;
	}
};

production element[100];
int prodcount=0;
nonTerminal nonTerm[100];
int cycle[100];
int nonTermcnt=0;
canItem canNode[100];
int canItemcnt=0;
int tag[100];
int cnt=0;
int copyId[10][10];
vector<char> stck;
char st[100];
int gram=0;
map < char ,pair <char,int> > stable[100];
map <char ,int > gtable[100];
map < char ,pair <char,int> > stable2[100];
map <char ,int > gtable2[100];
vector<int> derive;

void iterate()
{
	for(auto el: stable[0])
	{
		cout << el.first << endl;
	}
}

void calculateClosure(int idx, production el);

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

	element[prodcount].prod.push_back('N');
	for(int i=0;i<n;i++)
	{
		flag=0;
		scanf("%s",ar);
		if(i==0)
		{
			element[prodcount].dot=0;
			element[prodcount].prod.push_back(ar[0]);

			prodcount++;
		}

		for (int k = 0; ar[k]!='\0'; k++)
		{
			if(ar[k]!='-' && ar[k]!='>')
				element[prodcount].prod.push_back(ar[k]);
		}
		element[prodcount].dot=0;
		prodcount++;

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
				nonTerm[id].first.push_back(nonTerm[id].rhs[i][j]);	
			}
		}while(flag);
	}
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

int isProdEqual(production pd)
{
	for(int i=0;i<prodcount; i++)
	{
		if(pd.prod.size()!=element[i].prod.size())
			continue;
		int j;
		for(j=0;j<element[i].prod.size();j++)
		{
			if(pd.prod[j]!=element[i].prod[j]) break;
		}
		if(j==pd.prod.size())
		{
			return i;
		}
	}
	return -1;
}

void Table(int idx)
{
	set<production> :: iterator it;
	for(it=canNode[idx].prodItems.begin(); it!=canNode[idx].prodItems.end();it++)
	{
		production p= *it;
		if(p.dot+1 >= p.prod.size())
		{
			int id= isProdEqual(p);
			set<char> :: iterator lookit;
			for(lookit=p.lookahead.begin();lookit!=p.lookahead.end();lookit++)
			{
				stable[idx][*lookit] = pair<char,int> ('r',id);
				//printf("State %d on %c *REDUCE* using production %d\n",idx,*lookit,id);
			}
		}
		else if(p.prod[1]=='#')
		{
			int id= isProdEqual(p);
			set<char> :: iterator lookit;
			for(lookit=p.lookahead.begin();lookit!=p.lookahead.end();lookit++)
			{
				stable[idx][*lookit] = pair<char,int> ('r',id);
				//printf("State %d on %c *REDUCE* using production %d\n",idx,*lookit,id);
			}
		}
	}

	for(int i=0;i<termlist.size();i++)
	{

		char c = termlist[i];
		int flag=0;
		for(it=canNode[idx].prodItems.begin(); it!=canNode[idx].prodItems.end();it++)
		{
			production p = *it;
			if(p.dot+1<p.prod.size())
			{
				if(p.prod[p.dot+1]==c)
				{	
					production np=p;
					np.dot++;
					calculateClosure(canItemcnt,np);
					flag=1;
				}
			}
		}
		if(flag==0) continue;
		int in = canItemcnt;
		for(int j=0;j<canItemcnt;j++)
		{
			if(canNode[j]==canNode[in])
			{
				in=j;
				break;	
			}
		}

		stable[idx][c] = pair<char,int> ('s',in);
		//printf("State %d on %c *SHIFT* and change State to %d\n",idx,c,in);
		if(in==canItemcnt) 
		{
			canItemcnt++;
			Table(in);
		}
		else{
			canNode[canItemcnt].prodItems.clear();
		}
	}

	for(int i=0;i<nonTermcnt;i++)
	{
		char c=nonTerm[i].ch;
		int flag=0;
		for(it=canNode[idx].prodItems.begin(); it!=canNode[idx].prodItems.end();it++)
		{
			production p = *it;
			if(p.dot+1<p.prod.size())
			{
				if(p.prod[p.dot+1]==c)
				{	
					production np=p;
					np.dot++;
					calculateClosure(canItemcnt,np);
					flag=1;
				}
			}
		}
		if(flag==0) continue;
		int in = canItemcnt;
		for(int j=0;j<canItemcnt;j++)
		{
			if(canNode[j]==canNode[in])
			{
				in=j;
				break;	
			}
		}

		gtable[idx][c] = in;

		//printf("gtable %d %c %d\n",idx,c,in);
		//printf("State %d on %c *GO TO* State %d\n",idx,c,in);
		if(in==canItemcnt) 
		{
			canItemcnt++;
			Table(in);
		}
		else{
			canNode[canItemcnt].prodItems.clear();
		}
	}
}
void calculateClosure(int idx, production el)
{
	el.hash();
	canNode[idx].prodItems.insert(el);

	if(el.dot>=el.prod.size()-1)
		return;
	if(el.prod[el.dot+1]>='A' && el.prod[el.dot+1]<= 'Z')
	{
		set <char> look;
		int i;
		for(i=el.dot+2; i<el.prod.size();i++)
		{
			int flag = 0;
			if(el.prod[i]>='A' && el.prod[i]<= 'Z')
			{
				int id = computeIndex(el.prod[i]);
				for(int j=0; j<nonTerm[id].first.size();j++)
				{
					if(nonTerm[id].first[j]!='#')
					{
						look.insert(nonTerm[id].first[j]);
					}
					else
					{
						flag=1;
					}
				}
				if(!flag) break;
			}
			else
			{
				look.insert(el.prod[i]);
				break;
			}
		}
		if(i>=el.prod.size())
		{
			set <char> :: iterator it;
			for(it=el.lookahead.begin(); it!=el.lookahead.end();it++)
			{
				look.insert(*it);
			}
		}


		char curr = el.prod[el.dot+1];
		//printf("Curr=%c\n", curr);
		int id = computeIndex(curr);

		for(int k=0;k<nonTerm[id].count;k++)
		{
			production p;
			p.prod.clear();
			p.prod.push_back(curr);
			for(int z=0;z<nonTerm[id].rhs[k].size();z++)
			{
				p.prod.push_back(nonTerm[id].rhs[k][z]);
			}
			p.dot=0;
			p.lookahead = look;
			p.hash();
			if(canNode[idx].prodItems.find(p)==canNode[idx].prodItems.end())
			{
				calculateClosure(idx,p);
			}
		}
	} 
}
void calculateCanonical()
{
	element[0].lookahead.insert('$');

	calculateClosure(0,element[0]);
	canItemcnt++;

	Table(0);
}

void printStack()
{
	printf("stack:");
	for(int i=0;i<stck.size();i++)
	{
		printf("%c ",stck[i]);
	}
	printf("\n");
}

void printDerivation()
{
	printf("*************\n");
	printf("Derivation\n");
	printf("*************\n");
	for(int i=derive.size()-1;i>=0;i--)
	{
		for(int j=0;j<element[derive[i]].prod.size();j++)
		{
			printf("%c",element[derive[i]].prod[j]);
			if(j==0) printf("->");
		}
		printf("\n");
	}
}

void derivation()
{
	printf("Enter String:\n");
	scanf("%s",st);
	strcat(st,"$");
	stck.push_back(0+'0');
	int stIdx=0;
	int ac=0;

	printf("%c\n",element[0].prod[1]);

	if(stable2[0].find(st[stIdx])!=stable2[0].end()) 
	{
		stck.push_back(st[stIdx]);
		printf("pushing %c\n",st[stIdx]);
		stck.push_back(stable2[0][st[stIdx]].second+'0');
		printf("pushing %c\n",stable2[0][st[stIdx]].second+'0');
		stIdx++;
	}
	printStack();
	char currChar=st[0];
	while(!stck.empty())
	{
		int currIdx=stck.back()-'0';
		currChar=st[stIdx];	

		if(stable2[currIdx].find(currChar)!=stable2[currIdx].end() && stable2[currIdx][currChar].first=='s')
		{
			stck.push_back(currChar);
			printf("pushing %c\n",currChar );
			stck.push_back(stable2[currIdx][currChar].second+'0');
			printf("pushing %c\n",stable2[currIdx][currChar].second+'0');
			stIdx++;
			printStack();
		}
		else if(stable2[currIdx].find(currChar)!=stable2[currIdx].end() && stable2[currIdx][currChar].first=='r')
		{
			int len = element[stable2[currIdx][currChar].second].prod.size()-1;
			int currNon = element[stable2[currIdx][currChar].second].prod[0];

			derive.push_back(stable2[currIdx][currChar].second);

			if(element[stable2[currIdx][currChar].second].prod[1]!='#')
			{
				for(int i=0;i<len*2;i++)
				{
					//if(i%2==0)
					//	printf("poping %c\n",stck.back()-'0');
					//else
					printf("poping %c\n",stck.back());

					stck.pop_back();	
				}
			}
		
			printStack();
			currIdx=stck.back()-'0';

			int p= stck.back();
			//printf("CurrIdx CurrNon %d %c\n",currIdx,currNon );
			if(gtable2[currIdx].find(currNon)!=gtable2[currIdx].end())
			{
				//printf("GoTo\n");
				int next=gtable2[currIdx][currNon];
				stck.push_back(currNon);
				printf("pushing %c\n",currNon);
				if(stck.back()==element[0].prod[1] && currChar=='$')
				{
					ac=1;
				}
				stck.push_back(next+'0');
				printf("pushing %c\n",next+'0');
				printStack();
			}
			else 
			{
				break;
				printf("%c\n",stck.back());
			}
		}
		else
		{
			printf("..%c\n",stck.back());
			break;
		}
	}
	printStack();
	if(ac==1)
	{
		printf("Accepted\n");
		printDerivation();
	}
	else
		printf("Not Accepted\n");
}


void printCanItems()
{
	printf("******************\n");
	printf("Canonical Items\n");
	printf("******************\n");
	set <production> :: iterator it;
	for(int looper=0; looper<canItemcnt; looper++)
	{
		printf("\n*Node no %d*\n", looper);
		for(it=canNode[looper].prodItems.begin();it!=canNode[looper].prodItems.end();it++)
		{
			printf("\n");
			production tmp=*it;
			for(int j=0;j<tmp.prod.size();j++)
			{
				printf("%c ",tmp.prod[j]);
				if(j==0) printf("->");
			}
			printf("\n");
			printf("dot=%d\n",tmp.dot);
			printf("lookahead:");
			set <char> :: iterator it2;
			for(it2=tmp.lookahead.begin();it2!=tmp.lookahead.end();it2++)
			{
				printf(" %c ",(*it2));
			}
			printf("\n");
		}
		printf("**************\n");
	}
}

void LALRTable()
{
	printf("***Same Item pairs***\n");
	set <int> rmvItems,rmvCanItems;
	vector<int> itemPair[100];
	int itemPaircnt=0;
	int lalrItem=0;
	for(int i=0;i<canItemcnt;i++)
	{
		if(rmvItems.find(i)!=rmvItems.end())
		{
			continue;
		}
		for(int j=0;j<canItemcnt;j++)
		{
			if(i!=j)
			{
				if(canNode[i].isEqualwithoutLookahead(canNode[j]))
				{
					rmvItems.insert(j);
					itemPair[itemPaircnt].push_back(i);
					itemPair[itemPaircnt].push_back(j);
					printf("%d %d\n",i,j);
					itemPaircnt++;
				}
			}
		}
	}

	printf("****Removed Items****\n");
	set<int> :: iterator iter;
	for(iter=rmvItems.begin();iter!=rmvItems.end();iter++)
	{
		printf("%d ",*iter);
	}
	printf("\n");

	map < char ,pair <char,int> > ::iterator iter1;
	map <char ,int > ::iterator iter2;
	map < char ,pair <char,int> > temp;

	for(int i=0;i<canItemcnt;i++)
	{
		for(auto elem : stable[i])
		{
			int flag=0;
			if(elem.second.first=='s')
			{
				for(int j=0;j<itemPaircnt;j++)
				{	
					if(elem.second.second==itemPair[j][0] || elem.second.second==itemPair[j][1])
					{
						if(stable2[i].find(elem.first)==stable2[i].end())
						{
							stable2[i][elem.first] = make_pair('s',itemPair[j][0]);
							flag=1;
						}
						else
						{
							printf("conflict\n");
							return;
						}
						//rmvCanItems.insert(itemPair[j][1]);
					}
				}
				if(flag!=1)
				{
					stable2[i][elem.first]=make_pair('s',elem.second.second);
				}
			}
			else if(elem.second.first=='r')
			{
				for(int j=0;j<itemPaircnt;j++)
				{
					if(i==itemPair[j][1] || i==itemPair[j][0])
					{
						if(stable2[i].find(elem.first)==stable2[i].end())
						{
							stable2[itemPair[j][0]][elem.first]=make_pair('r',elem.second.second);
							flag=1;
						}
						else
						{
							printf("conflict\n");
							return;
						}
					}
				}
				if(flag!=1)
				{
					stable2[i][elem.first]=make_pair('r',elem.second.second);
				}
			}
			
		}

		for(auto elem: gtable[i])
		{
			int flag=0;
			for(int j=0;j<itemPaircnt;j++)
			{
				if(elem.second==itemPair[j][0] || elem.second==itemPair[j][1])
				{
					gtable2[i][elem.first] = itemPair[j][0];
					flag=1;
				}
			}
			if(flag!=1)
			{
				gtable2[i][elem.first]= elem.second;
			}
		}

	}

	printf("***LALR PARSING TABLE***\n");
	for(int i=0;i<canItemcnt;i++)
	{
		if(rmvItems.find(i)!=rmvItems.end()) continue;
		for(auto elem : stable2[i])
		{
			//printf("stable2[%d][%c] = %c %d\n",i,elem.first,elem.second.first,elem.second.second);
			if(elem.second.first=='s')
			{
				printf("State %d on %c *SHIFT* to state %d\n", i,elem.first,elem.second.second);
			}
			else if(elem.second.second=='r')
			{
				printf("State %d on %c *REDUCE* using production %d\n",i,elem.first,elem.second.second);	
			}
		}
		for(auto elem : gtable2[i])
		{
			//printf("gtable2[%d][%c] = %d\n",i,elem.first,elem.second);
			printf("State %d on %c *GOTO* state %d\n", i,elem.first,elem.second);
		}
	}
}

main()
{
	for(char a='a';a<='z';a++)
	{
		termlist.push_back(a);
	}
	termlist.push_back('(');
	termlist.push_back(')');
	termlist.push_back('$');
	termlist.push_back('*');
	termlist.push_back('+');


	input();
	printf("%d\n",nonTermcnt);
	
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
	printf("\n\nProduction\n");
	for(int i=0;i<prodcount;i++)
	{
		for(int j=0;j<element[i].prod.size();j++)
		{
			if(j==0) 
			{
				printf("%c->",element[i].prod[j]);
			}
			else
				printf("%c",element[i].prod[j]);
		}
		printf("\n");
	}

	printf("*****************\n");

	calculateCanonical();

	//printCanItems();
	
	LALRTable();

	derivation();

}