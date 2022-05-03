#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;

struct segtree_data_store {
    int64 addv = 0;
    int64 mulv = 1;
    int64 sum = 0;
    int len = 1;

    segtree_data_store() {}
    segtree_data_store(int val) : sum(val) {}

    void push_down(segtree_data_store& lson, segtree_data_store& rson) {
        if (mulv != 1) {
            lson.mulv *= mulv;
            rson.mulv *= mulv;
            lson.addv *= mulv;
            rson.addv *= mulv;
            lson.sum *= mulv;
            rson.sum *= mulv;
            mulv = 1;
        }
        if (addv != 0) {
            lson.addv += addv;
            rson.addv += addv;
            lson.sum += addv * (len - len / 2);
            rson.sum += addv * (len / 2);
            addv = 0;
        }
    }

    void push_up(segtree_data_store& lson, segtree_data_store& rson) {
        sum = lson.sum + rson.sum;
        len = lson.len + rson.len;
    }
};

struct segtree_query_sum {
    int64 sum = 0;
    segtree_query_sum() {}
    segtree_query_sum(segtree_data_store& seg) : sum(seg.sum) {}
    void merge_left(segtree_query_sum lson) { sum += lson.sum; }
    void merge_right(segtree_query_sum rson) { sum += rson.sum; }
};

struct segtree_update_mul {
    int64 val = 0;
    segtree_update_mul(int64 mul) : val(mul) {}
    void apply(segtree_data_store& seg) const {
        seg.mulv *= val;
        seg.addv *= val;
        seg.sum *= val;
    }
};

struct segtree_update_add {
    int64 val = 0;
    segtree_update_add(int64 add) : val(add) {}
    void apply(segtree_data_store& seg) const {
        seg.addv += val;
        seg.sum += val * int64(seg.len);
    }
};

class segtree {
   public:
    segtree(int n) : n(n), s((n << 2) + 1) { build(1, n, 1); }
    template <typename TBaseData>
    segtree(int n, TBaseData* data) : n(n), s((n << 2) + 1) {
        build(data, 1, n, 1);
    }

    int n;

    template <typename TUpdate>
    void update(int L, int R, const TUpdate& data) {
        update(L, R, data, 1, n, 1);
    }

    template <typename TQuery>
    TQuery query(int L, int R) {
        return query<TQuery>(L, R, 1, n, 1);
    }

   protected:
    vector<segtree_data_store> s;

#define LSON l, mid, rt << 1
#define RSON mid + 1, r, rt << 1 | 1

    void build(int l, int r, int rt) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(LSON);
        build(RSON);
        s[rt].push_up(s[rt << 1], s[rt << 1 | 1]);
    }

    template <typename TBaseData>
    void build(TBaseData* data, int l, int r, int rt) {
        if (l == r) {
            s[rt] = data[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(data, LSON);
        build(data, RSON);
        s[rt].push_up(s[rt << 1], s[rt << 1 | 1]);
    }

    template <typename TUpdate>
    void update(int L, int R, const TUpdate& data, int l, int r, int rt) {
        if (L <= l && r <= R) {
            data.apply(s[rt]);
            return;
        }
        s[rt].push_down(s[rt << 1], s[rt << 1 | 1]);
        int mid = (l + r) >> 1;
        if (L <= mid) update(L, R, data, LSON);
        if (R > mid) update(L, R, data, RSON);
        s[rt].push_up(s[rt << 1], s[rt << 1 | 1]);
    }

    template <typename TQuery>
    TQuery query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return TQuery(s[rt]);
        }
        s[rt].push_down(s[rt << 1], s[rt << 1 | 1]);
        int mid = (l + r) >> 1;
        TQuery res;
        if (L <= mid) res.merge_left(query<TQuery>(L, R, LSON));
        if (R > mid) res.merge_right(query<TQuery>(L, R, RSON));
        return res;
    }

#undef LSON
#undef RSON
};