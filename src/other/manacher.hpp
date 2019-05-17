#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const char BLANK = -1;

template <typename T>
int manacher(T* a, size_t len) {
    T* s = new T[len * 2 + 10];
    int* p = new int[len * 2 + 10];
    memset(s, 0, (len * 2 + 10) * sizeof(T));
    memset(p, 0, (len * 2 + 10) * sizeof(int));
    
    s[0] = s[1] = BLANK;
    for (int i = 0; i < len;i++) {
        s[i * 2 + 2] = a[i];
        s[i * 2 + 3] = BLANK;
    }
    len = len * 2 + 2;
    s[len] = 0;
    
    int mxpos = 0, mxaxis = 0;
    for (int i = 1; i < len; i++) {
        if (i < mxpos) {
            p[i] = min(p[mxaxis * 2 - i], p[mxaxis] + mxaxis - i);
        } else {
            p[i] = 1;
        }
        while (s[i + p[i]] == s[i - p[i]]) {
            p[i]++;
        }
        if (p[i] + i > mxpos) {
            mxpos = p[i] + i;
            mxaxis = i;
        }
    }
    
    int ans = 1;
    for (int i = 0; i < len; i++) {
        ans = max(ans, p[i]);
    }
    
    delete[] s;
    delete[] p;
    return ans - 1;
}
