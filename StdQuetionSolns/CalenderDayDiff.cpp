#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(0);
#define endl "\n"
#define int long long
#define INF 1e9
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sq(a) (a) * (a)
#define root(a) pow(a, 0.5)
#define vi vector<int>
#define pb push_back

int daydiff(int df, int mf, int yf, int di, int mi, int yi)
{
    int ans = 0;
    int m[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int l[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (yi == yf)
    {
        if (mi == mf)
            ans = df - di;
        else
        {
            if (yi % 4 == 0)
                ans += l[mi] - di + 1 + df;
            else
                ans += m[mi] - di + 1 + df;
            if (mf - mi > 1)
            {
                for (int month = mi + 1; month < mf; month++)
                {
                    if (yi % 4 == 0)
                        ans += l[month];
                    else
                        ans += m[month];
                }
            }
        }
        return ans;
    }
    if (yi % 4 == 0)
    {
        ans += l[mi] - di + 1;
        mi++;
        rep(i, mi, 13)
        {
            ans += l[i];
        }
    }
    else
    {
        ans += m[mi] - di + 1;
        mi++;
        rep(i, mi, 13)
        {
            ans += m[i];
        }
    }
    if (yf % 4 == 0)
    {
        ans += df;
        rep(i, 1, mf)
        {
            ans += l[i];
        }
    }
    else
    {
        ans += df;
        rep(i, 1, mf)
        {
            ans += m[i];
        }
    }
    if (yf - yi > 1)
    {
        for (int year = yi + 1; year < yf; year++)
        {
            if (year % 4 != 0)
                ans += 365;
            else
                ans += 366;
        }
    }
    return ans - 1;
}

int32_t main()
{
    int d1, d2, m1, m2, y1, y2, ans = 0;
    cin >> d2 >> m2 >> y2 >> d1 >> m1 >> y1;
    int day = daydiff(d2, m2, y2, d1, m1, y1);
    cout << day;
    return 0;
}
