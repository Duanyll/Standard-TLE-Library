#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long int64;

namespace polynomial
{
    const double PI = acos(-1);

    template <typename T>
    struct point
    {
        T x, y;
        point() : x(0), y(0) {}
        point(T X, T Y) : x(X), y(Y) {}
    };
    template <typename T>
    point<T> operator+(const point<T> &a, const point<T> &b)
    {
        return point<T>(a.x + b.x, a.y + b.y);
    }
    template <typename T>
    point<T> operator-(const point<T> &a, const point<T> &b)
    {
        return point<T>(a.x - b.x, a.y - b.y);
    }
    template <typename T>
    point<T> cross(const point<T> &a, const point<T> &b)
    {
        return point<T>(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }

    typedef point<double> complex;
    inline complex operator*(const complex &a, const complex &b) { return cross(a, b); }

    void fft(complex *f, int limit, int reverse, const int *r)
    {
        for (int i = 0; i < limit; i++)
        {
            if (i < r[i])
                swap(f[i], f[r[i]]);
        }
        for (int j = 1; j < limit; j <<= 1)
        {
            complex omega(cos(PI / j), reverse * sin(PI / j));
            for (int k = 0; k < limit; k += (j << 1))
            {
                complex cur(1, 0);
                for (int l = 0; l < j; l++, cur = cur * omega)
                {
                    complex nx = f[k + l], ny = cur * f[k + j + l];
                    f[k + l] = nx + ny;
                    f[k + j + l] = nx - ny;
                }
            }
        }
    }

    template <typename T = int>
    T *multiplicate_coefficient(complex *a, int n, complex *b, int m)
    {
        int lim = 1, l = 0;
        while (lim <= n + m)
        {
            lim <<= 1;
            l++;
        }
        int *r = new int[lim + 10];
        memset(r, 0, (lim + 10) * sizeof(int));
        for (int i = 0; i < lim; i++)
        {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
        }
        fft(a, lim, 1, r);
        fft(b, lim, 1, r);
        for (int i = 0; i <= lim; i++)
        {
            a[i] = a[i] * b[i];
        }
        fft(a, lim, -1, r);
        delete[] r;
        T *ans = new T[n + m + 1];
        for (int i = 0; i <= n + m; i++)
        {
            ans[i] = (T)(a[i].x / lim + 0.5);
        }
        return ans;
    }

    const int64 P = 998244353;
    const int64 G = 3;

    template <typename T>
    T pow_mod(T a, T b, T MOD)
    {
        T res = 1;
        while (b)
        {
            if (b & 1)
                res = res * a % MOD;
            a = a * a % MOD;
            b /= 2;
        }
        return res;
    }

    int64 inv = pow_mod(G, P - 2, P);

    void ntt(int64 *f, int limit, bool reverse, const int *r)
    {
        for (int i = 0; i < limit; i++)
        {
            if (i < r[i])
                swap(f[i], f[r[i]]);
        }
        for (int j = 1; j < limit; j <<= 1)
        {
            int64 omega =
                reverse ? pow_mod(G, (P - 1) / (j << 1), P) : pow_mod(inv, (P - 1) / (j << 1), P);
            for (int k = 0; k < limit; k += (j << 1))
            {
                int64 cur = 1;
                for (int l = 0; l < j; l++)
                {
                    int64 nx = f[k + l], ny = (cur * f[k + j + l]) % P;
                    f[k + l] = (nx + ny) % P;
                    f[k + j + l] = (nx - ny + P) % P;
                    cur = (cur * omega) % P;
                }
            }
        }
    }

    // template <typename T = int64>
    void multiplicate_coefficient(int64 *a, int n, int64 *b, int m)
    {
        int lim = 1, l = 0;
        while (lim <= n + m)
        {
            lim <<= 1;
            l++;
        }

        int *r = new int[lim + 10];
        memset(r, 0, (lim + 10) * sizeof(int));
        for (int i = 0; i < lim; i++)
        {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
        }
        ntt(a, lim, false, r);
        ntt(b, lim, false, r);
        for (int i = 0; i <= lim; i++)
        {
            a[i] = a[i] * b[i];
        }
        ntt(a, lim, true, r);
        int64 inv = pow_mod<int64>(lim, P - 2, P);
        for (int i = 0; i <= lim; i++)
        {
            a[i] = a[i] * inv % P;
        }
        delete[] r;
    }
};