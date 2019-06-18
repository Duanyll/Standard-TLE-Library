#include "lfs.hpp"
#include <vector>
#include <stack>

class bcc : public lfs {
   protected:
    int dfn[MAXN], low[MAXN], tim;
    int color[MAXN];  //  处理bcc数组时防重复用
    stack<pair<int, int>> s;

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++tim;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v == fa) continue;
            if (dfn[v] == 0) {
                s.push(make_pair(u, v));
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    vector<int> cur;
                    bcccnt++;
                    pair<int, int> now;
                    do {
                        now = s.top();
                        s.pop();
                        if (color[now.first] != bcccnt) {
                            cur.push_back(now.first);
                            color[now.first] = bcccnt;
                            belong[now.first].push_back(bcccnt);
                        }
                        if (color[now.second] != bcccnt) {
                            cur.push_back(now.second);
                            color[now.second] = bcccnt;
                            belong[now.second].push_back(bcccnt);
                        }
                    } while (!(now.first == u && now.second == v));
                    bccs.push_back(cur);
                }
            } else if (dfn[v] < dfn[u]) {
                s.push(make_pair(u, v));
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

   public:
    vector<int> belong[MAXN];
    int bcccnt;
    vector<vector<int>> bccs;

    bcc(int n) : lfs(n) {
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        memset(color, 0, sizeof color);
        tim = bcccnt = 0;
    }

    void pre() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == 0) dfs(i, -1);
        }
    }
};
