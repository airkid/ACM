#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>

using namespace std;

const int maxn=1000100;

char s1[maxn],s2[maxn];
int f[maxn];

void getfail(char* P,int* f)
{
    int m = strlen(P);
    f[0]=0;f[1]=0;
    for(int i=1;i<m;i++)
    {
        int j=f[i];
        while(j && P[i]!=P[j]) j=f[j];
        f[i+1]= P[i]==P[j] ? j+1:0;
    }
}

int kmp(char* T,char* P,int* f)
{int ans=0;
    int n=strlen(T),m=strlen(P);
    getfail(P,f);
    int j=0;
    for(int i=0;i<n;i++)
    {
        while(j && P[j]!=T[i])j=f[j];
        if(P[j]==T[i]) j++;
        if(j==m)ans++;
    }
    return ans;
}

int main()
{int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%s",&s2,&s1);
        printf("%d\n",kmp(s1,s2,f));
    }
}
