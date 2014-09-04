#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
typedef long long LL;

using namespace std;

const int maxnode=3010;
const int maxsize=30;
const int maxn=1010;
const int maxm=30;

int ch[maxnode][maxsize],val[maxnode],sz,n;
char s[maxn][maxm];

int idx(char c){return c-'a';}

void insert(char *s)
{
    int u=0,len=strlen(s);
    for(int i=0;i<len;i++)
    {
        int c=idx(s[i]);
        if(!ch[u][c])
        {
            sz++;
            memset(ch[sz],0,sizeof(ch[sz]));
            val[sz]=1;
            ch[u][c]=sz;
        }
        else
        val[ch[u][c]]++;
        u=ch[u][c];
    }
    //val[u]=-1;
}

void solve(char *s)
{
    //cout<<s<<endl;
    int u=0,len=strlen(s);
    for(int i=0;i<len;i++)
    {
        int c=idx(s[i]);
        u=ch[u][c];
        if(val[u]==1 || i==len-1)
        {
            //cout<<i<<endl;
            printf("%s ",s);
            for(int j=0;j<=i;j++)printf("%c",s[j]);
            printf("\n");
            return ;
        }
    }
}


int main()
{
    memset(ch[0],0,sizeof(ch[0]));
    sz=0;
    int n=0;
    while(~scanf("%s",&s[n]))
    {
        insert(s[n]);
        n++;
    }
    /*cin>>n;
    for(int i=0;i<n;i++)
    {
        scanf("%s",&s[i]);
        insert(s[i]);
    }*/
    for(int i=0;i<n;i++)
        solve(s[i]);
}
