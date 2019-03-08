#include <cctype>
#include <cstdio>

inline int read() {
    int X = 0, w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) {
        X = (X << 3) + (X << 1) + (ch ^ 48);
        ch = getchar();
    }
    return w ? -X : X;
}

inline double dbread() {
    double X = 0, Y = 1.0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = X * 10 + (ch ^ 48), ch = getchar();
    ch = getchar();  //读入小数点
    while (isdigit(ch)) X += (Y /= 10) * (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
