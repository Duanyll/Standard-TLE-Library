template <typename T>
T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    T GCD = exgcd(b, a % b, x, y);
    T tmp = x;
    x = y;
    y = tmp - a / b * y;
    return GCD;
}

template <typename T>
T inv1(T a, T MOD) {
    T x, y;
    T d = exgcd(a, MOD, x, y);
    if (d == 1) return (x % MOD + MOD) % MOD;
    return -1;
}
