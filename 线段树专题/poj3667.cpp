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

const int maxn=50100;

LL minl[maxn<<2],minr[maxn<<2],mind[maxn<<2],chg[maxn<<2],delta,len;
int ul,ur,ql,qr,n,m;

void pushup(int l,int r,int rt)
{
    minl[rt]=minl[lch];
    if(minl[lch]==(mid-l+1))minl[rt]+=minl[rch];
    minr[rt]=minr[rch];
    if(minr[rch]==(r-mid))minr[rt]+=minr[lch];
    mind[rt]=max(mind[lch],mind[rch]);
    mind[rt]=max(mind[rt],minr[lch]+minl[rch]);
}

void pushdown(int l,int r,int rt)
{
    if(l==r)return;//判断叶子节点防止越界
    if(~chg[rt])
    {
        chg[lch]=chg[rch]=chg[rt];
        minl[lch]=minr[lch]=mind[lch]=chg[rt]*(mid-l+1);
        minl[rch]=minr[rch]=mind[rch]=chg[rt]*(r-mid);
        chg[rt]=-1;
    }
}

void build(int l=1,int r=n,int rt=1)
{
    chg[rt]=-1;
    if(l==r)
    {
        minl[rt]=minr[rt]=mind[rt]=(r-l)+1;
        return;
    }
    build(ll);build(rr);
    pushup(l,r,rt);
}

void update(int l=1,int r=n,int rt=1)
{
    if(ul<=l && r<=ur)
    {
        chg[rt]=delta;
        minl[rt]=minr[rt]=mind[rt]=delta*(r-l+1);
        return;
    }
    pushdown(l,r,rt);
    if(ul<=mid)update(ll);
    if(ur>mid)update(rr);
    pushup(l,r,rt);
}

LL query(int l=1,int r=n,int rt=1)
{
    if(minl[rt]>=len)
    {
        return l;
    }
    pushdown(l,r,rt);
    if(mind[lch]>=len)return query(ll);
    else if(minr[lch]+minl[rch]>=len)return mid-minr[lch]+1;
    else return query(rr);
}

void init()
{int x;
    build();
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&x);
        if(x==1)
        {
            scanf("%lld",&len);
            if(mind[1]>=len)
            {
                int p=query();
                printf("%d\n",p);
                ul=p;ur=p+len-1;delta=0;
                update();
            }
            else printf("0\n");
        }
        else
        {
            scanf("%d%d",&ul,&ur);
            ur=ul+ur-1;
            delta=1;
            update();
        }
    }
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        init();
    }
}
