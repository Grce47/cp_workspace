class SuffixArray
{
private:
    using node = array<int, 3>;
    static void radix_sort(vector<node> &a)
    {
        int n = a.size();
        for (int id = 1; id >= 0; id--)
        {
            vector<int> cnt(n);
            for (auto &x : a)
                cnt[x[id]]++;

            vector<node> tmp_a(n);
            vector<int> pos(n, 0);

            for (int i = 1; i < n; i++)
                pos[i] = pos[i - 1] + cnt[i - 1];

            for (auto &x : a)
            {
                int i = x[id];
                tmp_a[pos[i]] = x;
                pos[i]++;
            }
            a = tmp_a;
        }
    }

public:
    static vector<int> getSuffixArray(const string &_s)
    {
        string s = _s;
        s.push_back(static_cast<char>(0));

        int n = s.size();
        vector<int> sa(n), cost(n);

        int k = -1;
        do
        {
            vector<node> a(n);

            if (k == -1)
            {
                for (int i = 0; i < n; i++)
                    a[i] = node{static_cast<int>(s[i]), 0, i};
                sort(a.begin(), a.end());
            }
            else
            {
                for (int i = 0; i < n; i++)
                    a[i] = node{cost[i], cost[(i + (1 << k)) % n], i};
                radix_sort(a);
            }

            for (int i = 0; i < n; i++)
                sa[i] = a[i][2];

            cost[sa[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                if (a[i][0] == a[i - 1][0] && a[i][1] == a[i - 1][1])
                    cost[sa[i]] = cost[sa[i - 1]];
                else
                    cost[sa[i]] = cost[sa[i - 1]] + 1;
            }

            k++;
        } while ((1 << k) < n);

        sa.erase(sa.begin());
        return sa;
    }
    static vector<int> getRank(const vector<int> &suffix_array)
    {
        int n = suffix_array.size();
        vector<int> rank(n);
        for (int i = 0; i < n; i++)
            rank[suffix_array[i]] = i;
        return rank;
    }
    static vector<int> getLCP(const string &s, const vector<int> &suffix_array, const vector<int> &rank)
    {
        int n = suffix_array.size(), h = 0;
        vector<int> lcp(n);
        for (int i = 0; i < n; i++)
        {
            if (rank[i] == 0)
                continue;
            int p = suffix_array[rank[i] - 1];

            while (i + h < n && p + h < n && s[i + h] == s[p + h])
                h++;

            lcp[rank[i]] = h;

            if (h > 0)
                h--;
        }
        return lcp;
    }
    static tuple<vector<int>, vector<int>, vector<int>> getAll(const string &s)
    {
        vector<int> sa = getSuffixArray(s);
        vector<int> rank = getRank(sa);
        vector<int> lcp = getLCP(s, sa, rank);
        return make_tuple(sa, rank, lcp);
    }
    static void display(const string &s, const vector<int> &suffix_array, const vector<int> &lcp)
    {
        cout << "idx\tlcp\tsuffix\n";
        for (int i = 0; i < suffix_array.size(); i++)
            cout << suffix_array[i] << "\t" << lcp[i] << "\t" << s.substr(suffix_array[i]) << endl;
    }
};