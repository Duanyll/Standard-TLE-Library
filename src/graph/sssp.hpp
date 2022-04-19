#include <queue>

#include "lfs.hpp"

class dijkstra : public lfs {
   public:
    dijkstra(int n) : lfs(n) { memset(dis, INF, sizeof dis); }
    int dis[MAXN];
    void solve(int s) {
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            q;
        dis[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            auto x = q.top();
            q.pop();
            int u = x.second;
            if (dis[u] < x.first) continue;
            for (int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].to;
                if (dis[u] + e[i].w < dis[v]) {
                    dis[v] = dis[u] + e[i].w;
                    q.push({dis[v], v});
                }
            }
        }
    }
};

class spfa : public lfs {
   public:
    spfa(int n) : lfs(n) { memset(dis, INF, sizeof dis); }
    int dis[MAXN];
    void solve(int s) {
        memset(ins, false, sizeof ins);
        memset(dis, INF, sizeof dis);
        queue<int> q;
        q.push(s);
        ins[s] = true;
        dis[s] = 0;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            ins[now] = false;
            for (int i = head[now]; i != -1; i = e[i].next) {
                int v = e[i].to;
                int w = e[i].w;
                if (dis[now] + w < dis[v]) {
                    dis[v] = dis[now] + w;
                    if (!ins[v]) {
                        q.push(v);
                        ins[v] = true;
                    }
                }
            }
        }
    }

   private:
    bool ins[MAXN];
};
