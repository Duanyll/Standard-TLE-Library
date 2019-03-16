#include "lfs.hpp"
using namespace std;

class lca : public lfs{
   public:
   	int dep[MAXN];
    lca(int n) : lfs(n) {
        memset(dep, -1, sizeof dep);
    }
    void pre(int rt = 1) { dfs(rt, 1, 0); }
    int querylca(int a, int b) {
        if (dep[a] > dep[b]) swap(a, b);
        int h = dep[b] - dep[a];
        for (int i = 20; i >= 0; i--) {
            if(h & (1 << i)) {
				b = f[b][i];
			}
        }
        if (a == b) return a;
        for (int i = 20; i >= 0; i--) {
            if (f[a][i] == f[b][i]) continue;
            a = f[a][i];
            b = f[b][i];
        }
        return f[a][0];
    }

   protected:
    int f[MAXN][22];

   private:
    void dfs(int u, int d, int fa) {
        dep[u] = d;
        f[u][0] = fa;
        for (int i = 1; i < 21; i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dep[v] == -1) {
                dfs(v, d + 1, u);
            }
        }
    }
};
