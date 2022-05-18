// set MAX_N and call fact_init();
vector<long long> Factorial(MAX_N + 1, 0);
void fact_init()
{
    Factorial[0] = Factorial[1] = 1;
    for (int i = 2; i <= MAX_N; i++)
        Factorial[i] = (Factorial[i - 1] * i) % MOD;
}

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

//returns (nCr) %MOD
long long nCr(int n, int r)
{
    if (r > n || r < 0)
        return 0;
    if (n == r || r == 0)
        return 1;
    return ((Factorial[n] * power(Factorial[r], MOD - 2)) % MOD * power(Factorial[n - r], MOD - 2)) % MOD;
}

// note: MAX_N >= 2*n
long long catalan_no(int n)
{
    return (nCr(2 * n, n) * power(n + 1, MOD - 2)) % MOD;
}
