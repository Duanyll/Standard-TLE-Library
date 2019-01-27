#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
int a[MAXN];
int dp[MAXN];

int main(int argc, char const *argv[]) {
    ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            dp[i] = 1;
            for (int j = 1; j < i; j++) {
                if (a[i] > a[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        cout << dp[n] << endl;
    }
    return 0;
}
