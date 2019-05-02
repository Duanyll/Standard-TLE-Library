#include <queue>
#include "lfs.hpp"

class dijkstra : public lfs {
   public:
    dijkstra(int n) : lfs(n){
        memset(dis, INF, sizeof dis);
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

class spfa : public lfs {
   public:
    spfa(int n) : lfs(n){
        memset(dis, INF, sizeof dis);
    }
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
                int w = e[i].w;
                int v = e[i].to;
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
