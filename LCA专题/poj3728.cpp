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

vector<int>G[maxn];
int fa[MAX_LOG_V+10][maxn],depth[maxn],cnt[maxn];
int n,m,root,cost[maxn],maxd[MAX_LOG_V+10][maxn],mind[MAX_LOG_V+10][maxn],up[MAX_LOG_V+10][maxn],down[MAX_LOG_V+10][maxn];

void dfs(int v,int p,int step)
{
    fa[0][v]=p;
    depth[v]=step;
    maxd[0][v]=max(cost[v],cost[p]);
    mind[0][v]=min(cost[v],cost[p]);
    up[0][v]=max(0,cost[p]-cost[v]);
    down[0][v]=max(0,cost[v]-cost[p]);
    for(int i=0;i<G[v].size();i++)if(G[v][i]!=p)
    {
        dfs(G[v][i],v,step+1);
    }
}

void make_st()
{
    for(int k=0;k+1<MAX_LOG_V;k++)
    for(int v=1;v<=n;v++)
    {
        fa[k+1][v]=fa[k][fa[k][v]];
        maxd[k+1][v]=max(maxd[k][v],maxd[k][fa[k][v]]);
        mind[k+1][v]=min(mind[k][v],mind[k][fa[k][v]]);
        up[k+1][v]=
        max(max(up[k][v],up[k][fa[k][v]]),maxd[k][fa[k][v]]-mind[k][v]);
        down[k+1][v]=
        max(max(down[k][v],down[k][fa[k][v]]),maxd[k][v]-mind[k][fa[k][v]]);
    }
}

int get_lca(int u,int v)
{
    if(depth[u]>depth[v])swap(u,v);
    for(int k=0;k<MAX_LOG_V;k++)
        if((depth[v]-depth[u])>>k & 1)
    {
        v=fa[k][v];
    }
    if(u==v)return u;
    for(int k=MAX_LOG_V-1;k>=0;k--)
    {
        if(fa[k][u]!=fa[k][v])
        {
            u=fa[k][u];
            v=fa[k][v];
        }
    }
    return fa[0][u];
}

int solve(int x,int z,int y)
{
    //cout<<x<<' '<<y<<' '<<z<<endl;
    int delta=depth[x]-depth[z];
    int tmp1=cost[x];
    int ans=0;
    for(int k=MAX_LOG_V;k>=0;k--)
        if(delta>>k&1)
    {
        ans=max(ans,maxd[k][x]-tmp1);
        tmp1=min(tmp1,mind[k][x]);
        ans=max(ans,up[k][x]);
        x=fa[k][x];
    }
    delta=depth[y]-depth[z];
    int tmp2=cost[y];
    for(int k=MAX_LOG_V;k>=0;k--)
        if(delta>>k&1)
    {
        ans=max(ans,tmp2-mind[k][y]);
        tmp2=max(tmp2,maxd[k][y]);
        ans=max(ans,down[k][y]);
        y=fa[k][y];
    }
    return max(ans,tmp2-tmp1);
}

void init_lca()
{int x,y,z;
    memset(cnt,0,sizeof(cnt));
    memset(G,0,sizeof(G));
    for(int i=1;i<=n;i++)scanf("%d",&cost[i]);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
        cnt[y]++;
    }
    for(int i=1;i<=n;i++)if(cnt[i]==0)root=i;
    dfs(1,1,1);
    make_st();
    //for(int k=0;k<=2;k++)for(int i=1;i<=n;i++)cout<<k<<' '<<i<<' '<<up[k][i]<<' '<<down[k][i]<<' '<<maxd[k][i]<<' '<<mind[k][i]<<endl;
    //for(int k=0;k<=4;k++)for(int i=1;i<=n;i++)cout<<i<<' '<<k<<' '<<fa[k][i]<<endl;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        int z=get_lca(x,y);
        int ans=solve(x,z,y);
        printf("%d\n",ans);
    }
}

int main()
{int T=0;
    while(~scanf("%d",&n))
    {
        init_lca();
    }
}
