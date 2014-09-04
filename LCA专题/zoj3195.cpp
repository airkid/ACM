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

vector<int>G[maxn];
vector<int>W[maxn];
int root,tot,n,m;
int cnt[maxn],vs[2*maxn],depth[2*maxn],id[maxn],dp[2*maxn][30],s[2*maxn],fa[maxn];

int get_rmq(int L,int H)
{
    int k=0;while((1<<(k+1))<=H-L+1)k++;
    if(depth[dp[L][k]]<depth[dp[H-(1<<k)+1][k]])
        return dp[L][k];
    else
        return dp[H-(1<<k)+1][k];
}

void init_rmq()
{
    int temp=0;while((1<<(temp+1))<=n*2-2)temp++;
    for(int i=0;i<=n*2-2;i++)dp[i][0]=i;
    for(int j=1;j<=temp;j++)
    for(int i=0;i<=n*2-2;i++)
    if(i+(1<<j)-1<=n*2-2)
    {
        if(depth[dp[i][j-1]]<depth[dp[i+(1<<(j-1))][j-1]])
        dp[i][j]=dp[i][j-1];
        else
        dp[i][j]=dp[i+(1<<(j-1))][j-1];
    }
}


void dfs(int v,int p,int d,int sum)
{
    id[v]=tot;
    vs[tot]=v;
    s[tot]=sum;
    depth[tot++]=d;
    for(int i=0;i<G[v].size();i++)
        if(G[v][i]!=p)
    {
        if(fa[G[v][i]]==0)
        {
            fa[G[v][i]]=p;
            dfs(G[v][i],v,d+1,sum+W[v][i]);
        }
        else
        {
            dfs(G[v][i],v,d+1,sum-W[v][i]);
        }
        vs[tot]=v;
        s[tot]=sum;
        depth[tot++]=d;
    }
}

int get_lca(int u,int v)
{
    int lca=vs[get_rmq(min(id[u],id[v]),max(id[u],id[v]))];
    return s[id[u]]-s[id[lca]]+s[id[v]]-s[id[lca]];
}

void init_lca()
{int x,y,z;
    memset(cnt,0,sizeof(cnt));
    memset(fa,0,sizeof(fa));
    memset(G,0,sizeof(G));
    memset(W,0,sizeof(W));
    s[0]=0;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        x++;y++;
        cnt[y]++;
        G[x].push_back(y);
        W[x].push_back(z);
        G[y].push_back(x);
        W[y].push_back(z);
    }
    for(int i=1;i<=n;i++)if(cnt[i]==0)root=i;
    tot=0;
    fa[root]=-1;
    dfs(root,-1,0,0);
    init_rmq();
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        x++;y++;z++;
        printf("%d\n",(get_lca(x,y)+get_lca(y,z)+get_lca(z,x))/2);
    }
}

int main()
{int T=0;
    while(~scanf("%d",&n))
    {
        T++;if(T>1)printf("\n");
        init_lca();
    }
}
