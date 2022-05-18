//START seg_tree
struct segment
{
    long long sum_value;
    bool def = false;
};

class Stree
{
private:
    segment combine(segment left, segment right)
    {
        if (left.def) return right;
        if (right.def) return left;

        segment res;
        res.def = false;

        res.sum_value = left.sum_value + right.sum_value;

        return res;
    }

    Stree* L = NULL;
    Stree* R = NULL;
    int ss, se;
    int mid;
    bool isOut(int qs, int qe)
    {
        return (ss > qe || se < qs);
    }
    bool isIn(int qs, int qe)
    {
        return (ss >= qs && se <= qe);
    }
    void clear()
    {
        if (ss == se) return;

        L->clear();
        R->clear();

        delete L;
        delete R;

        ss = se = mid = 0;
    }

    void push()
    {
        if (!to_push) return;

        val.sum_value += (long long)(se - ss + 1) * lazy;

        if (ss != se)
        {
            L->to_push = R->to_push = true;
            L->lazy += lazy;
            R->lazy += lazy;
        }
        lazy = 0;
        to_push = false;
    }
    bool to_push = false;
    long long lazy = 0;
    segment val;
public:

    Stree(int SS, int SE)
    {
        ss = SS;
        se = SE;
        mid = (ss + se) >> 1;
        val.def = false;
    }
    ~Stree() { clear(); }

    void buildTree()
    {
        if (ss == se)
        {
            val.sum_value = 0;
            return;
        }
        if (!L) L = new Stree(ss, mid);
        if (!R) R = new Stree(mid + 1, se);
        L->buildTree();
        R->buildTree();

        val = combine(L->val, R->val);
    }

    segment getVal(int q)
    {
        push();
        if (ss == se) return val;
        if (mid >= q) return L->getVal(q);
        return R->getVal(q);
    }
    segment getRangeVal(int qs, int qe)
    {
        push();
        if (isOut(qs, qe))
        {
            segment def;
            def.def = true;
            return def;
        }
        if (isIn(qs, qe)) return val;
        return combine(L->getRangeVal(qs, qe), R->getRangeVal(qs, qe));
    }
    void increaseRange(int qs, int qe, long long a)
    {
        push();
        if (isOut(qs, qe)) return;
        if (ss >= qs && se <= qe)
        {
            to_push = true;
            lazy += a;
            push();
            return;
        }

        L->increaseRange(qs, qe, a);
        R->increaseRange(qs, qe, a);

        val = combine(L->val, R->val);
    }

};
//END seg_tree