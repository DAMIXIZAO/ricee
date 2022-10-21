#include <bits/stdc++.h>
using namespace std;
const int N=100010;
int n1,n2;
int m1[N],m2[N];
int top;
int c[N],s[N],h[N];
inline int re()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int lowbit(int i)
{
	return i&(-i);
}
void add(int i,int x)
{
	for(int j=i;j<=n1+n2;j+=lowbit(j))
	{
		c[j]+=x;
	}
}
long long ask(int i)
{
	long long ans=0;
	for(int j=i;j;j-=lowbit(j))
	{
		ans+=c[j];
	}
	return ans;
}
int main(void)
{
	n1=re(),n2=re();
	for(int i=n1;i>=1;i--)
	{
		m1[i]=re();
	}
	for(int i=1;i<=n2;i++)
	{
		m2[i]=re();
	}
	for(int i=1;i<=n1;i++) s[i]=m1[i];
	for(int i=1;i<=n2;i++) s[i+n1]=m2[i];
	sort(s+1,s+1+n1+n2);
	for(int i=1;i<=n1;i++) m1[i]=lower_bound(s+1,s+n1+n2+1,m1[i])-s;
	for(int i=1;i<=n2;i++) m2[i]=lower_bound(s+1,s+n1+n2+1,m2[i])-s;
	for(int i=1;i<=n1;i++) h[m1[i]]=i;
	for(int i=1;i<=n2;i++) h[m2[i]]=i+n1;
	for(int i=1;i<=n1+n2;i++) add(i,1);
	int l=n1,r=n1+1;
	long long ans=0;
	for(int i=n1+n2;i>1;i--)
	{
		int top=h[i];
		if(top<=l)
		{
			ans+=ask(l)-ask(top);
		}
		else 
		{
			ans+=ask(top)-ask(r);
			if(i!=n1+n2) ans-=1;
		}
		l=r=top;
		add(top,-1);
	}
	cout<<ans<<endl;
	return 0;
}
