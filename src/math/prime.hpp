#include <cstring>

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