#include <bits/stdc++.h>
#include <time.h>
#include <math.h>

using namespace std;
char ar[100];

int indx,chCount;
vector<int> follow[100],state[100];
map<int,char> chmap;
set<char> chset;

struct node
{
    char ch;
    int pos;
    vector<int> first,last;
    node *left,*right;
    bool isNullable;
    
};

void printVector(vector<int> v)
{
    for(int i=0;i<v.size();i++)
    {
        printf("%d ",v[i]);
    }
}
void printNode(node *root)
{
    int flag=0;
    if(root)
    {
        printNode(root->left);
        printNode(root->right);
        
        if(!flag)
        {
            printf("Node: %c\n",root->ch);
            printf("Position: %d\n",root->pos);
            printf("Isnull: %d\n",root->isNullable);
            printf("first: {");
            printVector(root->first);
            printf("}\nlast: {");
            printVector(root->last);
            printf("}\n");
            printf("\n");
            printf("\n");
        }
    }
}

int precedence(char a)
{
    if (a == '(') return 1;
    else  if (a == '|') return 2;
    else  if (a == '.' ) return 3;
    else if (a == '*' ) return 4;
    else return 100;
}

bool isOperator(char ch)
{
    if(ch == '|'  || ch == '*' || ch == '.') return true;
    else return false;
}

node *createNode(char ch,int pos)
{
    node *n = new node;
    n->ch = ch;
    n->pos = pos;
    n->left = NULL; 
    n->right = NULL;
    n->first.clear();
    n->last.clear();
    return n;
}

vector<int> operator+(vector<int> a,vector<int> b)
{
    a.insert(a.end(),b.begin(),b.end());
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    return a;
}


string addDot()
{ 
	string st="";
	for(int i=0;i<strlen(ar);i++)
	{
		char c1 = ar[i];
		if(i+1<strlen(ar))
		{
			char c2=ar[i+1];
			st+=c1;
			if(c1!='(' && c2 != ')' && c1!='|' && (c2!='|' && c2!='*'))
			{
				st+='.';
			}
		}
	}
	st+=ar[strlen(ar)-1];
	return st;
}

string makePostfix(string str)
{
	string result="";
	stack <char> stck;
	for (int i=0;i<str.length();i++)
    {
        char ch = str.at(i);
        if(ch== '(')
        {
            stck.push(ch);
            continue;
        }
        else if(ch==')')
        {
            while (stck.top() !='(')
            {
                result += stck.top();
                stck.pop();
            }
            stck.pop();
            continue;
        }
        else
        {
            while (!stck.empty())
            {
                char top = stck.top();
                int topPr = precedence(top);
                int currPr = precedence(ch);

                if(topPr >= currPr)
                {
                    result += stck.top();
                    stck.pop();
                }
                else break;
            }
            stck.push(ch);
            continue;
        }
    }
    while (!stck.empty())
    {
        result += stck.top();
        stck.pop();
    }
    return result;
}

void createDFA(node *root,string inStr)
{
    int stateCount = 1,current = 1;
    char ch = 'A';
    vector<int> p;
    map< vector<int>, char> resultState;
    map< vector<int>, map< char, vector<int> > >  dfaTable;
    state[stateCount] = root->first;
    printf("\nstart state:\n{");
    for(int i=0;i<root->first.size();i++)
    {
        printf("%d ",root->first[i]);
    }
    printf("}\n");
    stateCount++;
    resultState[root->first] = ch++ ;
    while(1)
    {
        for(int i = 0 ; i < inStr.size() ; i++)
        {
            for(int j = 0 ; j < state[current].size() ; j++)
            {
                if(chmap[state[current][j]] == inStr[i])
                    p = p + follow[state[current][j]];
                if(resultState[p] == 0 && p.size() > 0)
                {
                    resultState[p] = ch++;
                    state[stateCount] = p;
                    stateCount++;
                }
            }
            dfaTable[state[current]][inStr[i]] = p;
            p.clear();
        }
        if(current == stateCount - 1)
            break;
        current++;
    }
    cout<<"\n\nConstructed DFA\n\n";
    int cnt=1;
    for(auto m : dfaTable)
    {
        int f=0;
        printf("Node #%d ",cnt);
        cnt++;
        cout<<"{ ";
        for(auto n : m.first)
        {    
            cout<<n<<" ";
            for(int k=0;k<root->last.size();k++)
            {
                if(root->last[k]==n)
                    f=1;
            }
        }
        cout<<" } ";
        if(f==1)
        {
            printf("(final)");
        }
        printf("\n");
        for(auto n : m.second)
        {
            cout<<" goes to : "<<" { ";
            for(auto k:n.second)
                cout<<k<<" ";
            cout<<" } ";
            cout<<"on "<<n.first<<endl;
        }
        cout<<endl;
    }

    //printf("%d %d\n",stateCount,current);
}

void assignPos(string str)
{
    node *nd;
    stack<node *> s;
    string inStr;
    for(int i = 0 ; i < str.size() ; i++)
    {
        if(!isOperator(str[i]))
        {
            indx++;
            if(str[i] != '#')
            {
                chCount++;
                chmap[chCount] = str[i];
                chset.insert(str[i]);
            }
            

            nd = createNode(str[i],indx);
            nd->isNullable = false;
            nd->first.push_back(indx);
            nd->last.push_back(indx);
        }
        else if(str[i] == '*')
        {
            nd = createNode(str[i],0);
            nd->left = s.top(), s.pop();
            nd->isNullable = true;
            nd->first = nd->left->first;
            nd->last = nd->left->last;
            

            for(int i = 0 ; i < nd->last.size() ; i++)
                follow[nd->last[i]] = follow[nd->last[i]] + nd->first;

        }
        else if(str[i] == '.')
        {
            nd = createNode(str[i],0);
            nd->right = s.top(), s.pop();
            nd->left = s.top(), s.pop();
            nd->isNullable = nd->right->isNullable && nd->left->isNullable;
            

            if(nd->left->isNullable)
                nd->first = nd->right->first + nd->left->first;
            else
                nd->first = nd->left->first;

            
            if(nd->right->isNullable)
                nd->last = nd->right->last + nd->left->last;
            else
                nd->last = nd->right->last;

            
            for(int i=0;i<nd->left->last.size();i++)
                follow[nd->left->last[i]] = follow[nd->left->last[i]] + nd->right->first;

        }
        else
        {
            nd = createNode(str[i],0);
            nd->right = s.top(), s.pop();
            nd->left = s.top(), s.pop();
            nd->isNullable = nd->right->isNullable && nd->left->isNullable;
            nd->first = nd->right->first + nd->left->first;
            nd->last = nd->right->last + nd->left->last;
        }
        s.push(nd);
    }
    for(auto nd:chset)
        inStr.push_back(nd);
    
    printNode(nd);
    printf("Follow List:\n");
    for(int i = 1 ; i <= chCount ; i++)
    {
        cout<<i<<"       "<<chmap[i]<<"       "<<"{ ";
        for(int j = 0; j < follow[i].size() ; j++)
        {
            cout<<follow[i][j]<<" ";
        }
        cout<<" }\n";
    }
    createDFA(nd,inStr);
}
main()
{
	scanf("%s",ar);
	printf("%s\n\n",ar);
	string str=addDot();
	string str2=makePostfix(str);
    assignPos(str2);
}