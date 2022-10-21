#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int n,tot;
const int maxn=1e5+10;
int bit[maxn];
int a[maxn],b[maxn];

inline int lowbit(int x)
{
	return x&-x;
}
inline void add(int pos,int x)
{
	for(int i=pos;i<=tot;i+=lowbit(i))bit[i]+=x;
}
inline int find_kth(int k)
{
	int ans=0,now=0;				//������Ҫ����һ�������ԭ�� ans���Ǵ𰸣�now�Ǳȵ�ǰ�ҵ�������С�����ֵĸ����� 
	for(int i=20;i>=0;i--)			//2^20����˵�ܴ��ˣ��������ǵ������ˣ����ǰ���20�����Ϳ��� 
	{
		ans+=(1<<i);			//���ô𰸼���ȥ������ 
		if(ans>tot||now+bit[ans]>=k)ans-=(1<<i);//���������������ֵ����ֹ����Խ�磩�������� ������k�������˻�ȥ������ע���Ǵ��ڵ��ڣ���ΪҪ�������ظ�Ԫ�أ����������ҵ���ʵ��һ������С�����ĸ���С��k����������������ܲ�����⣬���������������ˣ� 
		else now+=bit[ans];//�ܼӾͼ��ϣ����ﲻ���¼ӵ���ԭ����������Ϊ��״����Ľṹʹ����±��������������Ƕ��������һ��֦ 
	}
	return ans+1;//Ȼ�����1���Ǵ��� 
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[++tot]);		//������ 
		b[tot]=a[tot];
	}
	sort(a+1,a+1+n);				//�Ÿ��� 
	tot=unique(a+1,a+1+tot)-a-1;	//ȥ���� 
	for(int i=1;i<=n;i++)b[i]=lower_bound(a+1,a+1+tot,b[i])-a;//��ɢ��һ�� 
	for(int i=1;i<=n;i++)
	{
		add(b[i],1);			//��̬�ӵ� 
		if(i&1)printf("%d\n",a[find_kth((i+1)>>1)]);//��kth 
	}
	return 0;
}

