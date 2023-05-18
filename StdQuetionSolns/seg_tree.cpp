long long tree[int(1e7)], lazy[int(1e7)];
void push(const int &si, const int &ss, const int &se)
{
	if (lazy[si] == 0)
		return;
	tree[si] += lazy[si];
	if (ss != se)
	{
		lazy[2 * si + 1] += lazy[si];
		lazy[2 * si + 2] += lazy[si];
	}
	lazy[si] = 0;
}

long long getRange(const int si, const int ss, const int se, const int qs, const int qe)
{
	push(si, ss, se);
	if (ss > qe || qs > se)
		return LLONG_MIN;
	if (ss >= qs && se <= qe)
		return tree[si];
	int mid = (ss + se) >> 1;
	return max(getRange(2 * si + 1, ss, mid, qs, qe), getRange(2 * si + 2, mid + 1, se, qs, qe));
}

void increaseRange(const int si, const int ss, const int se, const int qs, const int qe, const long long val)
{
	push(si, ss, se);
	if (ss > qe || qs > se)
		return;
	if (ss >= qs && se <= qe)
	{
		lazy[si] += val;
		push(si, ss, se);
		return;
	}
	int mid = (ss + se) >> 1;
	increaseRange(2 * si + 1, ss, mid, qs, qe, val);
	increaseRange(2 * si + 2, mid + 1, se, qs, qe, val);

	tree[si] = max(tree[2 * si + 1], tree[2 * si + 2]);
}
