#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

template <typename value_t>
class fenwick {
   public:
    fenwick(int n) : n(n), c(n + 1, 0) {}

    void add(int i, value_t x) {
        while (i <= n) {
            c[i] += x;
            i += lowbit(i);
        }
    }

    value_t sum(int x) {
        value_t sum = 0;
        while (x > 0) {
            sum += c[x];
            x -= lowbit(x);
        }
        return sum;
    }

    value_t sum(int l, int r) { return sum(r) - sum(l - 1); }

   private:
    vector<value_t> c;
    int n;

    inline int lowbit(int x) { return x & (-x); }
};
