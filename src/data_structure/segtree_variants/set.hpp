#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 100010;

template <typename T>
class segtree {
   public:
    int n;
    segtree(int n) {
        memset(sum, 0, sizeof sum);
        memset(setv, -1, sizeof setv);
        this->n = n;
    }

    void set(int l, int r, T val) { set(l, r, val, 1, n, 1); }

    T query(int l, int r) {
        return query(l,r,1,n,1);
    }
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ls rt << 1
#define rs rt << 1 | 1
   protected:
    T sum[MAXN << 2], setv[MAXN << 2];
    void maintain(int l, int r, int rt) {
        if (r > l) {
            sum[rt] = sum[ls] + sum[rs];
        }
        if (setv[rt] >= 0) {
            sum[rt] = setv[rt] * (r - l + 1);
        }
    }

    void pushdown(int rt) {
        if (setv[rt] >= 0) {
            setv[ls] = setv[rs] = setv[rt];
            setv[rt] = -1;
        }
    }

    void set(int L, int R, T val, int l, int r, int rt) {
        if (L <= l && R >= r) {
            setv[rt] = val;
        } else {
            pushdown(rt);
            int m = (l + r) >> 1;
            if (L <= m) {
                set(L, R, val, lson);
            } else {
                maintain(lson);
            }
            if (R > m) {
                set(L, R, val, rson);
            } else {
                maintain(rson);
            }
        }
        maintain(l, r, rt);
    }

    T query(int L, int R, int l, int r, int rt) {
        T ret = 0;
        if (setv[rt] >= 0) {
            ret += setv[rt] * (min(r, R) - max(l, L) + 1);
        } else if (L <= l && R >= r) {
            ret += sum[rt];
        } else {
            int m = (l + r) >> 1;
            if (L <= m) {
                ret += query(L, R, lson);
            }
            if (R > m) {
                ret += query(L, R, rson);
            }
        }
       return ret;
    }
#undef lson
#undef rson
#undef ls
#undef rs
};
