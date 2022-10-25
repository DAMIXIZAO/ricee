#include <iostream>
#include <cstring>
using namespace std;
const int N=1e6+10;
int t,n;
char s[N];
int tr[N][26],tot,ne[N],e[N];
int q[N],hh,tt;
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
	int u=0,res=0;
	for(int i=1;s[i];i++)
	{
		u=tr[u][s[i]-'a'];
		for(int j=u;j&&e[j]!=-1;j=ne[j])
		{
			res+=e[j];
			e[j]=-1;
		}
	}
	return res;
}
int main(void)
{
	cin>>t;
	while(t--)
	{
		tot=0;
		memset(tr,0,sizeof tr);
		memset(ne,0,sizeof ne);
		memset(e,0,sizeof e);
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",s+1);
			insert(s);
		}
		build();
		scanf("%s",s+1);
		cout<<query(s)<<endl;
	}
	return 0;
} 
