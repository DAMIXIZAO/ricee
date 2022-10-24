#include <bits/stdc++.h>
using namespace std;
const int N=1e6+1,M=1e5+10;
int n;
char s[210][M];
int tr[N][26],tot,num,ne[N],ans[N],now[N],Map[N];
int q[N],hh,tt;
void insert(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		if(!tr[u][s[i]-'a']) tr[u][s[i]-'a']=++tot;
		u=tr[u][s[i]-'a']; 
		ans[u]++; 
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
int main(void)
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		insert(s[i]);
	}
	build();
	for(int i=tt-1;i>=0;i--)
	{
		ans[ne[q[i]]]+=ans[q[i]];
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[Map[i]]<<endl;
	}
	return 0;
}
