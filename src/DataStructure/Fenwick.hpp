#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

template <typename value_t>
class fenwick
{
  public:
	fenwick(int n)
	{
		memset(c, 0, sizeof c);
		this->n = n;
	}

	void add(int i, value_t x)
	{
		while (i <= n)
		{
			c[i] += x;
			i += Lowbit(i);
		}
	}

	value_t sum(int x)
	{
		value_t sum = 0;
		while (x > 0)
		{
			sum += c[x];
			x -= Lowbit(x);
		}
		return sum;
	}

	value_t sum(int x1, int x2)
	{
		return sum(x2) - sum(x1 - 1);
	}

  private:
	value_t c[MAXN];
	int n;

	inline int Lowbit(int x)
	{
		return x & (-x);
	}
};
