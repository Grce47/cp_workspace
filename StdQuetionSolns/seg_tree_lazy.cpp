class Stree
{
private:
    struct segment
    {
        long long sm = 0;
        bool def = false;
    };

    segment combine(const segment &left, const segment &right)
    {
        if (left.def)
            return right;
        if (right.def)
            return left;

        segment res;
        res.def = false;

        res.sm = left.sm + right.sm;

        return res;
    }

    struct state
    {
        int ss, se, mid;
        segment val;
        state *L = NULL, *R = NULL;
        state(int _ss, int _se) : ss(_ss), se(_se), mid((_ss + _se) >> 1) {}

        bool to_push = false;
        long long lazy = 0;

        inline void push()
        {
            if (!to_push)
                return;

            val.sm += (se - ss + 1LL) * lazy;

            if (ss != se)
            {
                L->lazy += lazy;
                R->lazy += lazy;
                L->to_push = R->to_push = true;
            }
            to_push = false;
            lazy = 0;
        }
    };

    vector<state> tree;

public:
    Stree(int l, int r)
    {
        tree.reserve((r - l + 1) << 2);
        tree.emplace_back(l, r);
    }
    void buildTree(state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];
        if (cur->ss == cur->se)
        {
            cur->val.sm = 0;
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
        cur->push();

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
        cur->push();

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
        cur->push();

        if (cur->ss == cur->se)
        {
            cur->val.sm = a;
            return;
        }
        if (cur->mid >= q)
        {
            updatePoint(q, a, cur->L);
            cur->R->push();
        }
        else
        {
            updatePoint(q, a, cur->R);
            cur->L->push();
        }

        cur->val = combine(cur->L->val, cur->R->val);
    }

    void increaseRange(int qs, int qe, long long a, state *cur = NULL)
    {
        if (cur == NULL)
            cur = &tree[0];
        cur->push();

        if (cur->ss > qe || cur->se < qs)
            return;
        if (cur->ss >= qs && cur->se <= qe)
        {
            cur->to_push = true;
            cur->lazy += a;
            cur->push();
            return;
        }
        increaseRange(qs, qe, a, cur->L);
        increaseRange(qs, qe, a, cur->R);

        cur->val = combine(cur->L->val, cur->R->val);
    }
};
