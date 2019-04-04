typedef long long int64;

int64 pow_mod(int64 a, int64 b, int MOD) {
    int64 res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}