#include <bits/stdc++.h>
using namespace std;
const int N=1000010,M=2e5+10;
int n;
char s[160][80];
char t[N];
int ans[M];
int tr[M][26],tot,ne[M],Map[160],num;
int q[M],hh,tt;
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
void upd(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		u=tr[u][s[i]-'a'];
		for(int j=u;j;j=ne[j])
		{
			ans[j]++;
		}
	}
}
int main(void)
{
	while(cin>>n&&n)
	{
		num=0;
		tot=0;
		memset(tr,0,sizeof tr);
		memset(ne,0,sizeof ne);
		memset(ans,0,sizeof ans);
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s[i]+1);
			insert(s[i]);
		}
		build();
		scanf("%s",t+1);
		upd(t);
		int temp=0;
		for(int i=1;i<=n;i++) temp=max(temp,ans[Map[i]]);
		cout<<temp<<endl;
		for(int i=1;i<=n;i++)
		{
			if(ans[Map[i]]==temp) cout<<s[i]+1<<endl;
		}
	}
	return 0;
}
