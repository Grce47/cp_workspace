class HLD
{
private:
    vector<int> label, inv_label, sub_tree_size, heavy_edge;
    int n;

    void dfs1(const vector<vector<int>> &_tree, int cur, int par)
    {
        for (auto &ele : _tree[cur])
        {
            if (ele == par)
                continue;
            dfs1(_tree, ele, cur);
            sub_tree_size[cur] += sub_tree_size[ele];
        }
    }

    void dfs2(const vector<vector<int>> &_tree, int cur, int par, int &lab)
    {
        label[cur] = lab;
        inv_label[lab] = cur;

        lab++;

        // leaf node
        if (_tree[cur].size() == 1 && cur != 0)
            return;

        int mxval = -1, heavy_node = -1;

        for (auto &ele : _tree[cur])
        {
            if (ele == par)
                continue;
            if (mxval < sub_tree_size[ele])
            {
                mxval = sub_tree_size[ele];
                heavy_node = ele;
            }
        }

        dfs2(_tree, heavy_node, cur, lab);
        tree[label[cur]].push_back(label[heavy_node]);
        heavy_edge[label[cur]] = label[heavy_node];

        for (auto &ele : _tree[cur])
        {
            if (ele == heavy_node || ele == par)
                continue;
            dfs2(_tree, ele, cur, lab);
            tree[label[cur]].push_back(label[ele]);
        }
    }

    void dfs3(int cur, int par)
    {
        parent[cur] = par;
        for (auto &ele : tree[cur])
        {
            if (ele == par)
                continue;
            if (ele == heavy_edge[cur])
                chain_top[ele] = chain_top[cur];
            dfs3(ele, cur);
            if (ele == heavy_edge[cur])
                chain_length[cur] = 1 + chain_length[ele];
        }
    }

public:
    vector<vector<int>> tree;
    vector<int> chain_top, chain_length, parent;

    HLD(vector<vector<int>> &_tree)
    {
        n = _tree.size();
        tree.resize(n);
        parent.resize(n);
        chain_length.resize(n, 1);
        label.resize(n);
        inv_label.resize(n);
        sub_tree_size.resize(n, 1);
        heavy_edge.resize(n, -1);

        chain_top.resize(n);
        iota(chain_top.begin(), chain_top.end(), 0);

        dfs1(_tree, 0, -1);
        int cnt = 0;
        dfs2(_tree, 0, -1, cnt);
        dfs3(0, -1);
    }

    /// @brief Gives node number in new labeled tree
    inline int get_label(const int &original_node)
    {
        return label[original_node];
    }

    /// @brief Gives node number of original tree from labeled value
    inline int get_original(const int &labeled_node)
    {
        return inv_label[labeled_node];
    }
};
