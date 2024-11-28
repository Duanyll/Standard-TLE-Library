#include <unordered_map>
#include <vector>
using namespace std;

const int MAXN = 1e6;

class du_sieve {
   private:
    int phi[MAXN + 5], mu[MAXN + 5], cnt, N;
    unordered_map<int, int> vphi, vmu;
    bool vis[MAXN + 5];
    vector<int> prime;

   public:
    void make_prime(int limit) {
        mu[1] = phi[1] = 1;
        for (int i = 2; i <= limit; i++) {
            if (!vis[i]) {
                prime.push_back(i);
                phi[i] = i - 1, mu[i] = -1;
            }
            for (int j = 0; j < prime.size() && i * prime[j] <= limit; j++) {
                vis[i * prime[j]] = 1;
                if (i % prime[j] == 0) {
                    phi[i * prime[j]] = phi[i] * prime[j];
                    break;
                }
                phi[i * prime[j]] = phi[prime[j]] * phi[i];
                mu[i * prime[j]] = -mu[i];
            }
        }
        for (int i = 1; i <= limit; i++)
            phi[i] += phi[i - 1], mu[i] += mu[i - 1];
    }
    int Phi(int x) {
        if (x <= N) return phi[x];
        if (vphi.count(x)) return vphi[x];
        int ans = (1 + x) * x / 2;
        for (int i = 2, j; i <= x; i = j + 1) {
            j = x / (x / i);
            ans -= (j - i + 1) * Phi(x / i);
        }
        return vphi[x] = ans;
    }
    int Mu(int x) {
        if (x <= N) return mu[x];
        if (vmu.count(x)) return vmu[x];
        int ans = 1;
        for (int i = 2, j; i <= x; i = j + 1) {
            j = x / (x / i);
            ans -= (j - i + 1) * Mu(x / i);
        }
        return vmu[x] = ans;
    }
    du_sieve(int n) {
        N = n;
        make_prime(n);
    }
};