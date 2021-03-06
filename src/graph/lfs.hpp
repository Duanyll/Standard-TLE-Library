#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

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
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt;
    int n;
};
