#include <bits/stdc++.h>
using namespace std;
int n,e;
int key[100005];
int pr[100005],taken[100005]={0};
vector <int> g[100005],w[100005];

struct element{
    int node, cost;
    element(int n, int c){
        node = n;
        cost = c;
    }
    bool operator <(const element &a)const
    {
        return cost < a.cost;
    }
    bool operator >(const element &a)const
    {
        return cost > a.cost;
    }
};
priority_queue<element, vector<element>, greater<element> > qu;
void ucs(int r)
{
    key[r]=0;
    pr[r]=10000;
    taken[r]=1;
    qu.push(element(r,0));
    int k,p;
    while(!qu.empty())
    {
        element temp=qu.top();
        qu.pop();
        p=temp.node;
        taken[p]=1;
        for(int i=0;i<g[p].size();i++)
        {
            k=g[p][i];
            if(taken[k]==0 && w[p][i]+key[p]<key[k])
            {
                key[k]=w[p][i]+key[p];
                pr[k]= p;
                qu.push(element(k,key[k]));
            }
        }

    }
}

void print_path(int dest)
{   
    if(pr[dest] != 10000)
    {
        dest= pr[dest];
        print_path(dest);
        printf("%d ",dest);
    }
}
main()
{
    int p,q,path;
    scanf("%d %d",&n,&e);
    for(int i=0;i<e;i++)
    {
        scanf("%d %d %d",&p,&q,&path);
        g[p].push_back(q);
        //g[q].push_back(p);
        w[p].push_back(path);
        //w[q].push_back(path);
    }
    for(int i=0;i<n;i++)
    {
        key[i]=10000;
        pr[i]=10000;
    }
    int src , dest;
    scanf("%d %d",&src,&dest);

    ucs(src);

    printf("%d\n",key[dest]);
    printf("path -> " );
    print_path(dest);
    printf("%d\n",dest );

}

