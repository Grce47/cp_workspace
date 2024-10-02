// monotonic CHT
// works only when q1 <= q2 <= q3... qi are queries
// better time complexity than dynamic hull
class CHT
{
private:
    struct Line
    {
        long long slope, yIntercept;

        Line(long long slope, long long yIntercept) : slope(slope), yIntercept(yIntercept) {}

        long long val(long long x)
        {
            return slope * x + yIntercept;
        }

        long long intersect(Line y)
        {
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };
    deque<pair<Line, long long>> dq;

public:
    void insert(long long slope, long long yIntercept)
    {
        Line newLine(slope, yIntercept);

        while (dq.size() > 1 && dq.back().second >= dq.back().first.intersect(newLine))
            dq.pop_back();

        if (dq.empty())
        {
            dq.emplace_back(newLine, 0);
            return;
        }

        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }

    long long query(long long x)
    {
        // if (dq.empty())
        //     return inf;
        while (dq.size() > 1)
        {
            if (dq[1].second <= x)
                dq.pop_front();
            else
                break;
        }

        return dq[0].first.val(x);
    }
};

// dynamic CHT
struct CHT
{
private:
    static const int MIN_MODE = -1, MAX_MODE = 1;
    static const long long INF = 1e17;

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
        mode = MIN_MODE;
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
        if (st.empty())
            return mode * -1LL * INF;
        auto l = *st.lower_bound({0, 0, x, 0});

        return mode * (l.m * x + l.c);
    }
};
