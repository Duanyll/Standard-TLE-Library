#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;

#define SEED time(0)
const double TBEGIN = 3000;
const double EPS = 1e-14;
const double TEND = EPS;
const double DELTAT = 0.99;
const double INF = 1e18;
template <typename T, typename TComp>
T SA(T s)
{
	srand(SEED);
	double t = TBEGIN;
	double ans = INF;
	T now = s;
	while (t > EPS)
	{
		T n = now.get_new([](double t) -> double {
			return (rand() * 2 - RAND_MAX) * t;
		},
						  t);
		double nans = n.get_ans();
		if (TComp()(nans, ans))
		{
			ans = nans;
			now = n;
		}
		else
		{
			if (exp((ans - nans) / t) * RAND_MAX > rand())
			{
				now = n;
			}
		}
		t *= DELTAT;
	}
	return now;
}

const double MAX_TIME = 0.8;
template <typename T, typename TComp>
T SA_Time(T s)
{
	state ans = SA<state, TComp>(s);
	while ((double)clock() / CLOCKS_PER_SEC < MAX_TIME)
		ans = SA<state, TComp>(ans);
	return ans;
}
