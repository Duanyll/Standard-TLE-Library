#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXM = 1e4 + 10;
const int MAXN = 1e6 + 10;

template <typename value_t>
struct kmp {
   public:
    // S:源串    T:模式串
    int operator()(const value_t *S, const int n, const value_t *T,
                   const int m) {
        getnext(T, m);
        return search(S, n, T, m);
    }

   private:
    int next[MAXM];
    void getnext(const value_t *T, const int m) {
        int j = 0, k = -1;  // j前缀，p后缀
        next[0] = -1;
        while (j < m - 1) {
            if (k == -1 || T[j] == T[k]) {
                j++;
                k++;
                if (T[j] != T[k]) {
                    next[j] = k;
                } else {
                    next[j] = next[k];
                }
            } else {
                k = next[k];
            }
        }
    }
    int search(const value_t *S, const int n, const value_t *T, const int m) {
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (j == -1 || S[i] == T[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
        if (j == m) {
            return i - j;
        } else {
            return -1;
        }
    }
    int count(const value_t *S, const int n, const value_t *T, const int m) {
        int i = 0, j = 0;
        int ans = 0;
        while (i < n && j < m) {
            if (j == -1 || S[i] == T[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
        if (j == m) {
            ans++;
            j = next[m - 1] + 1;
        } else {
            return -1;
        }
    }
};