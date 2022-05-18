#include <bits/stdc++.h>
using namespace std;

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


int main()
{
    ordered_set<int> st;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        st.insert(val);
    }

    int k;
    cin >> k;

    cout << (st.size() - st.order_of_key(k));

    return 0;
}
