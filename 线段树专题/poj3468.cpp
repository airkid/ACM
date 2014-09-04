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

const int maxn=500010;

LL data[maxn<<2],data1[maxn<<2],add[maxn<<2],add1[maxn<<2],num[maxn],d[maxn],delta;
int l[maxn],r[maxn];
int ul,ur,ql,qr,n,m,k;

void pushup(int l,int r,int rt)
{
    data[rt]=data[lch]+data[rch];
}
void pushup1(int l,int r,int rt)
{
    data1[rt]=data1[lch]+data1[rch];
}

void pushdown(int l,int r,int rt)
{
    if(l==r)return ;
    if(add[rt])
    {
        add[lch]+=add[rt];
        add[rch]+=add[rt];
        data[lch]+=add[rt]*(mid-l+1);
        data[rch]+=add[rt]*(r-mid);
        add[rt]=0;
    }
}

void pushdown1(int l,int r,int rt)
{
    if(l==r)return ;
    if(add1[rt])
    {
        add1[lch]+=add1[rt];
        add1[rch]+=add1[rt];
        data1[lch]+=add1[rt]*(mid-l+1);
        data1[rch]+=add1[rt]*(r-mid);
        add1[rt]=0;
    }
}

void build(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        data[rt]=num[l];
        add[rt]=0;
        return;
    }
    add[rt]=0;
    build(ll);build(rr);
    pushup(l,r,rt);
}

void build1(int l=1,int r=m,int rt=1)
{
    if(l==r)
    {
        data1[rt]=0;
        add1[rt]=0;
        return;
    }
    add1[rt]=0;
    build1(ll);build1(rr);
    pushup1(l,r,rt);
}

void update(int l=1,int r=n,int rt=1)
{
    if(ul<=l && r<=ur)
    {
        add[rt]+=delta;
        data[rt]+=delta*(r-l+1);
        return;
    }
    pushdown(l,r,rt);
    if(ul<=mid)update(ll);
    if(ur>mid)update(rr);
    pushup(l,r,rt);
}

void update1(int l=1,int r=m,int rt=1)
{
    if(ul<=l && r<=ur)
    {
        add1[rt]+=delta;
        data1[rt]+=delta*(r-l+1);
        return;
    }
    pushdown1(l,r,rt);
    if(ul<=mid)update1(ll);
    if(ur>mid)update1(rr);
    pushup1(l,r,rt);
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

LL query1(int l=1,int r=m,int rt=1)
{
    if(ql<=l && qr>=r)
    {
        return data1[rt];
    }
    pushdown1(l,r,rt);
    LL tmp=0;
    if(ql<=mid)tmp+=query1(ll);
    if(qr>mid)tmp+=query1(rr);
    pushup1(l,r,rt);
    return tmp;
}


void init()
{char s[20];
    for(int i=1;i<=n;i++)scanf("%lld",&num[i]);
    build();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%lld",&l[i],&r[i],&d[i]);
    }
    build1();
    for(int i=1;i<=k;i++)
    {
        scanf("%d%d",&ul,&ur);
        delta=1;
        update1();
    }
    for(int i=1;i<=m;i++)
    {
        ul=l[i];ur=r[i];ql=i;qr=i;
        delta=d[i]*query1();
        update();
    }
    for(int i=1;i<n;i++)
    {
        ql=qr=i;
        printf("%lld ",query());
    }
    ql=qr=n;
    printf("%lld\n",query());
}

int main()
{
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        init();
    }
}
