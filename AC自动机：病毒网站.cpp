#include <iostream>
#include <cstring>
using namespace std;
const int N=2e6+10;
int n,t;
char s[1010][60];
char T[N];
int tr[70000][26],tot,num,ne[70000],Map[70000],ans[70000];
int q[N],hh,tt;
void insert(char * s)
{
	int u=0;
	for(int i=1;s[i];i++)
	{
		if(!tr[u][s[i]-'A']) tr[u][s[i]-'A']=++tot;
		u=tr[u][s[i]-'A'];
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
		if(s[i]<'A'||s[i]>'Z')
		{
			u=0;
			continue;
		}
		u=tr[u][s[i]-'A'];
		ans[u]++;
	}
	for(int i=tt-1;i>=0;i--)
	{
		ans[ne[q[i]]]+=ans[q[i]];
	}
}
int main(void)
{
	while(scanf("%d",&n)!=EOF)
	{
		num=0,tot=0;
		memset(s,0,sizeof s);
		memset(tr,0,sizeof tr);
		memset(ne,0,sizeof ne);
		memset(ans,0,sizeof ans);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		insert(s[i]);
	}
	build();
	scanf("%s",T+1);
	upd(T);
	for(int i=1;i<=n;i++)
	{
		if(ans[Map[i]]) cout<<s[i]+1<<": "<<ans[Map[i]]<<endl;
	}
}
	return 0;
}
