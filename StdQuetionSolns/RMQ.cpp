template <class T>
struct RMQ
{
    vector<vector<T>> jmp;
    T property(T &n1, T &n2)
    {
        return max(n1, n2);
    }
    RMQ(const vector<T> &V)
    {
        int N = V.size(), on = 1, depth = 1;
        while (on < V.size())
            on *= 2, depth++;
        jmp.assign(depth, V);
        for (int i = 0; i < depth - 1; i++)
            for (int j = 0; j < N; j++)
                jmp[i + 1][j] = property(jmp[i][j],
                                         jmp[i][min(N - 1, j + (1 << i))]);
    }

    // if first_index==true; get first index in range [a,b] which has max priority
    // else; get last index
    int query_index(int a, int b, bool first_index = true)
    {
        int low = a, high = b, mid, ans = a;
        T q = this->query(a, b);
        while (low <= high)
        {
            mid = (low + high) >> 1;
            T cur = (first_index ? this->query(a, mid) : this->query(mid, b));
            if (cur == q)
            {
                ans = mid;
                if (first_index)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            else
            {
                if (first_index)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return ans;
    }

    // property(arr[a] ... arr[b])
    T query(int a, int b)
    {
        b++;
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return property(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};