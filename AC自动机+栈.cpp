#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
const int N=100010;
int n;
char T[N];
int t[N];
char s[N][50];
int tr[N][26],tot,num,ne[N],g[N],e[N],sum;
int q[N],hh,tt;
PII stk[N];
int top;
void insert(char * s)
{
	int u=0;
	int i=1;
	for(i;s[i];i++)
	{
		if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
		u=tr[u][s[i]-'a'];
	}
	e[u]=i-1;
}
void build()
{
	hh=0,tt=0;
	for(int i=0;i<26;i++)
	{
		if(tr[0][i]) q[tt++]=tr[0][i];
	}
	while(hh<tt)
	{
		int u=q[hh++];
		for(int i=0;i<26;i++)
		{
			if(tr[u][i])
			{
				ne[tr[u][i]]=tr[ne[u]][i];
				q[tt++]=tr[u][i];
			}
			else
			{
				tr[u][i]=tr[ne[u]][i];
			}
		}
	}
}
void upd(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		u=tr[u][s[i]-'a'];
		g[i]=u;
		stk[++top]={i,g[i]};
		if(e[u])
		{
			int len=e[u];
			while(len)
			{
				top--;
				len--;
			}
			if(!top) u=0;
			else u=stk[top].second;
		}
	}
}
int main(void)
{
	scanf("%s",T+1);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		insert(s[i]);
	}
	build();
	upd(T);
	int flag=0;
	int ff=0;
//	for(int i=1;T[i];i++) cout<<t[i]<<" ";
//	cout<<endl;
	for(int i=1;i<=top;i++)
	{
		cout<<T[stk[i].first];
	}
	return 0;
} 
