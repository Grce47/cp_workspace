/*
s = pp$saippuakauppias
p       p       $       s       a       i       p       p       u       a       k       a       u       p       p       i       a       s
0       1       0       0       0       0       1       2       0       0       0       0       0       1       2       0       0       0
*/
vector<int> prefix_function(const string &s)
{
	int n = (int)s.length();
	vector<int> pi(n);
	for (int i = 1; i < n; i++)
	{
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

/*
s = pp$saippuakauppias
p       p       $       s       a       i       p       p       u       a       k       a       u       p       p       i       a       s
0       1       0       0       0       0       2       1       0       0       0       0       0       2       1       0       0       0
*/
vector<int> z_function(const string& s)
{
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++)
	{
		if (i < r) 
			z[i] = min(r - i, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) 
			z[i]++;
		if (i + z[i] > r)
		{
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

/*
s = obsession
#       o       #       b       #       s       #       e       #       s       #       s       #       i       #       o       #       n       #
0       1       0       1       0       1       0       3       0       1       2       1       0       1       0       1       0       1       0
*/
vector<int> manacher(const string& s)
{
	string T = "#";
	for (char c : s)
	{
		T += c;
		T += '#';
	}
	int n = T.length();
	vector<int> P(n, 0);
	int C = 0, R = 0;
	for (int i = 0; i < n; i++)
	{
		int mirr = 2 * C - i;
		if (i < R)
			P[i] = min(R - i, P[mirr]);
		int a = i + (1 + P[i]);
		int b = i - (1 + P[i]);
		while (a < n && b >= 0 && T[a] == T[b])
		{
			P[i]++;
			a++;
			b--;
		}
		if (i + P[i] > R)
		{
			C = i;
			R = i + P[i];
		}
	}
	return P;
}
// usage example (to get longest pallandromic substring): getBoundary(max_element(manacherResult.begin(),manacherResult.end())-manacherResult.begin(),manacherResult);
pair<int, int> getBoundary(int manacherIdx, const vector<int> &manacherResult)
{
	int x = manacherIdx >> 1;
	int y = manacherResult[manacherIdx] >> 1;
	return make_pair(x - y, x + y - (manacherIdx % 2 == 0 ? 1 : 0));
}
