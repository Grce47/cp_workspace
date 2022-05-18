#include <bits/stdc++.h>
using namespace std;

// #define GR47
#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define precision(a) cout << setprecision(a) << fixed
#define vi vector<int>
#define sz(a) a.size()
#define amax(a, b) a = max(a, b)
#define amin(a, b) a = min(a, b)
#define vvi vector<vi>
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vb vector<bool>
#define vvb vector<vector<bool>>
#define mii map<int, int>
#define pii pair<int, int>
#define pll pair<long, long>
#define MP make_pair
#define all(a) a.begin(), a.end()
#define pb push_back
#define INF 1000000000
#define take(a) \
    int a;      \
    cin >> a;
#define MOD 1000000007
#define MAX_N 400001
#define set_bits __builtin_popcountll
#define ll long long
#define ull unsigned long long
#define ld long double

// works fine for n <= 500
// O(n^3)
const ll inf = 1LL << 62;
void floydWarshall(vector<vector<ll>> &m)
{
    int n = sz(m);
    rep(i, 0, n) m[i][i] = min(m[i][i], {});
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf)
    {
        auto newDist = max(m[i][k] + m[k][j], -inf);
        m[i][j] = min(m[i][j], newDist);
    }
    rep(k, 0, n) if (m[k][k] < 0) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}
//end

int32_t main()
{
    fastio();
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> link(n + 1, vector<ll>(n + 1, inf));
    rep(i, 0, n + 1) link[i][i] = 0;
    rep(i, 0, m)
    {
        int x, y;
        ll c;
        cin >> x >> y >> c;
        amin(link[x][y], c);
        amin(link[y][x], c);
    }
    floydWarshall(link);
    rep(i, 0, q)
    {
        int x, y;
        cin >> x >> y;
        if (link[x][y] == inf)
            cout << "-1\n";
        else
            cout << link[x][y] << "\n";
    }
    return 0;
}
