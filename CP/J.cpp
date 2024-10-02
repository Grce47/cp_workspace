#include <bits/stdc++.h>
using namespace std;

#ifdef GR47_LOCAL
#include "../files/GR47_debug.hpp"
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
#define sz(a) ((int)a.size())

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

typedef long long ll;

const long long MOD = 1000000007;
const int MAX_N = 500001;

void solve()
{
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifdef GR47_LOCAL
    freopen("../files/input.txt", "r", stdin);
    freopen("../files/output.txt", "w", stdout);
    freopen("../files/error.txt", "w", stderr);
#endif

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
