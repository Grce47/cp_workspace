struct CHT
{
private:
    enum
    {
        MIN_MODE = -1,
        MAX_MODE = 1,
        INF = 1000000000
    };
    struct line
    {
        mutable long long m, c, p, isline;
        bool operator<(const line &o) const
        {
            return ((o.isline) ? (m < o.m) : (p < o.p));
        }
    };
    multiset<line> st;
    long long mode;
    long long div(long long a, long long b)
    {
        return (a / b - ((a ^ b) < 0 && a % b));
    }
    bool isect(multiset<line>::iterator x, multiset<line>::iterator y)
    {
        if (y == st.end())
        {
            x->p = INF;
            return false;
        }
        if (x->m == y->m)
            x->p = (x->c > y->c) ? INF : -INF;
        else
            x->p = div((y->c - x->c), (x->m - y->m));
        return x->p >= y->p;
    }

public:
    CHT()
    {
        mode = MAX_MODE;
    }
    void add(long long m, long long c)
    {
        auto z = st.insert({mode * m, mode * c, 0, 1}), y = z++, x = y;

        while (isect(y, z))
            z = st.erase(z);
        if (x != st.begin() and isect(--x, y))
            isect(x, y = st.erase(y));

        while ((y = x) != st.begin() and (--x)->p >= y->p)
            isect(x, st.erase(y));
    }
    long long query(long long x)
    {
        assert(!st.empty());
        auto l = *st.lower_bound({0, 0, x, 0});

        return mode * (l.m * x + l.c);
    }
};
