#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

template <size_t SIZE = 100010, size_t EDGE = SIZE * 2>
class lfs {
   public:
    lfs(int N) {
        memset(head, -1, sizeof head);
        ecnt = 0;
        n = N;
    }
    void adde(int from, int to, int w) {
        e[ecnt].to = to;
        e[ecnt].w = w;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
    }
    void addde(int a, int b, int w) {
        adde(a, b, w);
        adde(b, a, w);
    }

   protected:
    struct Edge {
        int to, next, w;
    } e[EDGE];
    int head[SIZE];
    int ecnt;
    int n;

   private:
    virtual void dfs(int u, int fa) {
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != fa) {
                dfs(v, u);
            }
        }
    }
};
