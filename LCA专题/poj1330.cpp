#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<vector>
typedef long long LL;

using namespace std;

const int maxn=1100;

vector<int>G[maxn];
int root,tot,n,m;
int cnt[maxn],vs[2*maxn],depth[2*maxn],id[maxn],dp[2*maxn][30],ans[maxn];

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


void dfs(int v,int p,int d)
{
    id[v]=tot;
    vs[tot]=v;
    depth[tot++]=d;
    for(int i=0;i<G[v].size();i++)
        if(G[v][i]!=p)
    {
        dfs(G[v][i],v,d+1);
        vs[tot]=v;
        depth[tot++]=d;
    }
}

int get_lca(int u,int v)
{
    return vs[get_rmq(min(id[u],id[v]),max(id[u],id[v]))];
}

void init_lca()
{int x,y,k;
    //scanf("%d",&n);
    memset(cnt,0,sizeof(cnt));
    memset(G,0,sizeof(G));
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        scanf(":(%d)",&k);
        //cout<<k<<endl;
        for(int j=1;j<=k;j++)
        {
            scanf("%d",&y);
            cnt[y]++;
            G[x].push_back(y);
            G[y].push_back(x);
        }
    }
    for(int i=1;i<=n;i++)if(cnt[i]==0)root=i;
    tot=0;
    dfs(root,-1,0);
    init_rmq();
    scanf("%d",&m);
    //cout<<"m="<<m<<endl;
    memset(ans,0,sizeof(ans));
    for(int i=1;i<=m;i++)
    {   scanf("%*[^(](%d %d)",&x,&y);
        int tmp=get_lca(x,y);
        ans[tmp]++;
    }
    for(int i=1;i<=n;i++)if(ans[i])
        printf("%d:%d\n",i,ans[i]);
    //cout<<"finish"<<endl;
    return ;
}

int main()
{int T;
    while(~scanf("%d",&n))
    init_lca();
}
