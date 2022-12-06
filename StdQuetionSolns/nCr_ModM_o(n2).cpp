// set MAX_N and call fact_init();
long long factorial[MAX_N], nCr[MAX_N][MAX_N];
void fact_init()
{
    factorial[0] = factorial[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        factorial[i] = (factorial[i - 1] * i) % MOD;

    for (int i = 0; i < MAX_N; i++)
        nCr[i][0] = 1;

    for (int i = 1; i < MAX_N; i++)
        for (int j = 1; j < MAX_N; j++)
            nCr[i][j] = (nCr[i - 1][j] + nCr[i - 1][j - 1]) % MOD;
}
