#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-8;

int dcmp(double x, double y) {
	double c = x - y;
	if (c > EPS) return 1;
	if (c < -EPS) return -1;
	return 0;
}

template <typename T>
bool gauss(const vector<vector<T>>& in, vector<T>& out) {
	vector<vector<T>> a(in);
	size_t n = in.size();
	// i 枚举列 
	for (size_t i = 0; i < n; i++) {
		// 选定当前列的最大系数项 
		size_t mxid = i;
		for (size_t j = i + 1; j < n; j++) {
			if (dcmp(fabs(a[j][i]), fabs(a[mxid][i])) == 1) {
				mxid = j;
			}
		}
		// 提到当前排 
		swap(a[i], a[mxid]);
		if (a[i][i] == 0) return false;
		for (size_t j = 0; j < n; j++) {
			if (j == i) continue;
			T mi = a[j][i] / a[i][i];
			for (size_t k = i + 1; k <= n; k++) {
				a[j][k] -= a[i][k] * mi;
			}
		} 
	}
	
	out = vector<T>(n, 0);
	for (size_t i = 0; i < n; i++) {
		out[i] = a[i][n] / a[i][i];
	}
	return true;
}

template <typename T>
T det(vector<vector<T>> a, T mod, int n = -1) {
    T symbol = 1;
    if (n == -1) n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (a[i][i] != 0) {
                T d = a[j][i] / a[i][i] % mod;
                for (int k = i; k < n; k++) {
                    a[j][k] -= a[i][k] * d % mod;
                    a[j][k] = (a[j][k] % mod + mod) % mod;
                }
                swap(a[i], a[j]);
                symbol = -symbol;
            }
            swap(a[i], a[j]);
            symbol = -symbol;
        }
    }

    T ans = symbol;
    for (int i = 0; i < n; i++) {
        ans *= a[i][i];
        ans %= mod;
    }
    return (ans + mod) % mod;
}