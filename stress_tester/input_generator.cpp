#include <bits/stdc++.h>
using namespace std;

int genNum(int dig, bool minusAllowed = false)
{
    int ans = 0, ten = 1;
    for (int i = 0; i < dig; i++)
    {
        ans += (rand() % 10) * ten;
        ten *= 10;
    }

    if (minusAllowed)
        if (rand() % 2)
            ans *= -1;

    return ans;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <seed> <n's number digit> <ele's digit>" << std::endl;
        return 1;
    }

    int seed = std::atoi(argv[1]);
    srand(seed);

    int n = genNum(std::atoi(argv[2])) + 4;
    int dig = std::atoi(argv[3]);
    cout << n << endl;
    for (int i = 0; i < n; i++)
        cout << genNum(dig, true) << " ";
    cout << endl;
}