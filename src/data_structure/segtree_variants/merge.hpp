#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 50010;

class segtree {
   protected:
    int sum[MAXN << 2], lsum[MAXN << 2], rsum[MAXN << 2];
    int cover[MAXN << 2];

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
#define ls rt << 1
#define rs rt << 1 | 1

    void build(int l, int r, int rt) {
        cover[rt] = -1;
        sum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(lson);
        build(rson);
    }

    void pushdown(int rt, int len) {
        if (cover[rt] != -1) {
            cover[ls] = cover[rs] = cover[rt];
            lsum[ls] = rsum[ls] = sum[ls] = cover[rt] ? 0 : (len - (len >> 1));
            lsum[rs] = rsum[rs] = sum[rs] = cover[rt] ? 0 : (len >> 1);
            cover[rt] = -1;
        }
    }

    void pushup(int rt, int len) {
        lsum[rt] = lsum[ls];
        rsum[rt] = rsum[rs];
        if (lsum[rt] == (len - (len >> 1))) {
            lsum[rt] += lsum[rs];
        }
        if (rsum[rt] == (len >> 1)) {
            rsum[rt] += rsum[ls];
        }
        sum[rt] = max(rsum[ls] + lsum[rs], max(sum[ls], sum[rs]));
    }

    void update(int L, int R, int c, int l, int r, int rt) {
        if (L <= l && r <= R) {
            sum[rt] = lsum[rt] = rsum[rt] = c ? 0 : (r - l + 1);
            cover[rt] = c;
            return;
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if (L <= mid) {
            update(L, R, c, lson);
        }
        if (R > mid) {
            update(L, R, c, rson);
        }
        pushup(rt, r - l + 1);
    }

   public:
    int n;

    segtree(int n) {
        this->n = n;
        build(1, n, 1);
    }

    void update(int l, int r, int v) { update(l, r, v, 1, n, 1); }
};

class segtree_lmost : public segtree {
   protected:
    int query(int w, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if (sum[ls] >= w) {
            return query(w, lson);
        } else if (rsum[ls] + lsum[rs] >= w) {
            return mid - rsum[ls] + 1;
        } else if (sum[rs] >= w) {
            return query(w, rson);
        } else {
            return 0;
        }
    }

   public:
    int query(int w) {
        if (sum[1] < w) {
            return 0;
        }
        return query(w, 1, n, 1);
    }

    segtree_lmost(int n) : segtree(n) {}
};

class segtree_lr : public segtree {
   protected:
    int queryl(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return lsum[rt];
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if (R <= mid) {
            return queryl(L, R, lson);
        } else if (L > mid) {
            return queryl(L, R, rson);
        } else {
            int lans = queryl(L, mid, lson);
            if (lans == mid - L + 1) {
                return lans + queryl(mid + 1, R, rson);
            } else {
                return lans;
            }
        }
    }

    int queryr(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return rsum[rt];
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if (R <= mid) {
            return queryr(L, R, lson);
        } else if (L > mid) {
            return queryr(L, R, rson);
        } else {
            int rans = queryr(mid + 1, R, rson);
            if (rans == R - mid) {
                return queryr(L, mid, lson) + rans;
            } else {
                return rans;
            }
        }
    }

   public:
    segtree_lr(int n) : segtree(n) {}

    int query(int x) {
        int ans = queryr(1, x, 1, n, 1) + queryl(x, n, 1, n, 1);
        if (ans > 0) {
            ans -= 1;
        } else {
            ans = 0;
        }
        return ans;
    }
};
