#include "LFS_base.hpp"
#include <queue>

struct Dijkstra : public LFS
{
  public:
    Dijkstra(int n){
        memset(dis,INF,sizeof dis);
        LFS(n);
    }
    int dis[MAXN];
    void solve(int s)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
        dis[s] = 0;
        que.push(pair<int, int>(0, s));
        while (!que.empty())
        {
            pair<int, int> p = que.top();
            que.pop();
            int v = p.second;
            if (dis[v] < p.first)
                continue;
            for (int i = head[v]; ~i; i = e[i].next)
            {
                Edge now = e[i];
                if (now.w + dis[v] < dis[now.to])
                {
                    dis[now.to] = now.w + dis[v];
                    que.push(pair<int, int>(dis[now.to], now.to));
                }
            }
        }
    }
}