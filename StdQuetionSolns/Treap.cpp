random_device rd;
mt19937 gen(rd());

class Treap
{
private:
    int priority, subTreeSize;
    array<Treap *, 2> kids;

    static int size(Treap *me)
    {
        return me == NULL ? 0 : me->subTreeSize;
    }
    static void recalc(Treap *me)
    {
        if (me == NULL)
            return;

        me->subTreeSize = 1;
        for (auto &kid : me->kids)
            me->subTreeSize += size(kid);

        // EDIT THIS!!
        me->sum = me->data;
        for (auto &kid : me->kids)
            if (kid != NULL)
                me->sum += kid->sum;
        ///////////////////
    }

    static void prop(Treap *me)
    {
        if (me == NULL)
            return;

        // EDIT THIS!!
        if (!me->to_reverse)
            return;

        swap(me->kids[0], me->kids[1]);

        for (auto &kid : me->kids)
            if (kid != NULL)
                kid->to_reverse ^= 1;

        me->to_reverse = 0;
        /////////////////

        recalc(me);
    }

    // Customize Treap Here
    using datatype = long long;
    int to_reverse;
    datatype data, sum;
    //////////////////

public:
    Treap(datatype _data)
    {
        priority = gen();
        kids = {NULL, NULL};

        // Initialize your custom data
        data = _data;
        sum = _data;
        to_reverse = 0;
        ////////////////

        recalc(this);
    }

    static array<Treap *, 2> split(Treap *me, int nInLeft)
    {
        if (me == NULL)
            return {NULL, NULL};

        prop(me);

        if (size(me->kids[0]) >= nInLeft)
        {
            array<Treap *, 2> leftRes = split(me->kids[0], nInLeft);
            me->kids[0] = leftRes[1];
            recalc(me);
            return {leftRes[0], me};
        }

        nInLeft = nInLeft - size(me->kids[0]) - 1;
        array<Treap *, 2> rightRes = split(me->kids[1], nInLeft);
        me->kids[1] = rightRes[0];
        recalc(me);
        return {me, rightRes[1]};
    }

    static Treap *merge(Treap *l, Treap *r)
    {
        if (l == NULL)
            return r;
        if (r == NULL)
            return l;

        prop(l);
        prop(r);

        if (l->priority < r->priority)
        {
            l->kids[1] = merge(l->kids[1], r);
            recalc(l);
            return l;
        }
        else
        {
            r->kids[0] = merge(l, r->kids[0]);
            recalc(r);
            return r;
        }
    }

    static void reverseRange(Treap *&root, int l, int r)
    {
        array<Treap *, 2> sp = split(root, l);
        array<Treap *, 2> focus = split(sp[1], r - l + 1);

        focus[0]->to_reverse ^= 1;

        root = merge(sp[0], merge(focus[0], focus[1]));
    }
    
    static vector<datatype> inOrder(Treap *root)
    {
        vector<datatype> res;
        auto dfs = [&res](auto &&self, Treap *cur) -> void
        {
            if (cur == NULL)
                return;
            prop(cur);
            self(self, cur->kids[0]);
            res.push_back(cur->data);
            self(self, cur->kids[1]);
        };

        dfs(dfs, root);
        return res;
    }
};
