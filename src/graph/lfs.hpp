#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;

class lfs {
   public:
    lfs(int n) : n(n), head(n + 1, -1) {}
    lfs(int n, int m) : lfs(n) { e.reserve(m); }
    int n;

    vector<int> head;
    struct edge {
        int to;
        int next;
        int w;
    };
    vector<edge> e;

    void adde(int u, int v, int w = 1) {
        e.push_back(edge{.to = v, .next = head[u], .w = w});
        head[u] = e.size() - 1;
    }

    void addde(int a, int b, int w = 1) {
        adde(a, b, w);
        adde(b, a, w);
    }
};