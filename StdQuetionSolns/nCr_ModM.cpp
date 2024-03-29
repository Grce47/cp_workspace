// returns (a^n) % MOD
long long power(long long a, long long n)
{
    long long res = 1;
    while (n)
    {
        if (n & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        n = n >> 1;
    }
    return res;
}

// set MAX_N and call fact_init();
long long factorial[MAX_N], inv_factorial[MAX_N];
void fact_init()
{
    factorial[0] = factorial[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        factorial[i] = (factorial[i - 1] * i) % MOD;

    for (int i = 0; i < MAX_N; i++)
        inv_factorial[i] = power(factorial[i], MOD - 2);
}

// returns (nCr) %MOD
long long nCr(int n, int r)
{
    if (r > n || r < 0)
        return 0;
    if (n == r || r == 0)
        return 1;
    return ((factorial[n] * inv_factorial[r]) % MOD * inv_factorial[n - r]) % MOD;
}

// note: MAX_N >= 2*n
long long catalan_no(int n)
{
    return (nCr(2 * n, n) * power(n + 1, MOD - 2)) % MOD;
}
