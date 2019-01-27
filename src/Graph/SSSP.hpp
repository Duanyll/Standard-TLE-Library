#include <queue>
#include "LFS_base.hpp"

struct Dijkstra : public LFS {
   public:
    Dijkstra(int n) {
        memset(dis, INF, sizeof dis);
        LFS(n);
    }
    int dis[MAXN];
    void solve(int s) {
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            que;
        dis[s] = 0;
        que.push(pair<int, int>(0, s));
        while (!que.empty()) {
            pair<int, int> p = que.top();
            que.pop();
            int v = p.second;
            if (dis[v] < p.first) continue;
            for (int i = head[v]; ~i; i = e[i].next) {
                Edge now = e[i];
                if (now.w + dis[v] < dis[now.to]) {
                    dis[now.to] = now.w + dis[v];
                    que.push(pair<int, int>(dis[now.to], now.to));
                }
            }
        }
    }
};

struct SPFA : public LFS {
   public:
    SPFA(int n) {
        memset(dis, INF, sizeof dis);
        LFS(n);
    }
    int dis[MAXN];
    void solve(int s) {
        memset(vis, false, sizeof vis);
        memset(dis, INF, sizeof dis);
        queue<int> Q;
        Q.push(s);
        vis[s] = 1;
        dis[s] = 0;
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            vis[now] = 0;
            for (int i = head[now]; i != -1; i = e[i].next) {
                int w = e[i].w;
                int son = e[i].to;
                if (dis[now] + w < dis[son]) {
                    dis[son] = dis[now] + w;
                    if (!vis[son]) {
                        Q.push(son);
                        vis[son] = 1;
                    }
                }
            }
        }
    }

   private:
    bool vis[MAXN];
};