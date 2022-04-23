#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <functional>
#include <random>
using namespace std;

const double TBEGIN = 3000;
const double EPS = 1e-14;
const double TEND = EPS;
const double DELTAT = 0.99;
const double INF = 1e18;

template <typename TValue>
TValue sa(function<void(function<double()>)> step, function<TValue()> f,
          function<void(bool)> update,
          decltype(mt19937::default_seed) seed =
              chrono::steady_clock::now().time_since_epoch().count()) {
    double t = TBEGIN;
    double ans = INF;
    mt19937 rd(seed);
    while (t > EPS) {
        uniform_real_distribution dis(0, t);
        step([&]() -> auto { return dis(rd); });
        TValue cur = f();
        if (cur < ans) {
            ans = cur;
            update(true);
        } else {
            bernoulli_distribution accept(max(1.0lf, exp((ans - nans) / t)));
            if (accept(rd)) {
                update(true);
            } else {
                update(false);
            }
        }
        t *= DELTAT;
    }
    return ans;
}