class ArticulationGraph
{
private:
    int timer, V;
    vector<bool> vis, is_bridge;
    vector<int> in_time, low;

    void egdeDFS(int cur, int par, const vector<vector<int>> &graph, vector<pair<int, int>> &ret)
    {
        vis[cur] = 1;
        in_time[cur] = low[cur] = timer++;
        for (const int &child : graph[cur])
        {
            if (child == par)
                continue;

            if (vis[child])
            {
                low[cur] = min(low[cur], in_time[child]);
            }
            else
            {
                egdeDFS(child, cur, graph, ret);

                low[cur] = min(low[cur], low[child]);

                if (low[child] > in_time[cur])
                    ret.emplace_back(cur, child);
            }
        }
    }

    void pointDFS(int cur, int par, const vector<vector<int>> &graph)
    {
        int children = 0;
        vis[cur] = 1;
        in_time[cur] = low[cur] = timer++;

        for (const int &child : graph[cur])
        {
            if (child == par)
                continue;

            if (vis[child])
            {
                low[cur] = min(low[cur], in_time[child]);
            }
            else
            {
                children++;
                pointDFS(child, cur, graph);

                low[cur] = min(low[cur], low[child]);

                if (par != -1 && low[child] >= in_time[cur])
                    is_bridge[cur] = 1;
            }
        }

        if (par == -1 && children > 1)
            is_bridge[cur] = 1;
    }

public:
    vector<int> bridgePoints(const vector<vector<int>> &graph)
    {
        vector<int> ret;

        V = graph.size();
        timer = 0;

        vis.resize(V, false);
        is_bridge.resize(V, false);
        low.resize(V, 0);
        in_time.resize(V, 0);

        for (int u = 0; u < V; u++)
            if (!vis[u])
                pointDFS(u, -1, graph);

        for (int u = 0; u < V; u++)
            if (is_bridge[u])
                ret.emplace_back(u);
        return ret;
    }

    vector<pair<int, int>> bridgeEdges(const vector<vector<int>> &graph)
    {
        vector<pair<int, int>> ret;

        V = graph.size();
        timer = 0;

        vis.resize(V, false);
        in_time.resize(V, 0);
        low.resize(V, 0);

        for (int i = 0; i < V; i++)
        {
            if (vis[i])
                continue;
            egdeDFS(i, -1, graph, ret);
        }

        return ret;
    }
};