#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 5e5 + 10;

template<typename T,typename TMerge>
class spharse_table {
	protected:
		T st[MAXN][22];
		// st[i][j]:从i开始,长度为1<<j的区间的最大值
	public:
		spharse_table(int n, const int *a) {
			memset(st,0,sizeof st);
    		for (int i = 1; i <= n; i++) {
        		st[i][0] = a[i];
    		}
    		for (int j = 1; (1 << j) <= n; j++) {
        		for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            		st[i][j] = TMerge()(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            		//递推:每一节的最大值等于前半截和后半截的最大值
        		}
    		}
		}

		T query(int l, int r) {
    		int k = 0;
    		while ((1 << (k + 1)) <= r - l + 1) {
        		k++;
    		}
    		return TMerge()(st[l][k], st[r - (1 << k) + 1][k]);
    		//前后等长两节区间,区间可重复
		}
};

template<typename T>
struct maximize{
	T operator()(const T& a,const T& b) const {
		return max(a,b);
	}
};

template<typename T>
struct minimize{
	T operator()(const T& a,const T& b) const {
		return min(a,b);
	}
};
