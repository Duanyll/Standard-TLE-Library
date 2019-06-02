#include <queue>
#include "network_flow.hpp"
using namespace std;

template<size_t SIZE>
class dinic : public network_flow<SIZE> {
   private:
    int dis[SIZE];  //起点到i的距离
    int cur[SIZE];  //当前弧
    bool vis[SIZE];

    int s, t;

    bool bfs() {
        memset(vis, false, sizeof vis);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i : g[u]) {
                edge& now = e[i];
                if (!vis[now.to] && now.cap > now.flow) {
                    vis[now.to] = true;
                    dis[now.to] = dis[u] + 1;
                    q.push(now.to);
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int a) {
        if (u == t || a == 0) {
            return a;
        }
        int flow = 0;
        for (; cur[u] < g[u].size(); cur[u]++) {
            edge& now = e[g[u][cur[u]]];
            if (dis[u] + 1 == dis[now.to]) {
                int f = dfs(now.to, min(a, now.cap - now.flow));
                if (f > 0) {
                    now.flow += f;
                    e[g[u][cur[u]] ^ 1].flow -= f;
                    flow += f;
                    a -= f;
                    if (a == 0) {
                        break;
                    }
                }
            }
        }
        return flow;
    }

   public:
    dinic(int n) : network_flow(n) {
        memset(dis, 0, sizeof dis);
        memset(cur, 0, sizeof cur);
        memset(vis, false, sizeof vis);
    }

    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof cur);
            flow += dfs(s, INF);
        }
        return flow;
    }
};
