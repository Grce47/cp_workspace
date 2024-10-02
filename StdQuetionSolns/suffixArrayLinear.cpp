struct SuffixArray
{
private:
    static inline bool leq(int a1, int a2, int b1, int b2)
    {
        return (a1 < b1 || (a1 == b1 && a2 <= b2));
    }
    static inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3)
    {
        return (a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3)));
    }
    static void radixPass(int *a, int *b, int *r, int n, int K)
    {
        int *c = new int[K + 1];
        for (int i = 0; i <= K; i++)
            c[i] = 0;
        for (int i = 0; i < n; i++)
            c[r[a[i]]]++;
        for (int i = 0, sum = 0; i <= K; i++)
        {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }
        for (int i = 0; i < n; i++)
            b[c[r[a[i]]]++] = a[i];
        delete[] c;
    }
    static void suffixArray(int *s, int *SA, int n, int K)
    {
        int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
        int *s12 = new int[n02 + 3];
        s12[n02] = s12[n02 + 1] = s12[n02 + 2] = 0;
        int *SA12 = new int[n02 + 3];
        SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = 0;
        int *s0 = new int[n0];
        int *SA0 = new int[n0];
        for (int i = 0, j = 0; i < n + (n0 - n1); i++)
            if (i % 3 != 0)
                s12[j++] = i;
        radixPass(s12, SA12, s + 2, n02, K);
        radixPass(SA12, s12, s + 1, n02, K);
        radixPass(s12, SA12, s, n02, K);
        int name = 0, c0 = -1, c1 = -1, c2 = -1;
        for (int i = 0; i < n02; i++)
        {
            if (s[SA12[i]] != c0 || s[SA12[i] + 1] != c1 || s[SA12[i] + 2] != c2)
            {
                name++;
                c0 = s[SA12[i]];
                c1 = s[SA12[i] + 1];
                c2 = s[SA12[i] + 2];
            }
            if (SA12[i] % 3 == 1)
            {
                s12[SA12[i] / 3] = name;
            }
            else
            {
                s12[SA12[i] / 3 + n0] = name;
            }
        }
        if (name < n02)
        {
            suffixArray(s12, SA12, n02, name);
            for (int i = 0; i < n02; i++)
                s12[SA12[i]] = i + 1;
        }
        else
            for (int i = 0; i < n02; i++)
                SA12[s12[i] - 1] = i;
        for (int i = 0, j = 0; i < n02; i++)
            if (SA12[i] < n0)
                s0[j++] = 3 * SA12[i];
        radixPass(s0, SA0, s, n0, K);

        for (int p = 0, t = n0 - n1, k = 0; k < n; k++)
        {
            int i = (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2);
            int j = SA0[p];
            if (SA12[t] < n0 ? leq(s[i], s12[SA12[t] + n0], s[j], s12[j / 3])
                             : leq(s[i], s[i + 1], s12[SA12[t] - n0 + 1], s[j], s[j + 1], s12[j / 3 + n0]))
            {
                SA[k] = i;
                t++;
                if (t == n02)
                    for (k++; p < n0; p++, k++)
                        SA[k] = SA0[p];
            }
            else
            {
                SA[k] = j;
                p++;
                if (p == n0)
                    for (k++; t < n02; t++, k++)
                        SA[k] = (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2);
            }
        }
        delete[] s12;
        delete[] SA12;
        delete[] SA0;
        delete[] s0;
    }

public:
    // time: O(nlogn) for hashing values + O(n) for evaluating Suffix Array
    static vector<int> getSuffixArray(vector<int> &a, bool doHashing = true)
    {
        // Requirement: hash all values of array to {1...K}.
        int n = a.size();
        int *arr = new int[n + 3];
        arr[n] = arr[n + 1] = arr[n + 2] = 0;

        if (doHashing)
        {
            // hashing: O(nlogn)
            set<int> hash_set;
            for (auto &e : a)
                hash_set.insert(e);
            vector<int> hash_order;
            for (auto &e : hash_set)
                hash_order.push_back(e);

            for (int i = 0; i < n; i++)
                arr[i] = lower_bound(hash_order.begin(), hash_order.end(), a[i]) - hash_order.begin() + 1;
        }
        else
        {
            for (int i = 0; i < n; i++)
                arr[i] = a[i];
        }

        int *ans = new int[n];

        // claim to be O(n)
        suffixArray(arr, ans, n, *max_element(arr, arr + n));

        vector<int> ret(ans, ans + n);
        delete[] ans;
        delete[] arr;

        return ret;
    }

    // time: O(128 + n) for hashing characters + O(n) for evaluating Suffix Array
    static vector<int> getSuffixArray(const string &s)
    {
        int n = s.size();

        // hashing character to {1..K}
        vector<int> exist(128, 0);
        for (auto &e : s)
            exist[(int)e] = 1;

        int K = 0;
        for (int i = 0; i < 128; i++)
            if (exist[i])
                exist[i] = ++K;

        int *arr = new int[n + 3];
        arr[n] = arr[n + 1] = arr[n + 2] = 0;
        for (int i = 0; i < n; i++)
            arr[i] = exist[(int)s[i]];

        int *ans = new int[n];

        // claim to be O(n)
        suffixArray(arr, ans, n, K);

        vector<int> ret(ans, ans + n);
        delete[] ans;
        delete[] arr;
        return ret;
    }

    static vector<int> getRank(const vector<int> &suffix_array)
    {
        int n = suffix_array.size();
        vector<int> rank(n);
        for (int i = 0; i < n; i++)
            rank[suffix_array[i]] = i;
        return rank;
    }

    // lcp[0] = 0; lcp[i] = common_pref between s.substr(suffix_array[i-1]) and s.substr(suffix_array[i])
    template <typename T>
    static vector<int> getLCP(const T &s, const vector<int> &suffix_array, const vector<int> &rank)
    {
        int n = suffix_array.size(), h = 0;
        vector<int> lcp(n);
        for (int i = 0; i < n; i++)
        {
            if (rank[i] == 0)
                continue;
            int p = suffix_array[rank[i] - 1];

            while (i + h < s.size() && p + h < s.size() && s[i + h] == s[p + h])
                h++;

            lcp[rank[i]] = h;

            if (h > 0)
                h--;
        }
        return lcp;
    }

    // auto [sa, rank, lcp] = SuffixArray::getAll(s); //(>c++17)
    template <typename T>
    static tuple<vector<int>, vector<int>, vector<int>> getAll(const T &s)
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
            cout << suffix_array[i] << "\t" << lcp[i] << "\t" << s.substr(suffix_array[i]) << "\n";
    }
};