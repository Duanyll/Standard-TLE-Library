#include "../graph/lfs.hpp"
#include "segtree.hpp"

class tls : public lfs {
   public:
    tls(int n, int root = 1)
        : lfs(n, (n - 1) * 2),
          root(root),
          tree(1),
          size(n + 1, 0),
          top(n + 1, 0),
          son(n + 1, -1),
          dep(n + 1, 0),
          tid(n + 1, 0),
          rnk(n + 1, 0),
          fa(n + 1, 0) {}

    template <typename TBaseData>
    void init(TBaseData* num) {
        dfs1(root, 0, 0);
        dfs2(root, root);
        vector<TBaseData> data(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            data[i] = num[rnk[i]];
        }
        tree = segtree(n, data.data());
    }

    template <typename TUpdate>
    void update(int x, int y, const TUpdate& data) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            tree.update(tid[top[x]], tid[x], data);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        tree.update(tid[x], tid[y], data);
    }

    template <typename TQuery>
    TQuery query(int x) {
        return tree.query<TQuery>(tid[x], tid[x]);
    }

    template <typename TQuery>
    TQuery query(int x, int y) {
        TQuery x_to_lca;
        TQuery lca_to_y;
        while (top[x] != top[y]) {
            if (dep[top[x]] >= dep[top[y]]) {
                TQuery seg = tree.query<TQuery>(tid[top[x]], tid[x]);
                seg.flip();
                x_to_lca.merge_right(seg);
                x = fa[top[x]];
            } else {
                TQuery seg = tree.query<TQuery>(tid[top[y]], tid[y]);
                lca_to_y.merge_left(seg);
                y = fa[top[y]];
            }
        }
        if (dep[x] >= dep[y]) {
            TQuery seg = tree.query<TQuery>(tid[y], tid[x]);
            seg.flip();
            x_to_lca.merge_right(seg);
            x_to_lca.merge_right(lca_to_y);
            return x_to_lca;
        } else {
            TQuery seg = tree.query<TQuery>(tid[x], tid[y]);
            x_to_lca.merge_right(seg);
            x_to_lca.merge_right(lca_to_y);
            return x_to_lca;
        }
    }

    template <typename TUpdate>
    void update_subtree(int u, const TUpdate& data) {
        tree.update(tid[u], tid[u] + size[u] - 1, data);
    }

    template <typename TQuery>
    TQuery query_subtree(int u) {
        return tree.query<TQuery>(tid[u], tid[u] + size[u] - 1);
    }

   private:
    int root;
    segtree tree;
    int tim = 0;
    vector<int> size, top, son, dep, tid, rnk, fa;

    void dfs1(int u, int fa, int d) {
        dep[u] = d;
        this->fa[u] = fa;
        size[u] = 1;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != fa) {
                dfs1(v, u, d + 1);
                size[u] += size[v];
                if (son[u] == -1 || size[v] > size[son[u]]) son[u] = v;
            }
        }
    }
    void dfs2(int u, int tp) {
        top[u] = tp;
        tid[u] = ++tim;
        rnk[tid[u]] = u;
        if (son[u] == -1) return;
        dfs2(son[u], tp);
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != son[u] && v != fa[u]) dfs2(v, v);
        }
    }
};