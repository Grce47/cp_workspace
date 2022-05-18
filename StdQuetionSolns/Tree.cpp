class Tree
{
public:
    int n;
    vector<vector<int>> link;
    Tree(int N)
    {
        n = N;
        link.resize(n + 1);
    }

    void addEdge(int x, int y)
    {
        link[x].push_back(y);
        link[y].push_back(x);
    }
    
};
