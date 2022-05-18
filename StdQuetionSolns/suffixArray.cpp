// Suffix Array
#define sz(a) a.size()
typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits)
{ // (optional)
    // this is just 3 times faster than stl sort for N=10^6
    int mask = (1 << bits) - 1;
    rep(it, 0, 2)
    {
        int move = it * bits;
        vi q(1 << bits), w(sz(q) + 1);
        rep(i, 0, sz(b))
            q[(b[i].first >> move) & mask]++;
        partial_sum(q.begin(), q.end(), w.begin() + 1);
        vector<pli> res(b.size());
        rep(i, 0, sz(b))
            res[w[(b[i].first >> move) & mask]++] = b[i];
        swap(b, res);
    }
}
struct SuffixArray
{
    vi a;
    vi lcp;
    vi rank;
    string s;
    SuffixArray(const string &_s) : s(_s + '\0')
    {
        int N = sz(s);
        vector<pli> b(N);
        a.resize(N);
        rep(i, 0, N)
        {
            b[i].first = s[i];
            b[i].second = i;
        }

        int q = 8;
        while ((1 << q) < N)
            q++;
        for (int moc = 0;; moc++)
        {
            count_sort(b, q); // sort(all(b)) can be used as well
            a[b[0].second] = 0;
            rep(i, 1, N)
                a[b[i].second] = a[b[i - 1].second] +
                                 (b[i - 1].first != b[i].first);

            if ((1 << moc) >= N)
                break;
            rep(i, 0, N)
            {
                b[i].first = (ll)a[i] << q;
                if (i + (1 << moc) < N)
                    b[i].first += a[i + (1 << moc)];
                b[i].second = i;
            }
        }
        rep(i, 0, sz(a)) a[i] = b[i].second;
        calc_lcp();
        rank.resize(N);
        rep(i, 0, rank.size()) rank[a[i]] = i;
    }
    void calc_lcp()
    {
        // longest common prefixes: res[i] = lcp(a[i], a[i-1])
        int n = sz(a), h = 0;
        lcp.resize(n);
        vi inv(n);
        rep(i, 0, n) inv[a[i]] = i;
        rep(i, 0, n) if (inv[i] > 0)
        {
            int p0 = a[inv[i] - 1];
            while (s[i + h] == s[p0 + h])
                h++;
            lcp[inv[i]] = h;
            if (h > 0)
                h--;
        }
    }
    void display()
    {
        cout << "String : " << s << "\n{index , lcp}\n";
        rep(i, 0, sz(a))
        {
            cout << i << " -> ";
            cout << a[i] << " , " << lcp[i] << " : " << s.substr(a[i], sz(a) - a[i]) << "\n";
        }
    }
};
// END suffix Array