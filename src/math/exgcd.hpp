template <typename T>
T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    T g = exgcd(b, a % b, x, y);
    T tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

template <typename T>
T inv1(T a, T mod) {
    T x, y;
    T d = exgcd(a, mod, x, y);
    if (d == 1) return (x % mod + mod) % mod;
    return -1;
}