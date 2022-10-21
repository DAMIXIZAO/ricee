#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
int q,m,tt;
struct 
{
	int l,r;
	ll num;
}t[N*4];
inline int read()
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
void build(int i,int l,int r)
{
	t[i].l=l,t[i].r=r,t[i].num=1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
}
void add(int i,int idx,int x)
{
	if(t[i].l==t[i].r)
	{
		t[i].num=x;
		return;
	}
	int mid=(t[i].l+t[i].r)>>1;
	if(idx<=mid) add(i<<1,idx,x);
	else add(i<<1|1,idx,x);
	t[i].num=t[i<<1].num*t[i<<1|1].num%m;
}
void sub(int i,int x)
{
	if(t[i].l==t[i].r)
	{
		t[i].num=1;
		return;
	}
	int mid=(t[i].l+t[i].r)>>1;
	if(x<=mid) sub(i<<1,x);
	else sub(i<<1|1,x);
	t[i].num=t[i<<1].num*t[i<<1|1].num%m;
}
ll ask(int i,int l,int r)
{
	if(l<=t[i].l&&t[i].r<=r)
	{
		return t[i].num;
	}
	int mid=(t[i].l+t[i].r)>>1;
	ll ans=1;
	if(l<=mid) ans=ans*ask(i<<1,l,r)%m;
	if(mid<r) ans=ans*ask(i<<1|1,l,r)%m;
	return ans;
}
int main(void)
{
	tt=read();
	while(tt--)
	{
		memset(t,0,sizeof t);
		q=read(),m=read();
		int a,b;
		int tim=q;
		build(1,1,q);
		while(q--)
		{
			a=read(),b=read();
			if(a==1)
			{
				add(1,tim-q,b);
				cout<<ask(1,1,tim-q)<<endl;
			}
			else
			{
				sub(1,b);
				cout<<ask(1,1,tim-q)<<endl;
			}
		}
	}
	return 0;
}
