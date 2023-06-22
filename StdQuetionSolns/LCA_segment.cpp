struct segment
{
    int sm;
    bool def = true;
};

void init(segment &res, int u)
{
    res.def = false;

    // TODO: initialize for one length segment
    res.sm = 1;
}

segment combine(const segment &up, const segment &down)
{
    if (up.def)
        return up;
    if (down.def)
        return down;

    segment res;
    res.def = false;

    // TODO : Comine up and down segment
    res.sm = up.sm + down.sm;

    return res;
}

struct LCA
{
    int N;
    static const int D = 20;
    vector<vector<int>> table;
    vector<vector<segment>> seg;
    vector<int> depth;

    LCA(vector<vector<int>> &tree)
    {
        N = tree.size();
        depth.assign(N, 0);
        table.assign(D, vector<int>(N, -1));
        seg.assign(D, vector<segment>(N));
        dfs(0, -1, tree);
        for (int i = 1; i < D; i++)
        {
            for (int u = 0; u < N; u++)
            {
                if (table[i - 1][u] >= 0)
                {
                    table[i][u] = table[i - 1][table[i - 1][u]];
                    seg[i][u] = combine(seg[i - 1][table[i - 1][u]], seg[i - 1][u]);
                }
                else
                    table[i][u] = -1;
            }
        }
    }

    void dfs(int u, int p, vector<vector<int>> &tree)
    {
        table[0][u] = p;

        init(seg[0][u], u);

        for (int v : tree[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, tree);
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

    // get combined segment for [u(0),u(1),u(2),....u(up_walk)] where u(i+1) is parent of u(i) and u(0) = u
    segment combined_segment(int u, int up_walk)
    {
        assert(u >= 0 && u < N);
        assert(up_walk >= 0);
        assert(depth[u] >= up_walk);
        
        up_walk++;
        segment res;
        for (int i = D - 1; i >= 0; i--)
        {
            if ((up_walk & (1 << i)) > 0)
            {
                if (res.def)
                    res = seg[i][u];
                else
                    res = combine(seg[i][u], res);
                u = table[i][u];
            }
        }
        return res;
    }
};