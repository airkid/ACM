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

const int maxn=5010;

int data[maxn<<2],a[maxn],ql,qr,p,delta,n;

void pushup(int rt)
{
    //data[rt]=max(data[lch],data[rch]);
    data[rt]=data[lch]+data[rch];
}

void build(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        data[rt]=0;
        return;
    }
    build(ll);build(rr);
    pushup(rt);
}

void update(int l=1,int r=n,int rt=1)
{
    if(l==r)
    {
        //data[rt]=delta;
        data[rt]+=delta;
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
    //if(ql<=mid)tmp=max(tmp,query(ll));
    //if(qr>mid)tmp=max(tmp,query(rr));
    if(ql<=mid)tmp+=query(ll);
    if(qr>mid)tmp+=query(rr);
    return tmp;
}

int min(int a,int b)
{
    if(a<b)return a;return b;
}

void init()
{
    build();
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        a[i]++;
        ql=a[i]+1;qr=n;
        sum+=query();
        p=a[i];delta=1;
        update();
    }
    int ans=sum;
    for(int i=1;i<=n;i++)
    {
        a[i]--;
        sum+=-a[i]+n-a[i]-1;
        ans=min(ans,sum);
    }
    printf("%d\n",ans);
}

int main()
{
    while(~scanf("%d",&n))
    {
        init();
    }
}
