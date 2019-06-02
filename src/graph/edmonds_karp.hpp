#include <queue>
#include "network_flow.hpp"
using namespace std;

template <size_t SIZE>
class edmonds_karp : public network_flow<SIZE> {
   private:
    int a[SIZE];   //��㵽i�ĿɸĽ���
    int fa[SIZE];  //���·���ϵ����
   public:
    edmonds_karp(int n) : network_flow(n) {
        memset(a, 0, sizeof a);
        memset(fa, 0, sizeof fa);
    }

    int maxflow(int s, int t) {
        int flow = 0;
        while (true) {
            memset(a, 0, sizeof a);
            queue<int> q;
            q.push(s);
            a[s] = INF;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int i : g[u]) {
                    edge& now = e[i];
                    if (a[now.to] == 0 && now.cap > now.flow) {
                        fa[now.to] = i;
                        a[now.to] = min(a[u], now.cap - now.flow);
                        q.push(now.to);
                    }
                }
                if (a[t] > 0) {  //��֦���Ѿ��ҵ���һ��
                    break;
                }
            }
            if (a[t] == 0) {  //û������·��
                break;
            }
            for (int u = t; u != s; u = e[fa[u]].from) {
                e[fa[u]].flow += a[t];
                e[fa[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
};
