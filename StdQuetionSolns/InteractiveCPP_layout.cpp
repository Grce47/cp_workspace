#include <bits/stdc++.h>
using namespace std;

//------------------------------------------------//
#if __has_include("../files/GR47_debug.cpp")
#include "../files/GR47_debug.cpp"
#endif
#ifdef GR47_LOCAL
#define deb(x)             \
    {                      \
        cerr << #x << " "; \
        _print(x);         \
        cerr << "\n";      \
    }
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
template <class T>
ostream &operator<<(ostream &os, const vector<T> a)
{
    for (auto ele : a)
        os << ele << " ";
    return os;
}
template <class T>
istream &operator>>(istream &is, vector<T> &a)
{
    for (auto &ele : a)
        is >> ele;
    return is;
}
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<long long> vl;
typedef vector<vector<long long>> vvl;
typedef vector<bool> vb;
typedef vector<vector<bool>> vvb;
typedef map<int, int> mii;
typedef map<long long, long long> mll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef unsigned long long ull;
typedef long double ld;
typedef long long ll;
//------------------------------------------------//

const long long MOD = 1000000007;
const int MAX_N = 500001;

int query_count;

int query()
{
#ifdef GR47_LOCAL
    // write logic
#endif
}

void answer()
{
}

void solve()
{
    query_count = 0;
}

int32_t main()
{
#ifdef GR47_LOCAL
    freopen("../files/input.txt", "r", stdin);
    freopen("../files/output.txt", "w", stdout);
    freopen("../files/error.txt", "w", stderr);
#endif

    int tc = 1;
    cin >> tc;
    for (int loop = 1; loop <= tc; loop++)
        solve();
    return 0;
}
