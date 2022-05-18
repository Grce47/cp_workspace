/*
    Fri Nov 05 19:58:45 2021
    File : A.cpp
    CodeForce : Gr47
    CodeChef : gr47ace
    HackerRank : gracesharma47
*/
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

struct Min_Dist_Square
{
    ll min_dist = 0;
    int n;
    struct Point
    {
        ll x;
        ll y;
    };
    Point *X;
    ll square(ll a)
    {
        return a * a;
    }
    Min_Dist(vector<pll> const &a)
    {
        n = a.size();
        X = (Point *)malloc(sizeof(Point) * n);
        Point *Y = (Point *)malloc(sizeof(Point) * n);
        for (int i = 0; i < n; i++)
        {
            X[i].x = a[i].first;
            X[i].y = a[i].second;
            Y[i].x = a[i].first;
            Y[i].y = a[i].second;
        }
        auto cmp_x = [&](Point const &p1, Point const &p2) -> bool
        {
            if (p1.x == p2.x)
                return (p1.y < p2.y);
            return (p1.x < p2.x);
        };
        auto cmp_y = [&](Point const &p1, Point const &p2) -> bool
        {
            if (p1.y == p2.y)
                return (p1.x < p2.x);
            return (p1.y < p2.y);
        };
        sort(X, X + n, cmp_x);
        sort(Y, Y + n, cmp_y);
        min_dist = find_min_dist(0, n - 1, Y);
        free(Y);
        free(X);
    }

    ll dist(Point const &p1, Point const &p2)
    {
        return (square(p1.x - p2.x) + square(p1.y - p2.y));
    }

    ll brute(int low, int high)
    {
        ll mn = LLONG_MAX;
        for (int i = low; i < high; i++)
        {
            for (int j = i + 1; j <= high; j++)
            {
                ll tmp_dist = dist(X[i], X[j]);
                mn = min(mn, tmp_dist);
            }
        }
        return mn;
    }
    ll find_min_dist(int low, int high, Point *Y)
    {
        if (high - low <= 2)
            return brute(low, high);

        int mid = (low + high) >> 1;
        Point midPoint = X[mid];
        Point *yleft = (Point *)malloc(sizeof(Point) * (mid - low + 1));
        Point *yright = (Point *)malloc(sizeof(Point) * (high - mid));

        int pointer1 = 0, pointer2 = 0;

        int mid_cnt = 0;
        for (int i = low; i <= mid; i++)
        {
            if (X[i].x == midPoint.x && X[i].y == midPoint.y)
                mid_cnt++;
        }

        for (int i = 0; i < (high - low + 1); i++)
        {
            if (Y[i].x == midPoint.x && Y[i].y == midPoint.y)
            {
                if (mid_cnt)
                {
                    yleft[pointer1++] = Y[i];
                    mid_cnt--;
                }
                else
                    yright[pointer2++] = Y[i];
            }
            else if ((Y[i].x == midPoint.x && Y[i].y < midPoint.y) || Y[i].x < midPoint.x)
                yleft[pointer1++] = Y[i];
            else
                yright[pointer2++] = Y[i];
        }

        ll dl = find_min_dist(low, mid, yleft);
        ll dr = find_min_dist(mid + 1, high, yright);
        ll d = min(dl, dr);

        for (int i = 0; i < (high - low + 1); i++)
        {
            if (square(Y[i].x - midPoint.x) >= d)
                continue;
            for (int j = i + 1; j < (high - low + 1) && square(Y[j].y - Y[i].y) < d; ++j)
                if (dist(Y[i], Y[j]) < d)
                    d = dist(Y[i], Y[j]);
        }

        free(yleft);
        free(yright);
        return d;
    }
};

int32_t main()
{
    fastio();
    int n;
    cin >> n;
    vector<pll> a(n);
    rep(i, 0, n) cin >> a[i].first >> a[i].second;
    Min_Dist_Square ans(a);
    cout << ans.min_dist;
    return 0;
}
