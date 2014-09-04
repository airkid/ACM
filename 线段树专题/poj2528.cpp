#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#define lch (rt<<1)
#define rch (rt<<1|1)
#define mid ((l+r)>>1)
#define ll l , mid , lch
#define rr mid+1 , r , rch
typedef long long LL;
using namespace std;

const int maxn=200100;

LL data[maxn<<2],chg[maxn<<2],delta;
bool vis[maxn];
int ul,ur,ql,qr,n,m;

struct node
{
    int l,r,pos;
};

node a[maxn];
set<int>st;
set<int>::iterator it;
map<int,int>mp;

void pushup(int l,int r,int rt)
{
    if(data[lch]==data[rch] && data[lch]!=0)
    data[rt]=data[lch];
    else data[rt]=0;
}

void pushdown(int l,int r,int rt)
{
    if(l==r)return;//判断叶子节点防止越界
    if(~chg[rt])
    {
        chg[lch]=chg[rch]=chg[rt];
        data[lch]=chg[rt];
        data[rch]=chg[rt];
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
    data[rt]=0;
    if(l==r)
    {
        //data[rt]=0;
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
        //date[rt]+=delta(r-l+1);
        data[rt]=delta;
        chg[rt]=delta;
        return;
    }
    pushdown(l,r,rt);
    if(ul<=mid)update(ll);
    if(ur>mid)update(rr);
    pushup(l,r,rt);
}

void query(int l=1,int r=n,int rt=1)
{
    if(data[rt]!=0)
    {
        vis[data[rt]]=true;
        return;
    }
    if(l==r)return ;
    pushdown(l,r,rt);
    query(ll);query(rr);
    pushup(l,r,rt);
}

void init()
{
    scanf("%d",&m);
    st.clear();mp.clear();
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a[i].l,&a[i].r);
        a[i].pos=i;
        st.insert(a[i].l);st.insert(a[i].r);
    }
    int cnt=0;int pre=-1;
    for(it=st.begin();it!=st.end();it++)
    {
        if(pre!=-1 && pre+1!=*it)cnt++;
        cnt++;mp[*it]=cnt;
        pre=*it;
    }
    n=cnt;
    build();
    for(int i=1;i<=m;i++)
    {
        ul=mp[a[i].l];ur=mp[a[i].r];
        delta=a[i].pos;
        //cout<<ul<<' '<<ur<<' '<<delta<<endl;
        update();
    }
    memset(vis,0,sizeof(vis));
    query();
    int ans=0;
    for(int i=1;i<=m;i++)if(vis[i])ans++;
    printf("%d\n",ans);
}

int main()
{int T;
    scanf("%d",&T);
    while(T--)
    {
        init();
    }
}
