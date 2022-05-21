#include <bits/stdc++.h>
using namespace std;

//------------------------------------------------//
#if __has_include("../files/GR47_debug.cpp")
#include "../files/GR47_debug.cpp"
#endif
#ifdef GR47_LOCAL
#define deb(x) {cerr << #x << " "; _print(x); cerr << "\n";}
#else
#define deb(x)
#endif
#define rep(i, a, b) for (int i = a; i < b; i++)
#define precision(a) cout << setprecision(a) << fixed
#define MSB(x) (63 - __builtin_clzll(x))
#define amax(a, b) a = max(a, b)
#define amin(a, b) a = min(a, b)
#define MP make_pair
#define all(a) a.begin(), a.end()
typedef vector<int> vi; typedef vector<vector<int>> vvi; typedef vector<long long> vl; typedef vector<vector<long long>> vvl; typedef vector<bool> vb; typedef vector<vector<bool>> vvb; typedef map<int, int> mii; typedef map<long long, long long> mll; typedef pair<int, int> pii; typedef pair<long long, long long> pll; typedef unsigned long long ull; typedef long double ld; typedef long long ll;
//------------------------------------------------//

const long long MOD = 998244353;
const int MAX_N = 500001;

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

bitset<MAX_N> isprime;
void eratosthenes_sieve()
{
	isprime.set();
	isprime[0] = isprime[1] = 0;
	for (int i = 4; i < MAX_N; i += 2)
		isprime[i] = 0;
	for (int i = 3; i * i < MAX_N; i += 2)
		if (isprime[i])
			for (int j = i * i; j < MAX_N; j += i * 2)
				isprime[j] = 0;
}

vector<int> primes;
int N;
void init(int n)
{
    primes.clear();

    for(int i=0;i<=n;i++)
    {
        if(isprime[i])
        {
            primes.push_back(i);
        }
    }
    N = primes.size();

}

vector<vector<pair<int,pii>>> tree;
vector<vvi> pow_cnt;

void dfs(int cur,int par)
{
    for(auto ele : tree[cur])
    {
        int ch = ele.first,a = ele.second.first,b = ele.second.second;
        if(ch == par) continue;

        for(int i=0;i<N;i++)
        {
            pow_cnt[cur][0][i] = pow_cnt[ch][0][i];
            pow_cnt[cur][1][i] = pow_cnt[ch][1][i];
            
            int a_pow = 0,b_pow = 0;
            while(a > 0)
            {
                if(a%primes[i] != 0) break;
                a_pow++;
                a = a / primes[i];
            }
            while (b > 0)
            {
                if(b%primes[i] != 0) break;
                b_pow++;
                b = b/primes[i];
            }
            
            pow_cnt[ch][0][i] += b_pow;
            pow_cnt[ch][1][i] += a_pow;

            dfs(ch,cur);
        }

    }
}

void solve()
{
    int n;
    cin>>n;
    init(n);
    tree.clear();
    tree.resize(n);
    pow_cnt.clear();
    pow_cnt.resize(n,vvi(2,vi(primes.size())));

    rep(i,0,n-1)
    {
        int x,y,a,b;
        cin>>x>>y>>a>>b;
        x--;y--;
        int gc = __gcd(a,b);
        a /= gc;
        b /= gc;

        tree[x].push_back(MP(y,MP(a,b)));
        tree[y].push_back(MP(x,MP(b,a)));
    }

    dfs(0,0);

    vi den_lcm(N);

    rep(i,0,N)
    {
        rep(j,1,n)
        {
            den_lcm[i] = max(den_lcm[i],pow_cnt[j][1][i]);
        }
    }

    rep(i,0,n)
    {
        rep(j,0,N)
        {
            int rem = den_lcm[j] - pow_cnt[i][1][j];
            pow_cnt[i][1][j] = 0;
            pow_cnt[i][0][j] += rem;
        }
    }

    ll ans = 0;

    rep(i,0,n)
    {
        ll tmp_ans = 1;
        deb(pow_cnt[i][0]);
        rep(j,0,N)
        {
            tmp_ans = (tmp_ans * power(primes[j],pow_cnt[i][0][j])) % MOD;
        }
        ans = (ans + tmp_ans) %MOD;
    }
    deb(primes);
    cout<<ans<<"\n";
}

int32_t main()
{
// #define DEBUG_MODE
#ifndef DEBUG_MODE
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

#ifdef GR47_LOCAL
    freopen("../files/input.txt", "r", stdin); freopen("../files/output.txt", "w", stdout); freopen("../files/error.txt", "w", stderr);
#endif
#else
#ifdef GR47_LOCAL
    freopen("../files/input.txt", "r", stdin);
#endif
#endif

    eratosthenes_sieve();

    int tc = 1;
    cin >> tc;
    for (int loop = 1; loop <= tc; loop++)
    {
        // cout << "Case #" << loop << ": ";
        solve();
        // bool as = solve(); cout << (as ? "YES\n" : "NO\n");
        // int as = solve(); cout << as << "\n";
    }
    return 0;
}

/*
    Thu May 19 11:42:19 2022
    File : D.cpp
*/
