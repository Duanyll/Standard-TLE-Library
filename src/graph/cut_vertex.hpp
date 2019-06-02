#include <vector>
#include "lfs.hpp"

template<size_t SIZE>
class cut_vertex : public lfs<SIZE> {
   protected:
    int dfn[SIZE], low[SIZE];
    int tim;
    void dfs(int u, int fa) {
        int cc = 0;
        dfn[u] = low[u] = tim++;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dfn[v] == -1) {
                dfs(v, u);
                cc++;
                low[u] = min(low[u], low[v]);
                if (fa != -1 && low[v] > dfn[u]) {
                    ans.push_back(u);
                }
            } else if (v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == -1 && cc >= 2) {
            ans.push_back(u);
        }
    }

   public:
    vector<int> ans;
    cut_vertex(int n) : lfs(n) {
        memset(head, -1, sizeof head);
        ecnt = 0;
    }

    void solve() {
        memset(dfn, -1, sizeof dfn);
        tim = 1;

        for (int i = 1; i <= n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }

        sort(ans.begin(), ans.end());
        vector<int>::iterator it = unique(ans.begin(), ans.end());
        ans.erase(it, ans.end());
    }
};
