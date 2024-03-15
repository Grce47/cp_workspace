class CentroidDecomposition
{
private:
    int n;
    vector<bool> vis;
    vector<int> sz;
    const vector<vector<int>> &tree;

    int find_size(int v, int p = -1)
    {
        if (vis[v])
            return 0;
        sz[v] = 1;
        for (const int &x : tree[v])
            if (x != p)
                sz[v] += find_size(x, v);
        return sz[v];
    }

    int find_centroid(int v, int p, int cur_sz)
    {
        for (const int &x : tree[v])
            if (x != p)
                if (!vis[x] && sz[x] > (cur_sz / 2))
                    return find_centroid(x, v, cur_sz);
        return v;
    }

    void init_centroid(int v, int p)
    {
        find_size(v);
        int c = find_centroid(v, -1, sz[v]);
        vis[c] = true;
        centroid_par[c] = p;
        if (p == -1)
            root = c;
        else
            centorid_tree[p].push_back(c);
        for (const int &x : tree[c])
            if (!vis[x])
                init_centroid(x, c);
    }

public:
    vector<vector<int>> centorid_tree;
    vector<int> centroid_par;
    int root;
    CentroidDecomposition(vector<vector<int>> &_tree) : tree(_tree)
    {
        root = 0;
        n = tree.size();
        centorid_tree.resize(n);
        vis.resize(n, false);
        sz.resize(n, 0);
        centroid_par.resize(n, -1);
        init_centroid(0, -1);
    }
};