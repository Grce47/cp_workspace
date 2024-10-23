// n -> # of left nodes
// m -> # of right nodes
// e -> edges where e[i].first -> [0,n-1] and e[i].second -> [0,m-1]
// return max matching edges in O(E sqrt(V)) time
vector<pair<int, int>> hopcroft_karp(int n, int m, vector<pair<int, int>> &e, bool to_shuffle = true)
{
    vector<int> g(e.size()), l(n, -1), r(m, -1);

    if (to_shuffle)
    {
        random_device rd;
        mt19937 mt(rd());

        shuffle(e.begin(), e.end(), mt);
    }

    vector<int> deg(n + 1);

    for (const auto &[x, y] : e)
        deg[x]++;
    for (int i = 1; i <= n; i++)
        deg[i] += deg[i - 1];
    for (const auto &[x, y] : e)
        g[--deg[x]] = y;

    vector<int> a, p, q(n);
    while (true)
    {
        a.assign(n, -1), p.assign(n, -1);

        int t = 0;
        for (int i = 0; i < n; i++)
        {
            if (l[i] == -1)
                q[t++] = a[i] = p[i] = i;
        }

        bool match = false;
        for (int i = 0; i < t; i++)
        {
            int x = q[i];
            if (~l[a[x]])
                continue;

            for (int j = deg[x]; j < deg[x + 1]; j++)
            {
                int y = g[j];
                if (r[y] == -1)
                {
                    while (~y)
                    {
                        r[y] = x;
                        swap(l[x], y);
                        x = p[x];
                    }

                    match = true;
                    break;
                }

                if (p[r[y]] == -1)
                {
                    q[t++] = y = r[y];
                    p[y] = x;
                    a[y] = a[x];
                }
            }
        }

        if (!match)
            break;
    }

    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++)
        if (~l[i])
            ans.emplace_back(i, l[i]);
    return ans;
}

// Note: assert fail; if input graph is not bipartite
// input: undirected 0-based indexing graph
// returns  left_nodes, right_nodes, edge_list (relate [0,size(left)-1] -> [0,size(right)-1] )
tuple<vector<int>, vector<int>, vector<pair<int, int>>> get_bipartite_details(const vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> color(n, -1);

    auto dfs = [&color, &graph](auto &&self, int cur, int c) -> void
    {
        color[cur] = c;
        for (auto &child : graph[cur])
        {
            if (color[child] == -1)
                self(self, child, c ^ 1);

            // make sure graph is bipartite
            assert(color[child] != color[cur]);
        }
    };

    for (int i = 0; i < n; i++)
        if (color[i] == -1)
            dfs(dfs, i, 0);

    vector<int> left, right;
    for (int i = 0; i < n; i++)
    {
        if (color[i] == 0)
            left.push_back(i);
        else
            right.push_back(i);
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < (int)left.size(); i++)
    {
        for (auto &child : graph[left[i]])
        {
            int ridx = int(lower_bound(right.begin(), right.end(), child) - right.begin());
            edges.emplace_back(i, ridx);
        }
    }

    return make_tuple(left, right, edges);
}