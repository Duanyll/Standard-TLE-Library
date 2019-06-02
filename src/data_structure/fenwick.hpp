#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

template <typename value_t, size_t SIZE>
class fenwick {
   public:
    fenwick(int n) {
        memset(c, 0, sizeof c);
        this->n = n;
    }

    void add(int i, value_t x) {
        while (i <= n) {
            c[i] += x;
            i += Lowbit(i);
        }
    }

    value_t sum(int x) {
        value_t sum = 0;
        while (x > 0) {
            sum += c[x];
            x -= Lowbit(x);
        }
        return sum;
    }

    value_t sum(int x1, int x2) { return sum(x2) - sum(x1 - 1); }

   private:
    value_t c[SIZE];
    int n;

    inline int Lowbit(int x) { return x & (-x); }
};
