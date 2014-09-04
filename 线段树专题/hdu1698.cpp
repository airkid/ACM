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

const int maxn=100010;

LL data[maxn<<2],add[maxn<<2],chg[maxn<<2],num[maxn],delta;
int ul,ur,ql,qr,n,m;

void pushup(int l,int r,int rt)
{
    data[rt]=data[lch]+data[rch];
}

void pushdown(int l,int r,int rt)
{
    if(l==r)return ;
    if(~chg[rt])
    {
        chg[lch]=chg[rch]=chg[rt];
        data[lch]=chg[rt]*(mid-l+1);
        data[rch]=chg[rt]*(r-mid);
        chg[rt]=-1;
    }
    /*if(add[rt])
    {
        add[lch]+=add[rt];
        add[rch]+=add[rt];
        data[lch]+=add[rt]*(mid-l+1);
        data[rch]+=add[rt]*(r-mid);
        add[rt]=0;
    }*/
}

void build(int l=1,int r=n,int rt=1)
{
    //add[rt]=0;
    chg[rt]=-1;
    if(l==r)
    {
        data[rt]=1;
        return;
    }
    build(ll);build(rr);
    pushup(l,r,rt);
}

void update(int l=1,int r=n,int rt=1)
{
    if(ul<=l && r<=ur)
    {
        //add[rt]+=delta;
        chg[rt]=delta;
        data[rt]=delta*(r-l+1);
        return;
    }
    pushdown(l,r,rt);
    if(ul<=mid)update(ll);
    if(ur>mid)update(rr);
    pushup(l,r,rt);
}

LL query(int l=1,int r=n,int rt=1)
{
    if(ql<=l && qr>=r)
    {
        return data[rt];
    }
    pushdown(l,r,rt);
    LL tmp=0;
    if(ql<=mid)tmp+=query(ll);
    if(qr>mid)tmp+=query(rr);
    pushup(l,r,rt);
    return tmp;
}


void init()
{char s[20];
    //for(int i=1;i<=n;i++)scanf("%lld",&num[i]);
    scanf("%d%d",&n,&m);
    build();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%lld",&ul,&ur,&delta);
        update();
    }
    printf("%lld.\n",data[1]);
}

int main()
{int T;
    scanf("%d",&T);
    for(int k=1;k<=T;k++)
    {
        printf("Case %d: The total value of the hook is ",k);
        init();
    }
}
