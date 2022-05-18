// NOTE: works better for 0-based graph
class SCC
{
private:
    int n;
    vector<vector<int>> rev_link, link;
    vector<int> order;
    vector<bool> visited;
    void dfs1(int cur)
    {
        visited[cur] = true;
        for (int &child : link[cur])
        {
            if (visited[child])
                continue;
            dfs1(child);
        }
        order.push_back(cur);
    }

    void dfs2(int cur, int idx)
    {
        visited[cur] = true;
        scc[idx].insert(cur);
        scc_index[cur] = idx;
        for (int &child : rev_link[cur])
        {
            if (visited[child])
                continue;
            dfs2(child, idx);
        }
    }

    void buildScc()
    {
        fill(visited.begin(), visited.end(), false);
        int idx = 0;
        while (!order.empty())
        {
            int v = order.back();
            order.pop_back();
            if (visited[v])
                continue;
            dfs2(v, idx);
            idx++;
        }

        while (scc.back().empty())
            scc.pop_back();
    }

public:
    vector<set<int>> scc;      // sets of scc
    vector<int> scc_index;     // which node belong to which indexed scc
    vector<set<int>> scc_edge; // directed edges btw sccs
    vector<int> in_order;      // number of incoming edge for a scc
    vector<int> out_order;     // number of outgoing edge for a scc
    int scc_no;

    void clear()
    {
        n = 0;
        scc_no = 0;
        scc.clear();
        scc_index.clear();
        scc_edge.clear();
        in_order.clear();
        out_order.clear();
    }
    void build(vector<vector<int>> &ori_link)
    {
        n = ori_link.size();
        link.resize(n);
        rev_link.resize(n);
        scc.resize(n);
        scc_index.resize(n);

        for (int i = 0; i < n; i++)
        {
            for (int &ele : ori_link[i])
            {
                rev_link[ele].push_back(i);
                link[i].push_back(ele);
            }
        }

        visited.resize(n, false);
        for (int i = 0; i < n; i++)
        {
            if (visited[i])
                continue;
            dfs1(i);
        }

        buildScc();

        link.clear();
        rev_link.clear();
        visited.clear();
        order.clear();

        scc_no = (int)scc.size();
        scc_edge.resize(scc_no);
        in_order.resize(scc_no, 0);
        out_order.resize(scc_no, 0);

        int node1, node2;
        for (int i = 0; i < n; i++)
        {
            node1 = scc_index[i];
            for (int &ele : ori_link[i])
            {
                node2 = scc_index[ele];
                if (node1 == node2)
                    continue;
                if (scc_edge[node1].find(node2) != scc_edge[node1].end())
                    continue;

                scc_edge[node1].insert(node2);
                in_order[node2]++;
                out_order[node1]++;
            }
        }
    }
    void display()
    {
        for (int i = 0; i < scc_no; i++)
        {
            cout << i << " -> { ";
            for (const int &ele : scc[i])
                cout << ele << " ";
            cout << " }\n";
        }
        for (int i = 0; i < scc_no; i++)
        {
            cout << "EDGE " << i << " -> ";
            for (const int &ele : scc_edge[i])
                cout << ele << " ";
            cout << "\n";
        }
    }
    SCC()
    {
        n = 0;
        scc_no = 0;
    }
    SCC(vector<vector<int>> &ori_link)
    {
        build(ori_link);
    }
};