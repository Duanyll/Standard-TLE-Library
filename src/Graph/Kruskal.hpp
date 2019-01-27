#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 310;

namespace kruskal {
struct edge {
    int to, from;
    int dis;
    edge(int _t = 0, int _f = 0, int _dis = 0) {
        to = _t;
        from = _f;
        dis = _dis;
    }
} e[100010 * 2];

int ecnt;

void adde(int to, int from, int dis) { e[++ecnt] = edge(to, from, dis); }

int fa[MAXN];
int find(int u) { return (fa[u] == u) ? u : fa[u] = find(fa[u]); }

int solve(int n) {
    sort(e + 1, e + ecnt + 1,
         [](const edge a, const edge b) -> bool { return a.dis < b.dis; });
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    int cnt = 0;
    int pos = 0;
    int ans = 0;
    while (cnt < n && pos <= ecnt) {
        edge now = e[++pos];
        if (find(now.from) != find(now.to)) {
            ans += now.dis;
            cnt++;
            fa[find(now.from)] = find(fa[now.to]);
        }
    }
    return ans;
}
}  // namespace kruskal
