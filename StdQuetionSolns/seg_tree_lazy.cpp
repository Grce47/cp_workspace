struct segment
{
    long long mn;
    bool def = false;
};

class Stree
{
private:
    segment combine(const segment &left, const segment &right)
    {
        if (left.def)
            return right;
        if (right.def)
            return left;

        segment res;
        res.def = false;

        res.mn = min(left.mn, right.mn);
        return res;
    }

    struct state
    {
        int ss, se, mid;
        segment val;
        long long lazy = 0;
        bool to_push = false;
        state *L = NULL, *R = NULL;
        state(int _ss, int _se) : ss(_ss), se(_se), mid((_ss + _se) >> 1) {}
    };

    void push(state *cur)
    {
        if (!cur->to_push)
            return;
        cur->val.mn += cur->lazy;
        if (cur->ss != cur->se)
        {
            cur->L->to_push = cur->R->to_push = true;
            cur->L->lazy += cur->lazy;
            cur->R->lazy += cur->lazy;
        }
        cur->to_push = false;
        cur->lazy = 0;
    }

    vector<state> tree;

public:
    Stree(int l, int r)
    {
        tree.reserve(((r - l + 1) << 2) + 5);
        tree.emplace_back(l, r);
    }
    void buildTree(state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];
        if (cur->ss == cur->se)
        {
            cur->val.mn = 0;
            return;
        }

        if (cur->L == NULL)
        {
            tree.emplace_back(cur->ss, cur->mid);
            cur->L = &tree.back();
        }

        if (cur->R == NULL)
        {
            tree.emplace_back(cur->mid + 1, cur->se);
            cur->R = &tree.back();
        }

        buildTree(cur->L);
        buildTree(cur->R);

        cur->val = combine(cur->L->val, cur->R->val);
    }

    segment getVal(int q, state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];

        push(cur);

        if (cur->ss == cur->se)
            return cur->val;

        if (cur->mid >= q)
            return getVal(q, cur->L);
        return getVal(q, cur->R);
    }

    segment getRangeVal(int qs, int qe, state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];

        push(cur);

        if (cur->ss > qe || cur->se < qs)
        {
            segment def;
            def.def = true;
            return def;
        }
        if (cur->ss >= qs && cur->se <= qe)
            return cur->val;

        return combine(getRangeVal(qs, qe, cur->L), getRangeVal(qs, qe, cur->R));
    }

    void updatePoint(int q, long long a, state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];

        push(cur);

        if (cur->ss == cur->se)
        {
            cur->val.mn = a;
            return;
        }

        push(cur->L);
        push(cur->R);

        if (cur->mid >= q)
            updatePoint(q, a, cur->L);
        else
            updatePoint(q, a, cur->R);

        cur->val = combine(cur->L->val, cur->R->val);
    }

    void updateRange(int qs, int qe, long long a, state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];

        push(cur);

        if (cur->ss > qe || qs > cur->se)
            return;
        if (cur->ss >= qs && cur->se <= qe)
        {
            cur->to_push = true;
            cur->lazy += a;
            push(cur);
            return;
        }
        updateRange(qs, qe, a, cur->L);
        updateRange(qs, qe, a, cur->R);

        cur->val = combine(cur->L->val, cur->R->val);
    }
};