#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 100010;

class mcmf {
   public:
    mcmf(int n) {
        this->n = n;
        memset(head, -1, sizeof head);
        memset(e, 0, sizeof e);
    }
    void adde(int from, int to, int flow, int cost) {
        _adde(from, to, flow, cost);
        _adde(to, from, 0, -cost);
    }

    int max_flow = 0;
    int min_cost = 0;

    void solve(int s, int t) {
        // 每次只增广最短路
        while (spfa(s, t)) {
            max_flow += flow[t];
            min_cost += flow[t] * cost[t];
            int u = t;
            while (u != s) {
                e[in_edge[u]].flow -= flow[t];
                e[in_edge[u] ^ 1].flow += flow[t];
                u = e[in_edge[u]].from;
            }
        }
    }

   protected:
    struct edge {
        int from, to, next;
        int flow, cost;
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt = 0;
    int n;

    void _adde(int from, int to, int flow, int cost) {
        e[ecnt].from = from;
        e[ecnt].to = to;
        e[ecnt].flow = flow;
        e[ecnt].cost = cost;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
    }

    int cost[MAXN];     // 最小花费
    int in_edge[MAXN];  // 进入节点的边
    int flow[MAXN];     // 源点至此流量

    bool ins[MAXN];

    bool spfa(int s, int t) {
        memset(cost, INF, sizeof cost);
        memset(flow, INF, sizeof flow);
        memset(ins, false, sizeof ins);
        memset(in_edge, -1, sizeof in_edge);

        queue<int> q;
        q.push(s);
        ins[s] = true;
        cost[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ins[u] = false;
            for (int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].to;
                if (e[i].flow > 0 && cost[v] > cost[u] + e[i].cost) {
                    cost[v] = cost[u] + e[i].cost;
                    in_edge[v] = i;
                    flow[v] = min(flow[u], e[i].flow);
                    if (!ins[v]) {
                        q.push(v);
                        ins[v] = true;
                    }
                }
            }
        }
        return in_edge[t] != -1;
    }
};