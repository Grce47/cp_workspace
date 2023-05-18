#include <bits/stdc++.h>
using namespace std;

#define fastio()                      \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define mii map<int, int>
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
#define pb push_back
#define INF 100000000
#define take(a) \
    int a;      \
    cin >> a;
#define MOD 1000000007
#define MAX_N 50000
#define set_bits __builtin_popcountll
#define ll long long
#define ull unsigned long long
#define ld long double
// #define int long long

template <class T>
void _print(vector<T> &a)
{
    for (T ele : a)
        cout << ele << " ";
    cout << "\n";
}

template <class T>
void _print(T &a)
{
    cout << a << ' ';
}

int genNum(int a, int b)
{
    int val = a + rand() % (b - a + 1);
    return val;
}

char genChar()
{
    char ch = 'a';
    int ascii = genNum(0, 25);
    return char(ch + ascii);
}
int cnt = 1;
class testcase
{
public:
    int n, k;
    vi arr;
    string s;
    void randomize()
    {
        n = 1e5;
    }
    void display()
    {
        cout << n << " " << n << "\n";
        rep(i, 0, n) cout << n << " ";
        cout << '\n';
        rep(i,0,n) cout<<i+n<<" ";
        cout << "\n";
    }
};

int randNum(int a, int b)
{
    int val = a + rand() % (b - a + 1);
    return val;
}

int32_t main()
{
    srand(time(0));
    fastio();
    freopen("input.txt", "w", stdout);
    int tc = 1;
    // cin >> tc;
    // cout << tc << "\n";
    for (int loop = 1; loop <= tc; loop++)
    {
        // cout << loop << "\n";
        testcase t;
        t.randomize();
        t.display();
    }
    return 0;
}
