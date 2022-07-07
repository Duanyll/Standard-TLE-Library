#include <cctype>
#include <cstdio>

#define getchar()                                                              \
    (frS == frT &&                                                             \
             (frT = (frS = frBB) + fread(frBB, 1, 1 << 15, stdin), frS == frT) \
         ? EOF                                                                 \
         : *frS++)
char frBB[1 << 15], *frS = frBB, *frT = frBB;

template <typename T = int>
T read() {
    T x = 0;
    bool negative = false;
    char ch = '\0';
    while (!isdigit(ch))
    {
        negative |= (ch == '-');
        ch = getchar();
    }
    while (isdigit(ch)) {
        x *= 10;
        x += ch - '0';
        ch = getchar();
    }
    return negative ? -x : x;
}

double dbread() {
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
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
