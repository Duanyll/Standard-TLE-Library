#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long int64;
const int MOD = 1e8;

template <typename T, size_t h, size_t w>
class matrix : public vector<vector<T>> {
   public:
   	matrix(T val = 0) : vector<vector<T>>(h, vector<T>(w, val)) {}
   	matrix(const initializer_list<vector<T>>& li) : vector<vector<T>>() {
   		for (auto i : li) {
   			this->push_back(i);
   		}
   	}
	matrix<T, h, w> pow(int64 p) {
		static_assert(h == w, "height must equal width.");
		matrix<T, h, w> ret = unit();
		matrix<T, h, w> a(*this);
		while(p > 0) {
			if (p & 1) {
				ret = ret * a;
			}
			a = a * a;
			p >>= 1;
		}
		return ret;
	}
	static matrix<T, h, w> unit() {
		static_assert(h == w, "height must equal width.");
		matrix<T, h, w> ret(0);
		for (size_t i = 0; i < h; i++) {
			ret[i][i] = 1;
		}
		return ret;
	}
};

template <typename T, size_t h, size_t w>
matrix<T, h, w> operator+(const matrix<T, h, w>& a, const matrix<T, h, w>& b) {
	matrix<T, h, w> ans;
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0;j < w; j++) {
			ans[i][j] = a[i][j] + b[i][j];
			ans[i][j] = (ans[i][j] % MOD + MOD) % MOD;
		}
	}
	return ans;
}

template <typename T, size_t h, size_t w>
matrix<T, h, w> operator-(const matrix<T, h, w>& a, const matrix<T, h, w>& b) {
	matrix<T, h, w> ans;
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0;j < w; j++) {
			ans[i][j] = a[i][j] - b[i][j];
			ans[i][j] = (ans[i][j] % MOD + MOD) % MOD;
		}
	}
	return ans;
}

template <typename T, size_t h, size_t w, size_t w1>
matrix<T, h, w> operator*(const matrix<T, h, w1>& a, const matrix<T, w1, w>& b) {
	matrix<T, h, w> ans;
	for (size_t k = 0; k < w1; k++) {
		for (size_t i = 0; i < h; i++) {
			if (a[i][k] == 0) continue;
			for (size_t j = 0; j < w; j++) {
				ans[i][j] += a[i][k] * b[k][j];
				ans[i][j] %= MOD;
			}
		}
	}
	return ans;
}
