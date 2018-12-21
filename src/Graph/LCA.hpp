#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <map>
using namespace std;

const size_t MAXN = 100010;

class LCA
{
  public:
    LCA(int N)
    {
        memset(head, -1, sizeof head);
        memset(dep, -1, sizeof dep);
        ecnt = 0;
        n = N;
    }
    void adde(int from, int to)
    {
        e[ecnt].to = to;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
    }
    void addde(int a, int b)
    {
        adde(a, b);
        adde(b, a);
    }
    void pre()
    {
        dfs(1, 1, 0);
    }
    int querylca(int a, int b)
    {
        if (dep[a] > dep[b])
            swap(a, b);
        for (int i = 20; i >= 0; i--)
        {
            if (dep[a] <= dep[f[b][i]])
                b = f[b][i];
        }
        if (a == b)
            return a;
        for (int i = 20; i >= 0; i--)
        {
            if (f[a][i] == f[b][i])
                continue;
            a = f[a][i];
            b = f[b][i];
        }
        return f[a][0];
    }

  protected:
    struct Edge
    {
        int to, next;
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt;
    int n;
    int dep[MAXN];
    int dis[MAXN];
    int f[MAXN][22];

  private:
    void dfs(int u, int d, int fa)
    {
        dep[u] = d;
        f[u][0] = fa;
        for (int i = 1; i < 21; i++)
        {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (int i = head[u]; i != -1; i = e[i].next)
        {
            int v = e[i].to;
            if (dep[v] == -1)
            {
                dfs(v, d + 1, u);
            }
        }
    }
};