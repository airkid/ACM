#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
typedef long long LL;

using namespace std;

const int maxn=50010;
const int MAX_LOG_V=30;

vector<int>G;
vector<int>W;
int fa[MAX_LOG_V+10][maxn],s[MAX_LOG_V+10][maxn],depth[maxn],cnt[maxn];
int n,m,root;

void dfs(int v,int p,int step,int len)
{
    fa[0][v]=p;
    depth[v]=step;
    s[0][v]=len;
    for(int i=0;i<G[v].size();i++)if(G[v][i]!=p)
    {
        dfs(G[v][i],v,step+1,W[v][i]);
    }
}

void make_st()
{
    for(int k=0;k+1<MAX_LOG_V;k++)
    for(int v=1;v<=n;v++)
    if(fa[k][v]<0)
    {
        fa[k+1][v]=-1;
        s[k+1][v]=s[k][v];
    }
    else
    {
        fa[k+1][v]=fa[k][fa[k][v]];
        s[k+1][v]=s[k][v]+s[k][fa[k][v]];
    }
}

int get_lca(int u,int v)
{int sum=0;
    if(depth[u]>depth[v])swap(u,v);
    for(int k=0;k<MAX_LOG_V;k++)
        if((depth[v]-depth[u])>>k & 1)
    {
        v=fa[k][v];sum+=s[k][v];
    }
    if(u==v)return sum;
    for(int k=MAX_LOG_V-1;k>=0;k--)
    {
        if(fa[k][u]!=fa[k][v])
        {
            u=fa[k][u];
            v=fa[k][v];
            sum+=s[k][u]+s[k][v];
        }
    }
    return sum;
}

void init_lca()
{
    memset(cnt,0,sizeof(cnt));
    memset(G,0,sizeof(G));
    memset(W,0,sizeof(W));
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        x++;y++;
        G[x].push_back(y);
        W[x].push_back(z);
        G[y].push_back(x);
        W[y].push_back(z);
        cnt[y]++;
    }
    for(int i=1;i<=n;i++)if(cnt[i]==0)root=i;
    dfs(root,-1,0,0);
    make_st();
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        x++;y++;z++;
        printf("%d\n",(get_lca(x,y)+get_lca(y,z)+get_lca(y,x))/2);
    }
}

int main()
{
    while(~scanf("%d",&n))
        init_lca();
}
