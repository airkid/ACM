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

using namespace std;

const int maxn=200100;

int data[maxn<<2],w,h,n,len,m;

void pushup(int rt)
{
    data[rt]=max(data[lch],data[rch]);
    //data[rt]=data[lch]+data[rch];
}

void build(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        data[rt]=w;
        return;
    }
    build(ll);build(rr);
    pushup(rt);
}

int query(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        data[rt]-=len;
        return l;
    }
    int tmp=0;
    if(data[lch]>=len)tmp= query(ll);
    else tmp= query(rr);
    pushup(rt);
    return tmp;
}


void init()
{
    build();
}

int main()
{
    while(~scanf("%d%d%d",&h,&w,&m))
    {
        n=min(h,m);
        init();
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&len);
            if(data[1]<len)
                printf("-1\n");
            else printf("%d\n",query());
        }
    }
}
