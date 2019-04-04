int mod;
template <typename T>
struct auto_mod {
    T val;
    auto_mod(T x) { val = ((x % mod) + mod) % mod; }
    auto_mod() { val = 0; }
    operator T() { return val; }
};
template <typename T>
static auto_mod<T> operator+(const auto_mod<T>& a, const auto_mod<T>& b) {
    return auto_mod<T>(a.val + b.val);
}
template <typename T>
static auto_mod<T> operator+=(auto_mod<T>& a, const T& b) {
    return a = auto_mod<T>(a.val + b);
}
template <typename T>
static auto_mod<T> operator+=(auto_mod<T>& a, const auto_mod<T>& b) {
    return a = auto_mod<T>(a.val + b.val);
}
template <typename T>
static auto_mod<T> operator-(const auto_mod<T>& a, const auto_mod<T>& b) {
    return auto_mod<T>(a.val - b.val);
}
template <typename T>
static auto_mod<T> operator*(const auto_mod<T>& a, const auto_mod<T>& b) {
    return auto_mod<T>(a.val * b.val);
}
