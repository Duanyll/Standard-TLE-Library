int exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    int GCD = exgcd(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - a / b * y;
    return GCD;
}

int inv1(int a, int MOD)
{
    int x, y;
    int d = exgcd(a, MOD, x, y);
    if (d == 1)
        return (x % MOD + MOD) % MOD;
    return -1;
}
