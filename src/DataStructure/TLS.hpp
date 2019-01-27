#include "LFS_base.hpp"
#include "SegTree.hpp"

class TLS : public LFS {
   public:
    TLS(int N) {
        memset(head, -1, sizeof head);
        ecnt = 0;
        n = N;
        dfsc = 0;
        memset(son, -1, sizeof son);
        tree = new segtree<int>(N);
    }

    ~TLS() { delete tree; }

    void init() {
        dfs1(1, 0, 0);
        dfs2(1, 1);
        tree->init(num, rnk);
    }
    int num[MAXN];

    void Update(int x, int y, int val) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            tree->add_range(tid[top[x]], tid[x], val);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        tree->add_range(tid[x], tid[y], val);
    }

    int Query(int x) { return tree->query(tid[x]); }

   private:
    segtree<int> *tree;
    int dfsc;
    int size[MAXN], top[MAXN], son[MAXN];
    int dep[MAXN], tid[MAXN], rnk[MAXN], fa[MAXN];
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
        tid[u] = ++dfsc;
        rnk[tid[u]] = u;
        if (son[u] == -1) return;
        dfs2(son[u], tp);
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != son[u] && v != fa[u]) dfs2(v, v);
        }
    }
};