#include "lfs.hpp"

class offline_tree_path {
   public:
    lfs& g;

    offline_tree_path(lfs& graph, int root = 1)
        : g(graph),
          size(g.n + 1, 0),
          top(g.n + 1, 0),
          son(g.n + 1, -1),
          dep(g.n + 1, 0),
          fa(g.n + 1, 0),
          enter(g.n + 1, 0),
          leave(g.n + 1, 0) {
        eular.reserve(g.n * 2);
        eular.push_back(0);
        dfs1(root, 0, 0);
        dfs2(root, root);
    }

    int query_lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        return x;
    }

    template <typename TAns>
    struct query {
        int id = 0;
        int x = 0, y = 0;
        int l = 0, r = 0;
        int lca = 0;
        TAns ans = 0;
    };

    template <typename TQuery, typename TAns>
    void solve(vector<TQuery>& queries, function<void(int, TAns&)> add,
               function<void(int, TAns&)> del, TAns ans_reset = TAns()) {
        for (auto& q : queries) {
            if (enter[q.x] > enter[q.y]) {
                swap(q.x, q.y);
            }
            int lca = query_lca(q.x, q.y);
            if (lca == q.x) {
                q.l = enter[q.x];
                q.r = enter[q.y];
            } else {
                q.l = leave[q.x];
                q.r = enter[q.y];
                q.lca = lca;
            }
        }
        int block_size = g.n * 2 / sqrt(queries.size() * 2 / 3);
        sort(queries.begin(), queries.end(),
             [&](const auto& a, const auto& b) -> bool {
                 if (a.l / block_size != b.l / block_size) {
                     return a.l / block_size < b.l / block_size;
                 } else if ((a.l / block_size) & 1) {
                     return a.r < b.r;
                 } else {
                     return a.r > b.r;
                 }
             });

        TAns ans = ans_reset;
        vector<char> ins(g.n + 1, 0);  // Avoid vector<bool>
        auto update_point = [&](int u) {
            if (ins[u]) {
                del(u, ans);
            } else {
                add(u, ans);
            }
            ins[u] = !ins[u];
        };
        int l = 1;
        int r = 0;
        for (auto& q : queries) {
            while (l > q.l) update_point(eular[--l]);
            while (r < q.r) update_point(eular[++r]);
            while (l < q.l) update_point(eular[l++]);
            while (r > q.r) update_point(eular[r--]);
            if (q.lca != 0) {
                update_point(q.lca);
            }
            q.ans = ans;
            if (q.lca != 0) {
                update_point(q.lca);
            }
        }
    }

   private:
    vector<int> size, top, son, dep, fa;

    void dfs1(int u, int fa, int d) {
        dep[u] = d;
        this->fa[u] = fa;
        size[u] = 1;
        for (int i = g.head[u]; i != -1; i = g.e[i].next) {
            int v = g.e[i].to;
            if (v != fa) {
                dfs1(v, u, d + 1);
                size[u] += size[v];
                if (son[u] == -1 || size[v] > size[son[u]]) son[u] = v;
            }
        }
    }

    vector<int> enter, leave;
    vector<int> eular;

    void dfs2(int u, int tp) {
        top[u] = tp;
        eular.push_back(u);
        enter[u] = eular.size() - 1;
        if (son[u] != -1) {
            dfs2(son[u], tp);
            for (int i = g.head[u]; i != -1; i = g.e[i].next) {
                int v = g.e[i].to;
                if (v != son[u] && v != fa[u]) dfs2(v, v);
            }
        }
        eular.push_back(u);
        leave[u] = eular.size() - 1;
    }
};