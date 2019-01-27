#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e5;

namespace STTable {
int a[MAXN];
int st[MAXN][20];
// st[i][j]:从i开始,长度为1<<j的区间的最大值

void init(int n) {
    for (int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            //递推:每一节的最大值等于前半截和后半截的最大值
        }
    }
}

int query(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) {
        k++;
    }
    return max(st[l][k], st[r - (1 << k) + 1][k]);
    //前后等长两节区间,区间可重复
}
}  // namespace STTable