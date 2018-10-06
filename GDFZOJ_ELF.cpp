#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 10;
const int MOD = 201314;

inline int read()
{
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

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
    int dep[MAXN];

  protected:
    struct Edge
    {
        int to, next;
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt;
    int n;
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

int l[MAXN], r[MAXN], z[MAXN];
int sum[MAXN];

int main(int argc, char const *argv[])
{
    freopen("elf4.in","r",stdin);
    freopen("elf3.ans","w",stdout);
    int n, q;
    n = read();
    q = read();
    LCA *map = new LCA(n);
    bool islink = true;
    for (int i = 2; i <= n; i++)
    {
        int f = read();
        map->addde(f, i);
        if (f != i - 1)
        {
            islink = false;
        }
    }
    bool zsame = true;
    for (int i = 0; i < q; i++)
    {
        l[i] = read();
        r[i] = read();
        z[i] = read();
        if (i > 0 && z[i] != z[i - 1])
        {
            zsame = false;
        }
    }    
    if (zsame)
    {
        map->pre();
        sum[0] = 0;
        sum[1] = map->querylca(z[0], 1) % MOD;
        for (int i = 2; i <= n; i++)
        {
            sum[i] = (sum[i - 1] + map->querylca(z[0], i)) % MOD;
        }
        for (int i = 0; i < q; i++)
        {
            cout << (sum[r[i]] - sum[l[i] - 1]) % MOD << endl;
        }
        delete map;
        return 0;
    }
    if (islink)
    {
        sum[0] = 0;
        sum[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            sum[i] = (sum[i - 1] + i) % MOD;
        }
        for (int i = 0; i < q; i++)
        {
            if (r[i] < z[i])
            {
                cout << (sum[r[i]] - sum[l[i] - 1]) % MOD << endl;
            }
            else
            {
                if (l[i] > z[i])
                {
                    cout << (z[i] * (r[i] - l[i] + 1)) % MOD << endl;
                }
                else
                {
                    cout << ((sum[z[i]] - sum[l[i] - 1]) % MOD + (z[i] * (r[i] - z[i])) % MOD) % MOD << endl;
                }
            }
        }
        delete map;
        return 0;
    }
    map->pre();
    for (int i = 0; i < q; i++)
    {
        int ans = 0;
        for (int j = l[i]; j <= r[i]; j++)
        {
            ans += map->dep[map->querylca(z[i], j)];
            ans %= MOD;
        }
        cout << ans << endl;
    }
    delete map;
    return 0;
}
