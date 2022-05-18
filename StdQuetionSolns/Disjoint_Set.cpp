class DisSet
{
private:
    struct Node
    {
        int rank;
        int parent;
        int number;
    };
    Node *nodes;

public:
    DisSet(int N)
    {
        nodes = (Node *)malloc(sizeof(Node) * (N + 1));
        for (int i = 0; i <= N; i++)
        {
            nodes[i].rank = 0;
            nodes[i].number = 1;
            nodes[i].parent = i;
        }
    }
    int getParent(int cur)
    {
        if (nodes[cur].parent == cur)
            return cur;
        nodes[cur].parent = getParent(nodes[cur].parent);
        return nodes[cur].parent;
    }

    int getNumber(int cur)
    {
        return nodes[getParent(cur)].number;
    }

    void mergeSet(int n1, int n2)
    {
        n1 = getParent(n1);
        n2 = getParent(n2);
        if (n1 == n2)
            return;
        if (nodes[n1].rank < nodes[n2].rank)
        {
            nodes[n1].parent = n2;
            nodes[n2].number += nodes[n1].number;
        }
        else if (nodes[n1].rank > nodes[n2].rank)
        {
            nodes[n2].parent = n1;
            nodes[n1].number += nodes[n2].number;
        }
        else
        {
            nodes[n1].parent = n2;
            nodes[n2].number += nodes[n1].number;
            nodes[n2].rank++;
        }
    }
    bool isDiff(int n1, int n2)
    {
        return (getParent(n1) != getParent(n2));
    }
};
