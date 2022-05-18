#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// O(nlogn)
// return random[L,...,R];
vector<int> randomPermutation(int n)
{
    static bool ok = false;
    if (!ok)
    {
        srand(time(0));
        ok = true;
    }
    else
        srand(rand());
        
    int l = 0, r = n - 1;

    ordered_set<int> st;
    for (int i = l; i <= r; i++)
        st.insert(i);

    vector<int> res(n);
    for (int i = 0; i < n; i++)
    {
        int idx = rand() % st.size();
        auto ele = st.find_by_order(idx);
        res[i] = *ele;
        st.erase(ele);
    }
    return res;
}
