#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

template <size_t SIZE>
class network_flow {
   protected:
    struct edge {
        int from, to;
        int cap, flow;
        edge(int u, int v, int c, int f = 0)
            : from(u), to(v), cap(c), flow(f){};
    };
    int n, m;
    vector<edge> e;
    vector<int> g[SIZE];

   public:
    network_flow() {
        n = 0;
        m = 0;
    }

    network_flow(int n) {
        this->n = n;
        m = 0;
    }

    void adde(int from, int to, int cap) {
        e.push_back(edge(from, to, cap));
        g[from].push_back(e.size() - 1);
        e.push_back(edge(to, from, 0));
        g[to].push_back(e.size() - 1);
        m += 2;
    }

    void clear_flow() {
        for (edge& i : e) {
            i.flow = 0;
        }
    }
};
