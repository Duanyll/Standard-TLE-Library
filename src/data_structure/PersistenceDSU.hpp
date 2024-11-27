#include "PersistenceDSU.hpp"
#include<algorithm> 
using namespace std;
class PersistenceDSU
{
private:
	struct node
	{
		int lson,rson,fa,deep;
	}a[MAXN*LOG+5];
	int n,m,top,root[MAXN+5];
public:
	inline int build(int l,int r)
	{
		int num=++top;
		if(l==r)
		{
			a[num].fa=l;
			return num;
		}
		int mid=l+r>>1;
		a[num].lson=build(l,mid);
		a[num].rson=build(mid+1,r);
		return num;
	}
	inline int que(int now,int l,int r,int x)
	{
		if(l==r)return now;
		int mid=l+r>>1;
		if(mid>=x)return que(a[now].lson,l,mid,x);
		else return que(a[now].rson,mid+1,r,x);
	}
	inline int find(int now,int x)
	{
		int fa=que(root[now],1,n,x);
		if(a[fa].fa==x)return fa;
		return find(now,a[fa].fa);
	}
	inline int clone(int x)
	{
		int num=++top;
		a[num]=a[x];
		return num;
	}
	inline int hb(int x,int l,int r,int fx,int fy)
	{
		int num=clone(x);
	//	cout<<"hb:"<<a[x].rson<<" "<<x<<" "<<l<<" "<<r<<" "<<fx<<" "<<fy<<endl;
		if(l==r)
		{
			a[num].fa=fy;
			return num;
		}
		int mid=l+r>>1;
	//	cout<<"mid="<<mid<<endl;
		if(mid>=fx)
		{
	//		cout<<"left"<<endl;
			a[num].lson=hb(a[x].lson,l,mid,fx,fy);
		}
		else a[num].rson=hb(a[x].rson,mid+1,r,fx,fy);
		return num;
	}
	inline int add(int now,int l,int r,int x)
	{
		int num=clone(now); 
		if(l==r)
		{
			++a[num].deep;
			return num;
		}
		int mid=l+r>>1;
		if(mid>=x)a[num].lson=add(a[now].lson,l,mid,x);
		else a[num].rson=add(a[now].rson,mid+1,r,x);
		return num;
	}
	inline void merge(int x,int aa,int bb)
	{
		root[x]=root[x-1];
		aa=find(x,aa),bb=find(x,bb);
		if(a[aa].fa!=a[bb].fa)
		{
			if(a[aa].deep>a[bb].deep)swap(aa,bb);
			root[x]=hb(root[x-1],1,n,a[aa].fa,a[bb].fa);
			if(a[aa].deep==a[bb].deep)root[x]=add(root[x],1,n,a[bb].fa);
		}
	}
	inline bool check(int x,int xx,int yy)
	{
		xx=find(x,xx),yy=find(x,yy);
		if(a[xx].fa==a[yy].fa)return 1;
		return 0;
	}
};