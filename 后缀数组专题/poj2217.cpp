#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
typedef long long LL;

using namespace std;

const int maxn=300100;

char s[maxn],t[maxn];
int sa[maxn],lcp[maxn],Rank[maxn],n,k,t1[maxn],t2[maxn],c[maxn];


void build_sa(int m){
    int i, *x=t1,*y=t2;
    for (i=0;i<m;i++) c[i]=0;
    for (i=0;i<n;i++) c[x[i]=s[i]]++;
    for (i=1;i<m;i++) c[i]+=c[i-1];
    for (i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for (int k=1;k<=n;k<<=1){
        int p=0;
        for (i=n-k;i<n;i++) y[p++]=i;
        for (i=0;i<n;i++) if (sa[i]>=k)  y[p++]=sa[i]-k;
        for (i=0;i<m;i++) c[i]=0;
        for (i=0;i<n;i++) c[x[y[i]]]++;
        for (i=0;i<m;i++) c[i]+=c[i-1];
        for (i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1; x[sa[0]]=0;
        for (i=1;i<n;i++)
            x[sa[i]]=y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1:p++;
        if (p>=n) break;
        m=p;
    }
}


bool sa_cmp(int i,int j)
{
    if(Rank[i]!=Rank[j])return Rank[i]<Rank[j];
    int ri=i+k<=n?Rank[i+k]:-1;
    int rj=j+k<=n?Rank[j+k]:-1;
    return ri<rj;
}

void con_sa(char *s,int *sa)
{int tmp[maxn];
    for(int i=0;i<=n;i++)
    {
        sa[i]=i;
        Rank[i]=i<n?s[i]:-1;
    }
    for(k=1;k<=n;k*=2)
    {
        sort(sa,sa+n+1,sa_cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<=n;i++)
            tmp[sa[i]]=tmp[sa[i-1]]+
            (sa_cmp(sa[i-1],sa[i])?1:0);
        for(int i=0;i<=n;i++)
            Rank[i]=tmp[i];
    }
}


void construct_lcp()
{
    int i,j,k=0;
    for (i=0;i<n;i++) Rank[sa[i]]=i;
    for (i=0;i<n;i++) {
        if (k) k--;
        if (Rank[i]==0){
            lcp[Rank[i]]=0;
            continue;
        }
        int j =sa[Rank[i]-1];
        while (s[i+k]==s[j+k]) k++;
        lcp[Rank[i]]=k;
    }
}

int main()
{char c;int T;
    scanf("%d",&T);
    while(~scanf("%s",&s))
    {
        scanf("%s",&t);
        int len=strlen(s);
        n =len+1+strlen(t);
        strcpy(s+len+1,t);
        s[len]=1;
        //con_sa(s,sa);
        build_sa(300);
        //for(int i=0;i<n;i++)cout<<sa[i]<<' ';cout<<endl;
        construct_lcp();
        //for(int i=0;i<n;i++)cout<<lcp[i]<<' ';cout<<endl;
        int ans=0;
        for(int i=1;i<n;i++)
            if((sa[i]<len)!=(sa[i-1]<len))
            ans=max(ans,lcp[i]);
        printf("%d\n",ans);
    }
}
