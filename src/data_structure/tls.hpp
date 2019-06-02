#include "../graph/lfs.hpp"
#include "segtree.hpp"

template <typename T, size_t SIZE>
class tls : public lfs<SIZE> {
   public:
    tls(int n, int rt = 1) : lfs(n) {
        root = rt;
        tim = 0;
        this->num = num;
        memset(son, -1, sizeof son);
    }

    ~tls() { delete tree; }

    T* num;

    void init(T* num) {
        this->num = num;
        dfs1(root, 0, 0);
        dfs2(root, root);
        tree = new segtree<T, SIZE>(n, num, rnk);
    }

    void update(int x, int y, T val) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            tree->update(tid[top[x]], tid[x], val);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        tree->update(tid[x], tid[y], val);
    }

    T query(int x) { return tree->query(tid[x], tid[x]); }

    T query(int x, int y) {
        T ret = 0;
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            ret += tree->query(tid[top[x]], tid[x]);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        ret += tree->query(tid[x], tid[y]);
        return ret;
    }

    void update_subtree(int u, T x) {
        tree->update(tid[u], tid[u] + size[u] - 1, x);
    }

    T query_subtree(int u) { return tree->query(tid[u], tid[u] + size[u] - 1); }

   private:
    int root;
    segtree<T, SIZE>* tree;
    int tim;
    int size[SIZE], top[SIZE], son[SIZE];
    int dep[SIZE], tid[SIZE], rnk[SIZE], fa[SIZE];
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
