#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <assert.h>
using namespace std;

const int MAXN = 50010;

class segtree
{
  public:
    int sum[MAXN << 2];
    void PushUp(int rt)
    {
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    }

    void build(int l, int r, int rt)
    {
        if (l == r)
        {
            scanf("%d", &sum[rt]);
            return;
        }
        int m = (l + r) >> 1;
        build(l, m, rt << 1);
        build(m + 1, r, rt << 1 | 1);
        PushUp(rt);
    }

    void update(int p, int add, int l, int r, int rt)
    {
        if (l == r)
        {
            sum[rt] += add;
            return;
        }
        int m = (l + r) >> 1;
        if (p <= m)
            update(p, add, l, m, rt << 1);
        else
            update(p, add, m + 1, r, rt << 1 | 1);
        PushUp(rt);
    }

    int query(int ll, int rr, int l, int r, int rt)
    {
        if (ll <= l && rr >= r)
            return sum[rt];
        int m = (l + r) >> 1;
        int ret = 0;
        if (ll <= m)
            ret += query(ll, rr, l, m, rt << 1);
        if (rr > m)
            ret += query(ll, rr, m + 1, r, rt << 1 | 1);
        return ret;
    }
};