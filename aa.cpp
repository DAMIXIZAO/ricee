#include <bits/stdc++.h>
using namespace std;
const int N=100010,INF=0x3f3f3f3f;
int n,m;
int g[N],a[N],c[N];
int top,bot=INF,big;
map<int,int> hh;
int lowbit(int i)
{
	return i&(-i);
}
void add(int i)
{
	for(int j=i;j<=big;j+=lowbit(j))
	{
		c[j]++;
	}
}
int ask(int i)
{
	int ans=0;
	for(int j=i;j;j-=lowbit(j))
	{
		ans+=c[j];
	}
	return ans;
}
int main(void)
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>g[i],a[i]=g[i];
	sort(g+1,g+n+1);
	m=unique(g+1,g+n+1)-g-1;
	for(int i=1;i<=n;i++) 
	{
		int temp=a[i];
		a[i]=lower_bound(g+1,g+m+1,a[i])-g;
		big=max(big,a[i]);
		if(hh.count(a[i])==0) hh.insert({a[i],temp});
	}
	for(int i=1;i<=n;i++)
	{
		add(a[i]);
		top=max(top,a[i]);
		bot=min(bot,a[i]);
		if(i==1)
		{
			cout<<hh[a[i]]<<endl;
			continue;
		}
		if(i%2)
		{
			while(1)
			{
				int mid=(top+bot)/2;
				int temp=ask(mid);
				if(temp>=i/2+1)
				{
					if(mid==1) cout<<hh[1]<<endl;
					else
					{
						if(ask(mid-1)<i/2+1) 
						{
							cout<<hh[mid]<<endl;
							break;
						}
						else
						{
							top=mid;
						}
					}
				}
				else
				{
					bot=mid+1;
				}
			}
		}
	}
	return 0; 
}
