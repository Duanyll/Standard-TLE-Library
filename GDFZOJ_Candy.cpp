#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;

typedef long long int64;

const int MAXN = 500010;
const int MAXANS = 5e6 + 10;

int prime[MAXN];
bool isntp[MAXANS];
int pcnt;

int mod(int cnt, int b)
{
    int ans = 0;
    for (int i = 0; i < cnt; i++)
    {
        ans = (ans * 10 + 1) % b;
    }
    return ans;
}

void makeprime()
{
    pcnt = 0;
    memset(isntp, false, sizeof(isntp));
    for (int i = 2; i < MAXANS; ++i)
    {
        if (!isntp[i])
        {
            prime[pcnt++] = i;
        }
        for (int j = 0; j < pcnt; ++j)
        {
            if (i * prime[j] > MAXANS)
            {
                break;
            }
            isntp[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
}

char a[MAXN];

int main(int argc, char const *argv[])
{
    char now = getchar();
    int n = 0;
    while (isdigit(now))
    {
        a[n++] = now;
        now = getchar();
    }
    int tot = 0;
    for (int i = 0; i < n; i++)
    {
        tot += a[i] - '0';
    }
    if (tot % 2 == 0)
    {
        cout << 2 << endl;
        return 0;
    }
    makeprime();
    int ptot = tot;
    for (int i = 0; i < pcnt; i++)
    {
        if (prime[i] > tot)
        {
            break;
        }
        if (tot % prime[i] == 0)
        {
            ptot = prime[i];
            break;
        }
    }
    int p1 = MAXANS;
    for (int i = 0; i < pcnt; i++)
    {
        if (prime[i] > ptot)
        {
            break;
        }
        if (mod(n, prime[i]) == 0)
        {
            p1 = prime[i];
            break;
        }
    }
    cout << min(ptot, p1) << endl;
    return 0;
}
