#include <cstring>
#include <iostream>
using namespace std;

template<typename T> 
struct segtree_add{
	static T merge(T l,T r){
		return l+r;
	}

	static void pushdown(T val,T& l,T& r,T& lazyl,T& lazyr,T& lazyrt){
		lazyl += lazyrt;
		lazyr += lazyrt;
		l += (val - (val >> 1)) * lazyrt;
		r += (val >> 1) * lazyrt;
	}

	static void pdinit(T val,T& rt,T& lazy,int len){
		lazy += val;
		rt += (T)val * (len);
	}
};

const int MAXN = 100010;

template <typename T,typename oprs>
class segtree
{
  public:
	segtree(int cnt)
	{
		this->cnt = cnt;
		memset(sum, 0, sizeof sum);
		memset(lazy, 0, sizeof lazy);
	}
	void init()
	{
		Build(1, cnt, 1);
	}
	void init(T *num, int *rnk)
	{
		this->num = num;
		this->rnk = rnk;
		build(1, cnt, 1);
	}
	void add_range(int l, int r, T val)
	{
		Update(l, r, val, 1, cnt, 1);
	}
	T query(int l, int r)
	{
		return Query(l, r, 1, cnt, 1);
	}
	T query(int x)
	{
		return Query(1, cnt, 1, x);
	}

  private:
	T lazy[MAXN << 2];
	T sum[MAXN << 2];
	int cnt;

	T *num;
	int *rnk;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

	void PushUP(int rt){
		sum[rt] = oprs::merge(sum[rt<<1],sum[rt<<1|1]);
	}

	void PushDown(int rt, int m)
	{
		if (lazy[rt])
		{
			oprs::pushdown(m,sum[rt<<1],sum[rt<<1|1],lazy[rt<<1],lazy[rt<<1|1],lazy[rt]);
			lazy[rt] = 0;
		}
	}

	void Build(int l, int r, int rt)
	{
		lazy[rt] = 0;
		if (l == r)
		{
			cin >> sum[rt];
			return;
		}
		int m = (l + r) >> 1;
		Build(lson);
		Build(rson);
		PushUP(rt);
	}

	void build(int l, int r, int rt)
	{
		lazy[rt] = 0;
		if (l == r)
		{
			sum[rt] = num[rnk[rt]];
			return;
		}
		int m = (l + r) >> 1;
		build(lson);
		build(rson);
		PushUP(rt);
	}

	void Update(int L, int R, T c, int l, int r, int rt)
	{
		if (L <= l && R >= r)
		{
			oprs::pdinit(c,sum[rt],lazy[rt],r-l+1);
			return;
		}
		PushDown(rt, r - l + 1);
		int m = (l + r) >> 1;
		if (L <= m)
			Update(L, R, c, lson);
		if (R > m)
			Update(L, R, c, rson);
		PushUP(rt);
	}

	T Query(int L, int R, int l, int r, int rt)
	{
		if (L <= l && R >= r)
			return sum[rt];
		PushDown(rt, r - l + 1);
		int m = (l + r) >> 1;
		T ret = T();
		if (L <= m)
			ret = TMerge(ret,Query(L, R, lson));
		if (R > m)
			ret = TMerge(ret,Query(L, R, rson));
		return ret;
	}

	T Query(int l, int r, int rt, int val)
	{
		if (l == r)
			return sum[rt];
		PushDown(rt, r - l + 1);
		int m = (l + r) >> 1;
		T ret = T();
		if (val <= m)
			ret = Query(lson, val);
		else
			ret = Query(rson, val);
		PushUP(rt);
		return ret;
	}

#undef lson
#undef rson
};
