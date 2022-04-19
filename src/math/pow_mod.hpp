template <typename T>
T pow_mod(T a, T b, T MOD) {
    T res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}