#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#define lch (rt<<1)
#define rch (rt<<1|1)
#define mid ((l+r)>>1)
#define ll l , mid , lch
#define rr mid+1 , r , rch
typedef long long LL;
using namespace std;

const int maxn=500100;

LL maxl[maxn<<2],maxr[maxn<<2],maxd[maxn<<2],num[maxn],delta;
int ul,ur,ql,qr,n,m;

void pushup(int l,int r,int rt)
{
    maxl[rt]=maxl[lch];
    if(maxl[lch]==(mid-l+1))maxl[rt]=max(maxl[rt]+maxl[rch],maxl[rt]);
    maxr[rt]=maxr[rch];
    if(maxr[rch]=(r-mid))maxr[rt]=max(maxr[rt]+maxr[lch],maxr[rt]);
    maxd[rt]=max(maxd[lch],maxd[rch]);
    maxd[rt]=max(maxd[rt],maxr[lch]+maxl[rch]);
}

void build(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        maxl[rt]=maxr[rt]=maxd[rt]=num[l];
        return;
    }
    build(ll);build(rr);
    pushup(l,r,rt);
}

void query(int l=1,int r=n,int rt=1)
{
    if(ql<=l && qr>=r)
    {
        if(max)
    }
    if(ql<=mid)query(ll);
    if(qr>mid)query(rr);
}

void init()
{
    for(int i=1;i<=n;i++)scanf("%lld",&num[i]);
    for(int i=1;i<=m;i++)
    {
        ansl=n+1;ansr=-1;ans=0;
        scanf("%d%d",&ql,&qr);
    }
}

int main()
{
    while(~scanf("%d%d",&n,&m))
        init();
}
