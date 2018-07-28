#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

class LFS
{
  public:
	LFS()
	{
	}
	LFS(int N)
	{
		memset(head, -1, sizeof head);
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

  protected:
	struct Edge
	{
		int to, next, w;
	} e[MAXN * 2];
	int head[MAXN];
	int ecnt;
	int n;

  private:
	void dfs(int u, int fa)
	{
		for (int i = head[u]; i != -1; i = e[i].next)
		{
			int v = e[i].to;
			if (v != fa)
			{
				dfs(v, u);
			}
		}
	}
};
