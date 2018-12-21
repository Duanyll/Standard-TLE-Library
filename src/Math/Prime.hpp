#include <cstring>

const int MAXN = 500010;
const int MAXANS = 5e6 + 10;

int prime[MAXN];
bool isntp[MAXANS];
int pcnt;

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