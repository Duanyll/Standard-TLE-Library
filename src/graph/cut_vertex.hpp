#include <stack>
#include "lfs.hpp"

class cut_vertex : public lfs {
   protected:
    int dfn[MAXN], low[MAXN];
    int tim;
    int scc_count = 0;
    stack<int> s;
    void tarjan(int u, int fa) {
        s.push(u);
        int cc = 0;
        dfn[u] = low[u] = tim++;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dfn[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    cc++;
                    if (fa != -1 || cc > 1) {
                        is_cut_vertex[u] = true;
                    }
                    scc_count++;
                    while (!s.empty()) {
                        int cur = s.top();
                        s.pop();
                        belong_to[cur].push_back(scc_count);
                        if (cur == v) break;
                    }
                    belong_to[u].push_back(scc_count);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

   public:
    vector<int> belong_to[MAXN];
    bool is_cut_vertex[MAXN];
    cut_vertex(int n) : lfs(n) {}

    void pre() {
        memset(dfn, -1, sizeof dfn);
        memset(is_cut_vertex, false, sizeof is_cut_vertex);
        tim = 1;

        for (int i = 1; i <= n; i++) {
            if (dfn[i] == -1) {
                tarjan(i, -1);
            }
        }
    }

    void shrink_point(lfs* graph, vector<int>& mapping) {
        mapping = vector<int>(n + 1, 0);
        int cut_vertex_id = scc_count;
        for (int i = 1; i <= n; i++) {
            if (is_cut_vertex[i]) {
                cut_vertex_id++;
                mapping[i] = cut_vertex_id;
                for (auto& scc : belong_to[i]) {
                    graph->addde(cut_vertex_id, scc, 1);
                }
            } else {
                mapping[i] = belong_to[i][0];
            }
        }
    }
};