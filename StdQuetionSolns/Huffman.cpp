class Huffman
{
private:
    vector<int> encodingLength;
    vector<array<int, 2>> tree;

public:
    Huffman(const vector<int> &frequencies) : encodingLength(frequencies.size(), -1), tree(frequencies.size(), {-1, -1})
    {
        set<pair<int, int>> pq;

        int nxt = frequencies.size();
        for (int i = 0; i < nxt; i++)
            pq.insert(make_pair(frequencies[i], i));

        while (!pq.empty())
        {
            int f0 = pq.begin()->first, v0 = pq.begin()->second;
            pq.erase(pq.begin());

            if (pq.empty())
            {
                encodingLength[v0] = 0;
                break;
            }
            int f1 = pq.begin()->first, v1 = pq.begin()->second;
            pq.erase(pq.begin());

            tree[v0] = {nxt, 0};
            tree[v1] = {nxt, 1};

            pq.insert(make_pair(f0 + f1, nxt));

            encodingLength.push_back(-1);
            tree.push_back({-1, -1});
            nxt++;
        }
    }

    int getEncodingLength(int index)
    {
        return encodingLength[index] != -1 ? encodingLength[index] : (encodingLength[index] = 1 + getEncodingLength(tree[index][0]));
    }

    vector<bool> getEncoding(int index)
    {
        vector<bool> v;
        int cur = index;
        while (1)
        {
            if (tree[cur][0] != -1)
                v.push_back(tree[cur][1]);
            else
                break;
            cur = tree[cur][0];
        }
        reverse(v.begin(), v.end());
        return v;
    }
};