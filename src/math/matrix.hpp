#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

typedef long long int64;
const int MOD = 1e9 + 7;

template <typename T>
class matrix : public vector<vector<T>> {
   public:
   	matrix(int h = 0, int w = 0, T val = 0) : vector<vector<T>>(h, vector<T>(w, val)), width(w), height(h) {}
	int width, height;
	matrix<T> pow(int64 p) {
		assert(width == height);
		matrix<T> ret = unit(width);
		matrix<T> a(*this);
		while(p > 0) {
			if (p & 1) {
				ret = ret * a;
			}
			a = a * a;
			p >>= 1;
		}
		return ret;
	}
	static matrix<T> unit(int n) {
		matrix<T> ret(n, n, 0);
		for (int i = 0; i < n; i++) {
			ret[i][i] = 1;
		}
		return ret;
	}
};

template <typename T>
matrix<T> operator+(const matrix<T>& a, const matrix<T>& b) {
	assert(a.height == b.height && a.width == b.width);
	matrix<T> ans(a.width, a.height);
	for (int i = 0; i < a.height; i++) {
		for (int j = 0;j < a.width; j++) {
			ans[i][j] = a[i][j] + b[i][j];
			ans[i][j] %= MOD;
		}
	}
	return ans;
}

template <typename T>
matrix<T> operator-(const matrix<T>& a, const matrix<T>& b) {
	assert(a.height == b.height && a.width == b.width);
	matrix<T> ans(a.width, a.height);
	for (int i = 0; i < a.height; i++) {
		for (int j = 0;j < a.width; j++) {
			ans[i][j] = a[i][j] - b[i][j];
			ans[i][j] %= MOD;
		}
	}
	return ans;
}

template <typename T>
matrix<T> operator*(const matrix<T>& a, const matrix<T>& b) {
	assert(a.width == b.height);
	matrix<T> ans(a.height, b.width);
	for (int i = 0; i < a.height; i++) {
		for (int j = 0;j < b.width; j++) {
			for (int k = 0; k < a.width; k++) {
				ans[i][j] += a[i][k] * b[k][j];
				ans[i][j] %= MOD;
			}
		}
	}
	return ans;
}
