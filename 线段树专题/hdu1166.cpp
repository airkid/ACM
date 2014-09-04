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

const int maxn=200010;

int num[maxn<<2],data[maxn<<2],ql,qr,p,delta,n,m;

int max(int a,int b)
{
    if(a>b)return a;return b;
}

void pushup(int rt)
{
    data[rt]=max(data[lch],data[rch]);
}

void build(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        data[rt]=num[l];
        return;
    }
    build(ll);build(rr);
    pushup(rt);
}

void update(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        data[rt]=delta;
        return ;
    }
    if(p<=mid)update(ll);
    else update(rr);
    pushup(rt);
}

int query(int l=1,int r=n,int rt=1)
{
    if(ql<=l && qr>=r)
    {
        return data[rt];
    }
    int tmp=0;
    if(ql<=mid)tmp=max(tmp,query(ll));
    if(qr>mid)tmp=max(tmp,query(rr));
    return tmp;
}

void init()
{char s[20];
    for(int i=1;i<=n;i++)scanf("%d",&num[i]);
    build();
    for(int i=1;i<=m;i++)
    {
        scanf("%s",&s);
        if(s[0]=='Q')
        {
            scanf("%d%d",&ql,&qr);
            printf("%d\n",query());
        }
        else
        {
            scanf("%d%d",&p,&delta);
            update();
        }
    }
}

int main()
{int T;
    while(~scanf("%d%d",&n,&m))
    {
        init();
    }
}
