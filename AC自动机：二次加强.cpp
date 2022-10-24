#include <bits/stdc++.h> 
using namespace std;
const int N=200010,M=2000010;
char s[M];
int n;
int q[N],hh,tt;
int tr[N][26],tot,e[N],ne[N],ans[N],num;
int Map[N];
int st[N];
void insert(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
		u=tr[u][s[i]-'a'];
	}
	Map[++num]=u;
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
void query(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		u=tr[u][s[i]-'a'];
		ans[u]++;
	}
	for(int i=tt-1;i>=0;i--)
	{
		ans[ne[q[i]]]+=ans[q[i]];
	}
}
int main(void)
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		insert(s);
	}
	build();
	scanf("%s",s+1);
	query(s);
	for(int i=1;i<=n;i++)
	{
		cout<<ans[Map[i]]<<endl;
	}
	return 0;
}
