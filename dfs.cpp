#include <bits/stdc++.h>
using namespace std;
long int n,e;
int d[100000],f[100000];
int pr[100000];
int t;
char color[100000];
vector <int> g[100000],m;
void build()
{
    int p,i,q;
    for(i=0;i<e;i++)
    {
        scanf("%d %d",&p,&q);
        g[p].push_back(q);
        
    }

}
void print_path(int dest)
{
    printf("path-> ");
    for(int i=0;i<m.size();i++)
    {
        printf("%d ",m[i]);
    }
    printf("%d\n",dest );

}
void DFS(int u, int dest)
{

        int k,i,j;
        m.push_back(u);

        for(j=0;j<g[u].size();j++)
        {
            k=g[u][j];

            if(k==dest)
                print_path(dest);
            
            pr[k]=u;
            DFS(k,dest);

            
        }
        m.pop_back();
       
}
main()
{
    int i;
    scanf("%ld",&n);
    scanf("%ld",&e);
    build();

    int src , dest;
    scanf("%d %d",&src,&dest);

    DFS(src,dest);
    
}
