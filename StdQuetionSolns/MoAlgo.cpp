void add(int index)
{
    // add index, should be O(1)
}

void rem(int index)
{
    // remove index, should be O(1)
}

struct MoQuery
{
    static const int block_size = 448; // sqrt(n)
    int l, r, idx;
    bool operator<(const MoQuery &o) const
    {
        int t1 = l / block_size, t2 = o.l / block_size;
        if (t1 != t2) return t1 < t2;
        return (t1 & 1 ? r > o.r : r < o.r);
    }
};

vector<int> moSolver(const vector<pair<int, int>> &rangeQueries)
{
    int num_queries = rangeQueries.size();

    vector<MoQuery> queries(num_queries);
    vector<int> ans(num_queries);

    for (int i = 0; i < num_queries; i++)
    {
        queries[i].l = rangeQueries[i].first;
        queries[i].r = rangeQueries[i].second;
        queries[i].idx = i;
    }
    sort(queries.begin(), queries.end());

    int ptrL = queries[0].l, ptrR = queries[0].r;
    for (int i = ptrL; i <= ptrR; i++)
        add(i);

    for (auto &[l, r, idx] : queries)
    {
        while (ptrR < r)
            add(++ptrR);
        while (ptrL > l)
            add(--ptrL);
        while (ptrL < l)
            rem(ptrL++);
        while (ptrR > r)
            rem(ptrR--);

        // fill ans[idx]
    }
    return ans;
}