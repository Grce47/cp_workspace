template <class T>
struct RMQ
{
    vector<vector<T>> jmp;
    T property(T& n1, T& n2)
    {
        return max(n1, n2);
    }
    RMQ(const vector<T>& V)
    {
        int N = V.size(), on = 1, depth = 1;
        while (on < V.size())
            on *= 2, depth++;
        jmp.assign(depth, V);
        for (int i = 0; i < depth - 1; i++) for (int j = 0; j < N; j++)
            jmp[i + 1][j] = property(jmp[i][j],
                jmp[i][min(N - 1, j + (1 << i))]);
    }

    T query(int a, int b) // property(arr[a] ... arr[b])
    {
        b++;
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return property(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
