struct node
{
    long long ans,ones,zeros;
};

node inversion_calc(vi& a,int l,int r)
{
    if(l == r)
    {
        node def;
        def.ans = 0;
        def.ones = a[l];
        def.zeros = 1 - a[l];
        return def;
    }
    int mid = (l + r) >> 1;
    node left = inversion_calc(a,l,mid),right = inversion_calc(a,mid+1,r);
    node res;
    res.ans = left.ans + right.ans + (left.ones * right.zeros);
    res.ones = left.ones + right.ones;
    res.zeros = left.zeros + right.zeros;
    return res;
}
