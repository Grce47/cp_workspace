
// use adj_list with 0 based indexing and root of tree is 0
struct LCA
{
    int N;
    static const int D = 18;
    vector<vector<int>> table;
    vector<vector<int>> tree;

    vector<int> depth;

    LCA(vector<vector<int>>  &tree)
    {
        N = tree.size();
        this->tree = tree;
        depth.assign(N, 0);
        table.assign(D, vector<int>(N, -1));
        dfs(0, -1);
        for (int i = 1; i < D; i++)
        {
            for (int u = 0; u < N; u++)
            {
                if (table[i - 1][u] >= 0)
                    table[i][u] = table[i - 1][table[i - 1][u]];
                else
                    table[i][u] = -1;
            }
        }
    }

    void dfs(int u, int p)
    {
        table[0][u] = p;
        for (int v : tree[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    int up(int u, int dist)
    {
        for (int i = D - 1; i >= 0; i--)
        {
            if ((dist & (1 << i)) > 0)
            {
                u = table[i][u];
                if (u == -1)
                    return -1;
            }
        }
        return u;
    }

    int lca(int u, int v)
    {
        if (depth[u] < depth[v])
        {
            return lca(v, u);
        }

        int diff = depth[u] - depth[v];
        u = up(u, diff);
        if (u == v)
            return u;

        for (int i = D - 1; i >= 0; i--)
        {
            if (table[i][u] != table[i][v])
            {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }

    int distance(int u, int v)
    {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }
};
