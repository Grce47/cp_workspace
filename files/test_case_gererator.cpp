#include <bits/stdc++.h>
using namespace std;

#define int long long

int rand_big()
{
    return (long long)rand() * (long long)rand() * (long long)rand() * (long long)rand();
}

int randNum(int a, int b)
{
    int val = a + rand_big() % (b - a + 1);
    return val;
}

char genChar()
{
    char ch = 'a';
    int ascii = randNum(0, 25);
    return char(ch + ascii);
}
void testcase()
{
    int n = 10;
    cout << n << "\n";
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    random_shuffle(a.begin(), a.end());
    for (auto &e : a)
        cout << e << " ";
        
}

int32_t main()
{
    srand(time(0));
    freopen("input.txt", "w", stdout);
    int tc = 1;
    // cin >> tc;
    // cout << tc << "\n";
    for (int loop = 1; loop <= tc; loop++)
    {
        testcase();
    }
    return 0;
}
