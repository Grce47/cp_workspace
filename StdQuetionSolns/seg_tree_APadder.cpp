struct segment
{
    int64_t sum_value;
};
 
class Stree
{
private:
    segment combine(segment data1, segment data2)
    {
        segment res;
        res.sum_value = data1.sum_value + data2.sum_value;
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
    void push()
    {
        if (!to_push) return;
 
        int64_t no = se - ss + 1;
        val.sum_value += ((no * ((2LL * lazy.first) + ((no - 1LL) * lazy.second))) >> 1);
 
        if (ss != se)
        {
            L->lazy.first += lazy.first;
            L->lazy.second += lazy.second;
 
            R->lazy.second += lazy.second;
            int64_t lno = L->se - L->ss + 1;
            R->lazy.first += (lazy.first + (lno * lazy.second));
 
            L->to_push = true;
            R->to_push = true;
        }
        lazy.first = lazy.second = 0;
        to_push = false;
    }
    bool to_push = false;
    pair<int64_t, int64_t> lazy = make_pair(0LL, 0LL);
    segment val;
public:
 
    Stree(int SS, int SE)
    {
        ss = SS;
        se = SE;
        mid = (ss + se) >> 1;
    }
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
        if (isOut(qs, qe)) return (segment) { 0 };
        if (isIn(qs, qe)) return val;
        return combine(L->getRangeVal(qs, qe), R->getRangeVal(qs, qe));
    }
    void increaseRange(int qs, int qe, int64_t a, int64_t d)
    {
        push();
        if (isOut(qs, qe)) return;
        if (ss >= qs && se <= qe)
        {
            to_push = true;
            int64_t lno = ss - qs;
            lazy.first += a + (lno * d);
            lazy.second += d;
            push();
            return;
        }
 
        L->increaseRange(qs, qe, a, d);
        R->increaseRange(qs, qe, a, d);
 
        val = combine(L->val, R->val);
    }
 
};
//END seg_tree