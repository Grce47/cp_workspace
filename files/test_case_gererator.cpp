#include <bits/stdc++.h>
using namespace std;

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

int randNum(int a, int b)
{
    int val = a + rand() % (b - a + 1);
    return val;
}

void testcase()
{
    int n = randNum(100, 1000);
    cout << n << endl;
}

int32_t main()
{
    srand(time(0));
    freopen("input.txt", "w", stdout);
    int tc = 1;
    // cin >> tc;
    cout << tc << "\n";
    for (int loop = 1; loop <= tc; loop++)
    {
        testcase();
    }
    return 0;
}
