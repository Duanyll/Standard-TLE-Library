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

template <typename value_t>
class fenwick {
   public:
    fenwick(int n) : n(n), c(n + 1, 0) {}

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
    vector<value_t> c;
    int n;

    inline int Lowbit(int x) { return x & (-x); }
};
