// Dinic's Algo : O(EV^2)
class Graph
{
private:
    struct Edge
    {
        int v, flow;
        long long C;
        int rev;
        Edge(int _v, int _flow, long long _C, int _rev) : v(_v), flow(_flow), C(_C), rev(_rev) {}
    };
    int V;
    vector<int> level;
    vector<vector<Edge>> adj;
    bool BFS(int s, int t)
    {
        for (int i = 0; i < V; i++)
            level[i] = -1;

        level[s] = 0;
        list<int> q;
        q.push_back(s);

        vector<Edge>::iterator i;
        while (!q.empty())
        {
            int u = q.front();
            q.pop_front();
            for (i = adj[u].begin(); i != adj[u].end(); i++)
            {
                Edge &e = *i;
                if (level[e.v] < 0 && e.flow < e.C)
                {
                    level[e.v] = level[u] + 1;
                    q.push_back(e.v);
                }
            }
        }
        return level[t] < 0 ? false : true;
    }
    long long sendFlow(int u, long long flow, int t, int *start)
    {
        if (u == t)
            return flow;

        for (; start[u] < adj[u].size(); start[u]++)
        {
            Edge &e = adj[u][start[u]];

            if (level[e.v] == level[u] + 1 && e.flow < e.C)
            {
                long long curr_flow = min(flow, e.C - e.flow);
                long long temp_flow = sendFlow(e.v, curr_flow, t, start);
                if (temp_flow > 0)
                {
                    e.flow += temp_flow;
                    adj[e.v][e.rev].flow -= temp_flow;
                    return temp_flow;
                }
            }
        }
        return 0;
    }

public:
    Graph(int _V) : V(_V)
    {
        adj.resize(V);
        level.resize(V);
    }

    void addEdge(int u, int v, long long C)
    {
        adj[u].emplace_back(v, 0, C, adj[v].size());
        adj[v].emplace_back(u, 0, 0, adj[u].size());
    }

    long long DinicMaxflow(int s, int t)
    {
        if (s == t)
            return -1;

        long long total = 0;

        while (BFS(s, t) == true)
        {
            int *start = new int[V + 1]{0};
            while (long long flow = sendFlow(s, LLONG_MAX, t, start))
                total += flow;

            delete[] start;
        }

        return total;
    }
};
