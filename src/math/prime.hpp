#include <cstring>
#include "pow_mod.hpp"

typedef long long int64;

const int MAXA = 5e6 + 10;
const int AMXA = 5e6;

int prime[MAXA];
bool isntp[MAXA];
int prime_cnt;

void make_prime() {
    prime_cnt = 0;
    memset(isntp, false, sizeof(isntp));
    for (int i = 2; i <= AMXA; ++i) {
        if (!isntp[i]) {
            prime[prime_cnt++] = i;
        }
        for (int j = 0; j < prime_cnt; ++j) {
            if (i * prime[j] > AMXA) {
                break;
            }
            isntp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

int phi[MAXA];

void init_phi() {
    phi[1] = 1;
    for (int i = 2; i <= AMXA; i++) {
        if (!isntp[i]) {
            prime[++prime_cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= prime_cnt && i * prime[j] <= AMXA; j++) {
            isntp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

bool mr(int64 x, int64 b) {
    int64 d, p = 0;
    d = x - 1;
    while ((d & 1) == 0) d >>= 1, ++p;
    int i;
    int64 cur = pow_mod(b, d, x);  //快速幂
    if (cur == 1 || cur == x - 1) return true;
    for (i = 1; i <= p; ++i) {
        cur = cur * cur % x;
        //为了防止溢出,这里最好用快速乘或者直接用__int128转化一下
        if (cur == x - 1) return true;
    }
    if (i > p) return false;
}
bool is_not_prime(int64 x) {
    if (x == 46856248255981 || x < 2) return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251) return true;
    return mr(x, 2) && mr(x, 3) && mr(x, 7) && mr(x, 61) && mr(x, 24251);
}