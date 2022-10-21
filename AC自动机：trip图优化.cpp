#include <bits/stdc++.h>
using namespace std;
const int N=1000010;
int n;
int tr[N][26],tot,e[N];
char s[N];
int q[N],hh,tt;
int ne[N];
void insert(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
		u=tr[u][s[i]-'a'];
	}
	e[u]++;
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
int query(char * s)
{
	int u=0,ans=0;
	for(int i=1;s[i];i++)
	{
		u=tr[u][s[i]-'a'];
		for(int j=u;j&&e[j]!=-1;j=ne[j])
		{
			ans+=e[j];
			e[j]=-1;
		}
	}
	return ans;
}
int main(void)
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		insert(s);
	}
	scanf("%s",s+1);
	build();
	printf("%d\n",query(s));
	return 0;
} 
