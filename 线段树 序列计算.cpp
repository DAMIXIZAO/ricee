#include <bits/stdc++.h>
using namespace std;
const int N=200010;
struct tree
{
	int l,r;
	int num,numa,numb,lna,rna,lnb,rnb,lazy,rev;
}t[N*4];
int n,m;
int a[N];
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
void genx(int i)
{
	t[i].num=t[i<<1].num+t[i<<1|1].num;
	t[i].numa=max(max(t[i<<1].numa,t[i<<1|1].numa),t[i<<1].rna+t[i<<1|1].lna);
	if(t[i<<1].lna==t[i<<1].r-t[i<<1].l+1) t[i].lna=t[i<<1].lna+t[i<<1|1].lna;
	else t[i].lna=t[i<<1].lna;
	if(t[i<<1|1].rna==t[i<<1|1].r-t[i<<1|1].l+1) t[i].rna=t[i<<1|1].rna+t[i<<1].rna;
	else t[i].rna=t[i<<1|1].rna;
	t[i].numb=max(max(t[i<<1].numb,t[i<<1|1].numb),t[i<<1].rnb+t[i<<1|1].lnb);
	if(t[i<<1].lnb==t[i<<1].r-t[i<<1].l+1) t[i].lnb=t[i<<1].lnb+t[i<<1|1].lnb;
	else t[i].lnb=t[i<<1].lnb;
	if(t[i<<1|1].rnb==t[i<<1|1].r-t[i<<1|1].l+1) t[i].rnb=t[i<<1|1].rnb+t[i<<1].rnb;
	else t[i].rnb=t[i<<1|1].rnb;
}
void build(int i,int l,int r)
{
	t[i].l=l,t[i].r=r,t[i].lazy=-1;
	if(l==r)
	{
		t[i].num=t[i].numa=t[i].lna=t[i].rna=a[l];
		t[i].numb=t[i].lnb=t[i].rnb=1-a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	genx(i);
}
void put(int i)
{
    if(t[i].lazy != -1)
	{//优先级最高
		t[i].rev = 0;//清空标记
        int val = t[i].lazy;
        t[i<<1].num = (t[i<<1].r - t[i<<1].l + 1) * val;
        t[i<<1|1].num = (t[i<<1|1].r - t[i<<1|1].l + 1) * val;
        
        t[i<<1].lazy = t[i<<1|1].lazy = val;
		t[i<<1].rev = t[i<<1|1].rev = 0;
        if(val==1)
        {
        	t[i<<1].numa=t[i<<1].lna=t[i<<1].rna=t[i<<1].r-t[i<<1].l+1;
    		t[i<<1].numb=t[i<<1].lnb=t[i<<1].rnb=0;
         	t[i<<1|1].numa=t[i<<1|1].lna=t[i<<1|1].rna=t[i<<1|1].r-t[i<<1|1].l+1;
    		t[i<<1|1].numb=t[i<<1|1].lnb=t[i<<1|1].rnb=0;   		
        }
        else
        {
        	t[i<<1].numa=t[i<<1].lna=t[i<<1].rna=0;
    		t[i<<1].numb=t[i<<1].lnb=t[i<<1].rnb=t[i<<1].r-t[i<<1].l+1;
         	t[i<<1|1].numa=t[i<<1|1].lna=t[i<<1|1].rna=0;
    		t[i<<1|1].numb=t[i<<1|1].lnb=t[i<<1|1].rnb=t[i<<1|1].r-t[i<<1|1].l+1;         	
        }
		t[i].lazy = -1;
    }
    if(t[i].rev)
	{
        t[i<<1].num = (t[i<<1].r - t[i<<1].l + 1) - t[i<<1].num;
        t[i<<1|1].num = (t[i<<1|1].r - t[i<<1|1].l + 1) - t[i<<1|1].num;
        
        if(t[i<<1].lazy != -1)t[i<<1].lazy ^= 1;//综合考虑优先级， 对其他标记的影响
		else t[i<<1].rev ^= 1;
		if(t[i<<1|1].lazy != -1)t[i<<1|1].lazy ^= 1;
		else t[i<<1|1].rev ^= 1;
        
        swap(t[i<<1].numa, t[i<<1].numb);
        swap(t[i<<1].lnb, t[i<<1].lna);
        swap(t[i<<1].rnb, t[i<<1].rna);
        
        swap(t[i<<1|1].numa, t[i<<1|1].numb);
        swap(t[i<<1|1].lnb, t[i<<1|1].lna);
        swap(t[i<<1|1].rnb, t[i<<1|1].rna);
		
		t[i].rev = 0;
    }
}
void upd(int i,int l,int r,int x)
{
	if(l==t[i].r&&t[i].r==r)
	{
		if(x==0)
		{
			t[i].num=t[i].numa=t[i].lna=t[i].rna=0;
			t[i].numb=t[i].lnb=t[i].rnb=t[i].r-t[i].l+1;
			t[i].lazy=0;
		}
		else
		{
			t[i].num=t[i].numa=t[i].lna=t[i].rna=t[i].r-t[i].l+1;
			t[i].numb=t[i].lnb=t[i].rnb=0;
			t[i].lazy=1;
		}
		return;
	}
	put(i);
	int mid=(t[i].l+t[i].r)>>1;
	if(mid<l) upd(i<<1|1,l,r,x);
	else if(mid>=r) upd(i<<1,l,r,x);
	else upd(i<<1,l,mid,x),upd(i<<1|1,mid+1,r,x);
	genx(i);
}
void change(int i,int l,int r)
{
	if(l==t[i].l&&t[i].r==r)
	{
		t[i].num=t[i].r-t[i].l+1-t[i].num;
		swap(t[i].numa,t[i].numb);
		swap(t[i].lna,t[i].lnb);
		swap(t[i].rna,t[i].rnb);
		t[i].rev^=1;
		return;
	}
	int mid=(t[i].l+t[i].r)>>1;
	put(i);
	if(mid<l) change(i<<1|1,l,r);
	else if(mid>=r) change(i<<1,l,r);
	else change(i<<1,l,mid),change(i<<1|1,mid+1,r);
	genx(i);
}
int ask(int i,int l,int r)
{
	if(l==t[i].l&&t[i].r==r)
	{
		return t[i].num;
	}
	put(i);
	int mid=(t[i].l+t[i].r)>>1;
	if(mid<l) return ask(i<<1|1,l,r);
	else if(mid>=r) return ask(i<<1,l,r);
	else return ask(i<<1,l,mid)+ask(i<<1|1,mid+1,r);
}
tree query(int i,int l,int r)
{
	if(l==t[i].l&&t[i].r==r)
	{
		return t[i];
	}
	put(i);
	int mid=(t[i].l+t[i].r)>>1;
	if(mid<l) return query(i<<1|1,l,r);
	else if(mid>=r) return query(i<<1,l,r);
	else 
	{
		tree ans,L=query(i<<1,l,mid),R=query(i<<1|1,mid+1,r);
		ans.num=L.num+R.num;
		ans.lna=L.lna;
		if(L.lna==L.r-L.l+1) ans.lna+=R.lna;
		ans.rna=R.rna;
		if(R.rna==R.r-R.l+1) ans.rna+=L.rna;
		ans.lnb=L.lnb;
		if(L.lnb==L.r-L.l+1) ans.lnb+=R.lnb;
		ans.rnb=R.rnb;
		if(R.rnb==R.r-R.l+1) ans.rnb+=L.rnb;
		ans.numa=L.rna+R.lna;
		ans.numa=max(ans.numa,L.numa);
		ans.numa=max(ans.numa,R.numa);		
		ans.numb=L.rnb+R.lnb;
		ans.numb=max(ans.numb,L.numb);
		ans.numb=max(ans.numb,R.numb);	
		return ans;
	}
}
int main(void)
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,1,n);
	while(m--)
	{
		int b,c,d;
		b=read(),c=read()+1,d=read()+1;
		if(b==0||b==1)
		{
			upd(1,c,d,b);
		}
		else if(b==2)
		{
			change(1,c,d);
		}
		else if(b==3)
		{
			cout<<ask(1,c,d)<<endl;
		}
		else
		{
			cout<<query(1,c,d).numa<<endl;
		}
	}
	return 0;
}
