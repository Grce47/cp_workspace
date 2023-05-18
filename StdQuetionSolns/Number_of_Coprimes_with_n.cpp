// O (sqrt(n) + log(n))
// numbers <= m, coprime to n
int ncp(int n, int m)
{
    vector<int> prs;
    int n_cp = n;
    for (int i = 2; i * i <= n_cp; i++)   // O(sqrt(n) + log(n))
    {
        if (n_cp % i == 0)
        {
            prs.push_back(i);
            while (n_cp % i == 0)
                n_cp /= i;
        }
    }

    if (n_cp != 1)
        prs.push_back(n_cp);

    int ans = 0;
    int k = prs.size();                    // k < 9 -> n <= 1e9
    for (int i = 0; i < (1 << k); i++)     // Time < O (2**9 * 9) = O (4608)
    {
        int prod = 1;
        int mult = 1;
        for (int j = 0; j < k; j++)        
        {
            if ((i >> j) & 1)
            {
                mult *= -1;
                prod *= prs[j];
            }
        }
        ans += mult * (m / prod);
    }
    return ans;
}
