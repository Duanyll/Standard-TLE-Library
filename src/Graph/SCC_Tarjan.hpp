#include "LFS_base.hpp"
#include <stack>

class SCC_Tarjan : public LFS
{
  public:
    void solve()
    {
        memset(dfn, -1, sizeof dfn);
        memset(low, -1, sizeof low);
        memset(ins, false, sizeof ins);
        tim = 1;
        scccnt = 0;
        while (!s.empty())
        {
            s.pop();
        }
        tarjan(1);
    }

  protected:
    stack<int> s;
    bool ins[MAXN];
    int scccnt;
    int belong[MAXN];
    int mina[MAXN];
    int low[MAXN], dfn[MAXN];
    int tim;
    void tarjan(int u)
    {
        dfn[u] = low[u] = tim++;
        s.push(u);
        ins[u] = true;
        for (int i = head[u]; i != -1; i = e[i].next)
        {
            int v = e[i].to;
            if (dfn[v] == -1)
            {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else
            {
                if (ins[v])
                {
                    low[u] = min(low[u], dfn[v]);
                }
            }
        }
        if (dfn[u] == low[u])
        {
            scccnt++;
            int v = 0;
            while (v != u)
            {
                v = s.top();
                s.pop();
                ins[v] = false;
                belong[v] = scccnt;
            }
        }
    }
};