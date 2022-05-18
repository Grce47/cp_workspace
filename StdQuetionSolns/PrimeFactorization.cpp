
// method 1 -> O(sqrt(n)) per query

vi factorization(int n)
{
    if (n == 1)
        return {};
    vi ans;
    while (n % 2 == 0)
    {
        ans.pb(2);
        n /= 2;
    }
    int prime = 3;
    while (prime * prime <= n)
    {
        while (n % prime == 0)
        {
            ans.pb(prime);
            n /= prime;
        }
        prime += 2;
    }
    if (n > 2)
        ans.push_back(n);
    return ans;
}

// method 2 -> O(nlog(logn) + query*logn)

int spf[MAX_N];
void sieve()
{
    spf[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        spf[i] = i;

    for (int i = 4; i < MAX_N; i += 2)
        spf[i] = 2;

    for (int i = 3; i * i < MAX_N; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j < MAX_N; j += i)
                if (spf[j] == j)
                    spf[j] = i;
        }
    }
}

vector<int> getFactorization(int x)
{
    vector<int> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}


//end