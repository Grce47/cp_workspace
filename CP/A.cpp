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
const int MAX_N = 1000001;

/*
    ORDERED SET
    st.find_by_order(index) -> pointer to element of given index
    st.order_of_key(element) -> number of elements strictly less than that element
 */

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// END

ordered_set<int> st;


// set MAX_N and call fact_init();
vector<int64_t> Factorial(MAX_N + 1, 0);
void fact_init()
{
    Factorial[0] = Factorial[1] = 1;
    for (int i = 2; i <= MAX_N; i++)
        Factorial[i] = (Factorial[i - 1] * i) % MOD;
}

// returns (a^n) % MOD
int64_t power(int64_t a, int64_t n)
{
    int64_t res = 1;
    while (n)
    {
        if (n & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        n = n >> 1;
    }
    return res;
}

//returns (nCr) % MOD
int64_t nCr(int n, int r)
{
    if (r > n || r < 0)
        return 0;
    if (n == r || r == 0)
        return 1;
    return ((Factorial[n] * power(Factorial[r], MOD - 2)) % MOD * power(Factorial[n - r], MOD - 2)) % MOD;
}

//START seg_tree
class Stree
{
private:
    Stree* L = NULL;
    Stree* R = NULL;
    int ss, se;
    int mid;
    bool isOut(int qs, int qe)
    {
        return (ss > qe || se < qs);
    }
    bool isIn(int qs, int qe)
    {
        return (ss >= qs && se <= qe);
    }
    void clear()
    {
        if (ss == se) return;

        L->clear();
        R->clear();

        delete L;
        delete R;

        ss = se = mid = 0;
    }
    int val;
public:

    Stree(int SS, int SE)
    {
        ss = SS;
        se = SE;
        mid = (ss + se) >> 1;
    }
    ~Stree() { clear(); }

    void buildTree()
    {
        if (ss == se)
        {
            val = 0;
            return;
        }
        if (!L) L = new Stree(ss, mid);
        if (!R) R = new Stree(mid + 1, se);
        L->buildTree();
        R->buildTree();

        val = L->val + R->val;
    }

    int getVal(int q)
    {
        if (ss == se) return val;
        if (mid >= q) return L->getVal(q);
        return R->getVal(q);
    }
    int getRangeVal(int qs, int qe)
    {
        if (isOut(qs, qe)) return 0;
        if (isIn(qs, qe)) return val;
        return L->getRangeVal(qs, qe) + R->getRangeVal(qs, qe);
    }
    void update(int q)
    {
        if (ss == se)
        {
            val++;
            return;
        }
        if (mid >= q) L->update(q);
        else R->update(q);

        val = L->val + R->val;
    }
};
//END seg_tree

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

    fact_init();
    int n, k;
    cin >> n >> k;

    vector<pii> a(n);
    rep(i, 0, n)
    {
        cin >> a[i].first >> a[i].second;
        st.insert(a[i].first);
        st.insert(a[i].second);
    }

    rep(i, 0, n)
    {
        a[i].first = st.order_of_key(a[i].first);
        a[i].second = st.order_of_key(a[i].second);
    }

    sort(all(a));
    ll ans = 0;
    int N = st.size();
    Stree seg_tree(0, N);
    seg_tree.buildTree();

    int p = 0;

    rep(i, 0, N)
    {
        int starts = 0;
        while (p < n)
        {
            if (a[p].first > i) break;
            seg_tree.update(a[p].second);
            starts++;
            p++;
        }

        int ends = seg_tree.getRangeVal(i, N) - starts;
        rep(j, 1, starts + 1)
        {
            ans = (ans + (nCr(starts, j) * nCr(ends, k - j)) % MOD) % MOD;
        }

    }

    cout << ans << "\n";
    return 0;
}

