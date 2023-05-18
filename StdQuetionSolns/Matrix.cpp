struct Matrix
{
    vector<vector<long long>> table;
    int n;
    Matrix(int N)
    {
        n = N;
        table.resize(n, vector<long long>(n, 0));
    }
    void add_mod(long long &a, long long b)
    {
        a = a + b;
        while (a < 0)
            a += MOD;
        a %= MOD;
    }
    long long mul_mod(long long a, long long b)
    {
        return (a * b) % MOD;
    }
    Matrix operator*(Matrix const &other)
    {
        Matrix res(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                    add_mod(res.table[i][j], mul_mod(table[i][k], other.table[k][j]));
            }
        }
        return res;
    }
    long long sum_of_all()
    {
        long long res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                add_mod(res, table[i][j]);
        }
        return res;
    }
};

Matrix power(Matrix base, long long k)
{
    Matrix res(base.n); // identity matrix
    for (int i = 0; i < base.n; i++)
        res.table[i][i] = 1;
    while (k)
    {
        if (k & 1)
            res = res * base;
        base = base * base;
        k = k >> 1;
    }
    return res;
}
