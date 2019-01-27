template <typename value_t>
class segtree {
   public:
    segtree() {}
    segtree(int cnt) {
        this->cnt = cnt;
        memset(sum, 0, sizeof sum);
        memset(lazy, 0, sizeof lazy);
    }
    void init() { Build(1, cnt, 1); }
    void init(value_t *num, int *rnk) {
        this->num = num;
        this->rnk = rnk;
        build(1, cnt, 1);
    }
    void add_range(int l, int r, value_t val) { Update(l, r, val, 1, cnt, 1); }
    value_t query(int l, int r) { return Query(l, r, 1, cnt, 1); }
    value_t query(int x) { return Query(1, cnt, 1, x); }

   private:
    value_t lazy[MAXN << 2];
    value_t sum[MAXN << 2];
    int cnt;

    value_t *num;
    int *rnk;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

    void PushUP(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }

    void PushDown(int rt, int m) {
        if (lazy[rt]) {
            lazy[rt << 1] += lazy[rt];
            lazy[rt << 1 | 1] += lazy[rt];
            sum[rt << 1] += (m - (m >> 1)) * lazy[rt];
            sum[rt << 1 | 1] += (m >> 1) * lazy[rt];
            lazy[rt] = 0;
        }
    }

    void Build(int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            cin >> sum[rt];
            return;
        }
        int m = (l + r) >> 1;
        Build(lson);
        Build(rson);
        PushUP(rt);
    }

    void build(int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            sum[rt] = num[rnk[rt]];
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        PushUP(rt);
    }

    void Update(int L, int R, value_t c, int l, int r, int rt) {
        if (L <= l && R >= r) {
            lazy[rt] += c;
            sum[rt] += (value_t)c * (r - l + 1);
            return;
        }
        PushDown(rt, r - l + 1);
        int m = (l + r) >> 1;
        if (L <= m) Update(L, R, c, lson);
        if (R > m) Update(L, R, c, rson);
        PushUP(rt);
    }

    value_t Query(int L, int R, int l, int r, int rt) {
        if (L <= l && R >= r) return sum[rt];
        PushDown(rt, r - l + 1);
        int m = (l + r) >> 1;
        value_t ret = 0;
        if (L <= m) ret += Query(L, R, lson);
        if (R > m) ret += Query(L, R, rson);
        return ret;
    }

    value_t Query(int l, int r, int rt, int val) {
        if (l == r) return sum[rt];
        PushDown(rt, r - l + 1);
        int m = (l + r) >> 1;
        value_t ret = 0;
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