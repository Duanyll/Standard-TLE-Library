#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 10;
const int SIGMA = 26;

struct suffix_array {
    int sa[MAXN];     // 排名为i的后缀的位置 sa[rnk[i]] = i
    int rnk[MAXN];     // 后缀i的排名 rnk[sa[i]] = i
    int bucket[MAXN];  // 元素i出现的次数
    int tp[MAXN];      // 基数排序的第二关键字

    int operator[](int x) { return sa[x]; }
    // str 下标从1开始
    suffix_array(char* str, int len) {
        memset(sa, 0, sizeof sa);
        memset(rnk, 0, sizeof rnk);
        memset(bucket, 0, sizeof bucket);
        int m = 200;
        for (int i = 1; i <= len; i++) {
            rnk[i] = str[i];
            bucket[rnk[i]]++;
        }
        for (int i = 1; i <= m; i++) {
            bucket[i] += bucket[i - 1];
        }
        for (int i = len; i >= 1; i--) {
            sa[bucket[rnk[i]]--] = i;
        }
        int k = 1, p;
        do {
            int cnt = 0;
            memset(bucket, 0, sizeof bucket);
            for (int i = len - k + 1; i <= len; i++) {
                tp[++cnt] = i;
            }
            for (int i = 1; i <= len; i++) {
                if (sa[i] > k) tp[++cnt] = sa[i] - k;
            }
            for (int i = 1; i <= len; i++) {
                bucket[rnk[i]]++;
            }
            for (int i = 1; i <= m; i++) {
                bucket[i] += bucket[i - 1];
            }
            for (int i = len; i >= 1; i--) {
                sa[bucket[rnk[tp[i]]]--] = tp[i];
            }
            p = 1;
            swap(rnk, tp);
            rnk[sa[1]] = 1;
            for (int i = 2; i <= len; i++) {
                rnk[sa[i]] = (tp[sa[i]] == tp[sa[i - 1]] &&
                               tp[sa[i] + k] == tp[sa[i - 1] + k])
                                  ? p
                                  : ++p;
            } 
            k <<= 1;
            m = p;
        } while (p < len);
    }
};