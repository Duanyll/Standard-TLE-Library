template <typename value_t, size_t SIZE>
class segtree {
   public:
    segtree(int n) {
        this->n = n;
        memset(sum, 0, sizeof sum);
        memset(lazy, 0, sizeof lazy);
        build(1, n, 1);
    }

    segtree(int n, int* a) {
        this->n = n;
        memset(sum, 0, sizeof sum);
        memset(lazy, 0, sizeof lazy);
        build_with_array(a, 1, n, 1);
    }
    segtree(int n, value_t* num, int* rnk) {
        this->n = n;
        memset(sum, 0, sizeof sum);
        memset(lazy, 0, sizeof lazy);
        build_for_tls(num, rnk, 1, n, 1);
    }
    void update(int l, int r, value_t val) { update(l, r, val, 1, n, 1); }
    value_t query(int l, int r) { return query(l, r, 1, n, 1); }

   private:
    value_t lazy[SIZE << 2];
    value_t sum[SIZE << 2];
    int n;

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

    void pushup(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }

    void pushdown(int rt, int mid) {
        if (lazy[rt]) {
            lazy[rt << 1] += lazy[rt];
            lazy[rt << 1 | 1] += lazy[rt];
            sum[rt << 1] += (mid - (mid >> 1)) * lazy[rt];
            sum[rt << 1 | 1] += (mid >> 1) * lazy[rt];
            lazy[rt] = 0;
        }
    }

    void build(int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            cin >> sum[rt];
            return;
        }
        int mid = (l + r) >> 1;
        build(lson);
        build(rson);
        pushup(rt);
    }

    void build_with_array(int* a, int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            sum[rt] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build_with_array(a, lson);
        build_with_array(a, rson);
        pushup(rt);
    }

    void build_for_tls(value_t* num, int* rnk, int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            sum[rt] = num[rnk[rt]];
            return;
        }
        int mid = (l + r) >> 1;
        build_for_tls(num, rnk, lson);
        build_for_tls(num, rnk, rson);
        pushup(rt);
    }

    void update(int L, int R, value_t c, int l, int r, int rt) {
        if (L <= l && R >= r) {
            lazy[rt] += c;
            sum[rt] += (value_t)c * (r - l + 1);
            return;
        }
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        if (L <= mid) update(L, R, c, lson);
        if (R > mid) update(L, R, c, rson);
        pushup(rt);
    }

    value_t query(int L, int R, int l, int r, int rt) {
        if (L <= l && R >= r) return sum[rt];
        pushdown(rt, r - l + 1);
        int mid = (l + r) >> 1;
        value_t ret = 0;
        if (L <= mid) ret += query(L, R, lson);
        if (R > mid) ret += query(L, R, rson);
        return ret;
    }

#undef lson
#undef rson
};