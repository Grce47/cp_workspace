/*
Misc:-
	Some Optimization
	Ordered Set
	RMQ
	Sieve
	CHT
	Huffman
	Mo's Algorithm

String Algos:-
	KMP
	Z-Function
	Manacher
	Suffix Array

Graph/Tree:-
	Articulation Point/Edges
	LCA
	SCC
	HLD
	Centroid Decomposition
	Floyd Warshall
	Bellman Ford
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_N = 2e5;
const ll MOD = 1e9 + 7;

/*
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
*/

// to Optimize std::bitset::count() and __builtin_popcount()
#pragma GCC target("popcnt")

namespace OrderedSet
{
	/*
		ORDERED SET
		st.find_by_order(index) -> pointer to element of given index
		st.order_of_key(element) -> number of elements strictly less than that element
	*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
	using namespace __gnu_pbds;
	template <typename T>
	using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
}

namespace rmq
{
	template <class T>
	struct RMQ
	{
		vector<vector<T>> jmp;
		T property(T &n1, T &n2)
		{
			return max(n1, n2);
		}
		RMQ(const vector<T> &V)
		{
			int N = V.size(), on = 1, depth = 1;
			while (on < V.size())
				on *= 2, depth++;
			jmp.assign(depth, V);
			for (int i = 0; i < depth - 1; i++)
				for (int j = 0; j < N; j++)
					jmp[i + 1][j] = property(jmp[i][j],
											 jmp[i][min(N - 1, j + (1 << i))]);
		}
		// property(arr[a] ... arr[b])
		T query(int a, int b)
		{
			b++;
			assert(a < b); // or return inf if a == b
			int dep = 31 - __builtin_clz(b - a);
			return property(jmp[dep][a], jmp[dep][b - (1 << dep)]);
		}
	};
}

namespace Sieve
{
	bitset<MAX_N> isprime;
	void eratosthenes_sieve()
	{
		isprime.set();
		isprime[0] = isprime[1] = 0;
		for (int i = 4; i < MAX_N; i += 2)
			isprime[i] = 0;
		for (int i = 3; i * i < MAX_N; i += 2)
			if (isprime[i])
				for (int j = i * i; j < MAX_N; j += i * 2)
					isprime[j] = 0;
	}
}

namespace ConvexHullTrick
{
	// monotonic CHT
	// works only when q1 <= q2 <= q3... qi are queries
	// better time complexity than dynamic hull
	class MonotonicCHT
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
			// if (dq.empty())  return inf;
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
		long long ceil_div(long long a, long long b)
		{
			return (a / b - ((a ^ b) < 0 && a % b));
		}
		bool intersect(multiset<line>::iterator x, multiset<line>::iterator y)
		{
			if (y == st.end())
			{
				x->p = INF;
				return false;
			}
			if (x->m == y->m)
				x->p = (x->c > y->c) ? INF : -INF;
			else
				x->p = ceil_div((y->c - x->c), (x->m - y->m));
			return x->p >= y->p;
		}

	public:
		CHT()
		{
			mode = MIN_MODE;
		}
		void add(long long m, long long c)
		{
			auto z = st.insert({mode * m, mode * c, 0, 1});
			auto y = z++;
			auto x = y;

			while (intersect(y, z))
				z = st.erase(z);
			if (x != st.begin() and intersect(--x, y))
				intersect(x, y = st.erase(y));

			while ((y = x) != st.begin() and (--x)->p >= y->p)
				intersect(x, st.erase(y));
		}
		long long query(long long x)
		{
			if (st.empty())
				return mode * -1LL * INF;
			auto l = *st.lower_bound({0, 0, x, 0});

			return mode * (l.m * x + l.c);
		}
	};
}

namespace HuffmanEncoding
{
	class Huffman
	{
	private:
		vector<int> encodingLength;
		vector<array<int, 2>> tree;

	public:
		Huffman(const vector<int> &frequencies) : encodingLength(frequencies.size(), -1), tree(frequencies.size(), {-1, -1})
		{
			set<pair<int, int>> pq;

			int nxt = frequencies.size();
			for (int i = 0; i < nxt; i++)
				pq.insert(make_pair(frequencies[i], i));

			while (!pq.empty())
			{
				int f0 = pq.begin()->first, v0 = pq.begin()->second;
				pq.erase(pq.begin());

				if (pq.empty())
				{
					encodingLength[v0] = 0;
					break;
				}
				int f1 = pq.begin()->first, v1 = pq.begin()->second;
				pq.erase(pq.begin());

				tree[v0] = {nxt, 0};
				tree[v1] = {nxt, 1};

				pq.insert(make_pair(f0 + f1, nxt));

				encodingLength.push_back(-1);
				tree.push_back({-1, -1});
				nxt++;
			}
		}

		int getEncodingLength(int index)
		{
			return encodingLength[index] != -1 ? encodingLength[index] : (encodingLength[index] = 1 + getEncodingLength(tree[index][0]));
		}

		vector<bool> getEncoding(int index)
		{
			vector<bool> v;
			int cur = index;
			while (1)
			{
				if (tree[cur][0] != -1)
					v.push_back(tree[cur][1]);
				else
					break;
				cur = tree[cur][0];
			}
			reverse(v.begin(), v.end());
			return v;
		}
	};
}

namespace MoAlgo
{
	void add(int index)
	{
		// add index, should be O(1)
	}

	void rem(int index)
	{
		// remove index, should be O(1)
	}

	struct MoQuery
	{
		static const int block_size = 448; // sqrt(n)
		int l, r, idx;
		bool operator<(const MoQuery &o) const
		{
			int t1 = l / block_size, t2 = o.l / block_size;
			if (t1 != t2)
				return t1 < t2;
			return (t1 & 1 ? r > o.r : r < o.r);
		}
	};

	vector<int> moSolver(const vector<pair<int, int>> &rangeQueries)
	{
		int num_queries = rangeQueries.size();
		vector<MoQuery> queries(num_queries);
		vector<int> ans(num_queries);

		for (int i = 0; i < num_queries; i++)
		{
			queries[i].l = rangeQueries[i].first;
			queries[i].r = rangeQueries[i].second;
			queries[i].idx = i;
		}
		sort(queries.begin(), queries.end());

		int ptrL = queries[0].l, ptrR = queries[0].r;
		for (int i = ptrL; i <= ptrR; i++)
			add(i);

		for (auto &[l, r, idx] : queries)
		{
			while (ptrR < r)
				add(++ptrR);
			while (ptrL > l)
				add(--ptrL);
			while (ptrL < l)
				rem(ptrL++);
			while (ptrR > r)
				rem(ptrR--);

			// fill ans[idx]
		}
		return ans;
	}
}

namespace KMP
{
	/*
	s = pp$saippuakauppias
	p       p       $       s       a       i       p       p       u       a       k       a       u       p       p       i       a       s
	0       1       0       0       0       0       1       2       0       0       0       0       0       1       2       0       0       0
	*/
	vector<int> kmp(const string &s)
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
}

namespace Z_Function
{
	/*
	s = pp$saippuakauppias
	p       p       $       s       a       i       p       p       u       a       k       a       u       p       p       i       a       s
	0       1       0       0       0       0       2       1       0       0       0       0       0       2       1       0       0       0
	*/
	vector<int> z_function(const string &s)
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
}

namespace Manacher
{
	/*
	s = obsession
	#       o       #       b       #       s       #       e       #       s       #       s       #       i       #       o       #       n       #
	0       1       0       1       0       1       0       3       0       1       2       1       0       1       0       1       0       1       0
	*/
	vector<int> manacher(const string &s)
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
}

namespace SuffixArray
{
	using node = array<int, 3>;
	void radix_sort(vector<node> &a)
	{
		int n = a.size();
		for (int id = 1; id >= 0; id--)
		{
			vector<int> cnt(n);
			for (auto &x : a)
				cnt[x[id]]++;

			vector<node> tmp_a(n);
			vector<int> pos(n, 0);

			for (int i = 1; i < n; i++)
				pos[i] = pos[i - 1] + cnt[i - 1];

			for (auto &x : a)
			{
				int i = x[id];
				tmp_a[pos[i]] = x;
				pos[i]++;
			}
			a = tmp_a;
		}
	}

	vector<int> getSuffixArray(const string &_s)
	{
		string s = _s;
		s.push_back(static_cast<char>(0));

		int n = s.size();
		vector<int> sa(n), cost(n);

		int k = -1;
		do
		{
			vector<node> a(n);

			if (k == -1)
			{
				for (int i = 0; i < n; i++)
					a[i] = node{static_cast<int>(s[i]), 0, i};
				sort(a.begin(), a.end());
			}
			else
			{
				for (int i = 0; i < n; i++)
					a[i] = node{cost[i], cost[(i + (1 << k)) % n], i};
				radix_sort(a);
			}

			for (int i = 0; i < n; i++)
				sa[i] = a[i][2];

			cost[sa[0]] = 0;
			for (int i = 1; i < n; i++)
			{
				if (a[i][0] == a[i - 1][0] && a[i][1] == a[i - 1][1])
					cost[sa[i]] = cost[sa[i - 1]];
				else
					cost[sa[i]] = cost[sa[i - 1]] + 1;
			}

			k++;
		} while ((1 << k) < n);

		sa.erase(sa.begin());
		return sa;
	}

	vector<int> getRank(const vector<int> &suffix_array)
	{
		int n = suffix_array.size();
		vector<int> rank(n);
		for (int i = 0; i < n; i++)
			rank[suffix_array[i]] = i;
		return rank;
	}

	vector<int> getLCP(const string &s, const vector<int> &suffix_array, const vector<int> &rank)
	{
		int n = suffix_array.size(), h = 0;
		vector<int> lcp(n);
		for (int i = 0; i < n; i++)
		{
			if (rank[i] == 0)
				continue;
			int p = suffix_array[rank[i] - 1];

			while (i + h < n && p + h < n && s[i + h] == s[p + h])
				h++;

			lcp[rank[i]] = h;

			if (h > 0)
				h--;
		}
		return lcp;
	}
}

namespace ArticulationPoint
{
	// Global Variables
	int timer, V;
	vector<bool> vis, is_bridge;
	vector<int> in_time, low;

	void helperDFS(int cur, int par, const vector<vector<int>> &graph)
	{
		int children = 0;
		vis[cur] = 1;
		in_time[cur] = low[cur] = timer++;

		for (const int &child : graph[cur])
		{
			if (child == par)
				continue;

			if (vis[child])
			{
				low[cur] = min(low[cur], in_time[child]);
			}
			else
			{
				children++;
				helperDFS(child, cur, graph);

				low[cur] = min(low[cur], low[child]);

				if (par != -1 && low[child] >= in_time[cur])
					is_bridge[cur] = 1;
			}
		}

		if (par == -1 && children > 1)
			is_bridge[cur] = 1;
	}

	vector<int> bridgePoints(const vector<vector<int>> &graph)
	{
		vector<int> ret;

		V = graph.size();
		timer = 0;

		vis.resize(V, false);
		is_bridge.resize(V, false);
		low.resize(V, 0);
		in_time.resize(V, 0);

		for (int u = 0; u < V; u++)
			if (!vis[u])
				helperDFS(u, -1, graph);

		for (int u = 0; u < V; u++)
			if (is_bridge[u])
				ret.emplace_back(u);
		return ret;
	}
}

namespace ArticulationEdge
{
	// global variables
	int timer, V;
	vector<bool> vis;
	vector<int> in_time, low;

	void egdeDFS(int cur, int par, const vector<vector<int>> &graph, vector<pair<int, int>> &ret)
	{
		vis[cur] = 1;
		in_time[cur] = low[cur] = timer++;
		for (const int &child : graph[cur])
		{
			if (child == par)
				continue;

			if (vis[child])
			{
				low[cur] = min(low[cur], in_time[child]);
			}
			else
			{
				egdeDFS(child, cur, graph, ret);

				low[cur] = min(low[cur], low[child]);

				if (low[child] > in_time[cur])
					ret.emplace_back(cur, child);
			}
		}
	}
	vector<pair<int, int>> bridgeEdges(const vector<vector<int>> &graph)
	{
		vector<pair<int, int>> ret;

		V = graph.size();
		timer = 0;

		vis.resize(V, false);
		in_time.resize(V, 0);
		low.resize(V, 0);

		for (int i = 0; i < V; i++)
		{
			if (vis[i])
				continue;
			egdeDFS(i, -1, graph, ret);
		}

		return ret;
	}
}

namespace LCA_NORMAL
{
	// use adj_list with 0 based indexing and root of tree is 0
	struct LCA
	{
		int N;
		static const int D = 20;
		vector<vector<int>> table;

		vector<int> depth;

		LCA(vector<vector<int>> &tree)
		{
			N = tree.size();
			depth.assign(N, 0);
			table.assign(D, vector<int>(N, -1));
			dfs(0, -1, tree);
			for (int i = 1; i < D; i++)
			{
				for (int u = 0; u < N; u++)
				{
					if (table[i - 1][u] >= 0)
						table[i][u] = table[i - 1][table[i - 1][u]];
					else
						table[i][u] = -1;
				}
			}
		}

		void dfs(int u, int p, const vector<vector<int>> &tree)
		{
			table[0][u] = p;
			for (int v : tree[u])
			{
				if (v == p)
					continue;
				depth[v] = depth[u] + 1;
				dfs(v, u, tree);
			}
		}

		int up(int u, int dist)
		{
			for (int i = D - 1; i >= 0; i--)
			{
				if ((dist & (1 << i)) > 0)
				{
					u = table[i][u];
					if (u == -1)
						return -1;
				}
			}
			return u;
		}

		int lca(int u, int v)
		{
			if (depth[u] < depth[v])
			{
				return lca(v, u);
			}

			int diff = depth[u] - depth[v];
			u = up(u, diff);
			if (u == v)
				return u;

			for (int i = D - 1; i >= 0; i--)
			{
				if (table[i][u] != table[i][v])
				{
					u = table[i][u];
					v = table[i][v];
				}
			}
			return table[0][u];
		}

		int distance(int u, int v)
		{
			int w = lca(u, v);
			return depth[u] + depth[v] - 2 * depth[w];
		}
	};
}

namespace LCA_Segment
{
	struct segment
	{
		int sm;
		bool def = true;
	};

	void init(segment &res, int u)
	{
		res.def = false;

		// TODO: initialize for one length segment
		res.sm = 1;
	}

	segment combine(const segment &up, const segment &down)
	{
		if (up.def)
			return up;
		if (down.def)
			return down;

		segment res;
		res.def = false;

		// TODO : Comine up and down segment
		res.sm = up.sm + down.sm;

		return res;
	}

	struct LCA
	{
		int N;
		static const int D = 20;
		vector<vector<int>> table;
		vector<vector<segment>> seg;
		vector<int> depth;

		LCA(vector<vector<int>> &tree)
		{
			N = tree.size();
			depth.assign(N, 0);
			table.assign(D, vector<int>(N, -1));
			seg.assign(D, vector<segment>(N));
			dfs(0, -1, tree);
			for (int i = 1; i < D; i++)
			{
				for (int u = 0; u < N; u++)
				{
					if (table[i - 1][u] >= 0)
					{
						table[i][u] = table[i - 1][table[i - 1][u]];
						seg[i][u] = combine(seg[i - 1][table[i - 1][u]], seg[i - 1][u]);
					}
					else
						table[i][u] = -1;
				}
			}
		}

		void dfs(int u, int p, vector<vector<int>> &tree)
		{
			table[0][u] = p;

			init(seg[0][u], u);

			for (int v : tree[u])
			{
				if (v == p)
					continue;
				depth[v] = depth[u] + 1;
				dfs(v, u, tree);
			}
		}

		int up(int u, int dist)
		{
			for (int i = D - 1; i >= 0; i--)
			{
				if ((dist & (1 << i)) > 0)
				{
					u = table[i][u];
					if (u == -1)
						return -1;
				}
			}
			return u;
		}

		int lca(int u, int v)
		{
			if (depth[u] < depth[v])
			{
				return lca(v, u);
			}

			int diff = depth[u] - depth[v];
			u = up(u, diff);
			if (u == v)
				return u;

			for (int i = D - 1; i >= 0; i--)
			{
				if (table[i][u] != table[i][v])
				{
					u = table[i][u];
					v = table[i][v];
				}
			}
			return table[0][u];
		}

		int distance(int u, int v)
		{
			int w = lca(u, v);
			return depth[u] + depth[v] - 2 * depth[w];
		}

		// get combined segment for [u(0),u(1),u(2),....u(up_walk)] where u(i+1) is parent of u(i) and u(0) = u
		segment combined_segment(int u, int up_walk)
		{
			assert(u >= 0 && u < N);
			assert(up_walk >= 0);
			assert(depth[u] >= up_walk);

			up_walk++;
			segment res;
			for (int i = D - 1; i >= 0; i--)
			{
				if ((up_walk & (1 << i)) > 0)
				{
					if (res.def)
						res = seg[i][u];
					else
						res = combine(seg[i][u], res);
					u = table[i][u];
				}
			}
			return res;
		}
	};
}

namespace StonglyConnectedComponent
{
	// NOTE: works better for 0-based graph
	class SCC
	{
	private:
		int n;
		vector<vector<int>> rev_link, link;
		vector<int> order;
		vector<bool> visited;

		// to store post-order traversal in Original Graph
		void dfs1(int cur)
		{
			visited[cur] = true;
			for (int &child : link[cur])
			{
				if (visited[child])
					continue;
				dfs1(child);
			}
			order.push_back(cur);
		}

		void dfs2(int cur, int idx)
		{
			visited[cur] = true;
			scc[idx].insert(cur);
			scc_index[cur] = idx;
			for (int &child : rev_link[cur])
			{
				if (visited[child])
					continue;
				dfs2(child, idx);
			}
		}

		void buildScc()
		{
			fill(visited.begin(), visited.end(), false);
			int idx = 0;
			while (!order.empty())
			{
				int v = order.back();
				order.pop_back();
				if (visited[v])
					continue;
				dfs2(v, idx);
				idx++;
			}

			while (scc.back().empty())
				scc.pop_back();
		}

	public:
		vector<set<int>> scc;	   // sets of scc
		vector<int> scc_index;	   // which node belong to which indexed scc
		vector<set<int>> scc_edge; // directed edges btw sccs
		vector<int> in_order;	   // number of incoming edge for a scc
		vector<int> out_order;	   // number of outgoing edge for a scc
		int scc_no;

		void clear()
		{
			n = 0;
			scc_no = 0;
			scc.clear();
			scc_index.clear();
			scc_edge.clear();
			in_order.clear();
			out_order.clear();
		}
		void build(vector<vector<int>> &ori_link)
		{
			n = ori_link.size();
			link.resize(n);
			rev_link.resize(n);
			scc.resize(n);
			scc_index.resize(n);

			for (int i = 0; i < n; i++)
			{
				for (int &ele : ori_link[i])
				{
					rev_link[ele].push_back(i);
					link[i].push_back(ele);
				}
			}

			visited.resize(n, false);
			for (int i = 0; i < n; i++)
			{
				if (visited[i])
					continue;
				dfs1(i);
			}

			buildScc();

			link.clear();
			rev_link.clear();
			visited.clear();
			order.clear();

			scc_no = (int)scc.size();
			scc_edge.resize(scc_no);
			in_order.resize(scc_no, 0);
			out_order.resize(scc_no, 0);

			int node1, node2;
			for (int i = 0; i < n; i++)
			{
				node1 = scc_index[i];
				for (int &ele : ori_link[i])
				{
					node2 = scc_index[ele];
					if (node1 == node2)
						continue;
					if (scc_edge[node1].find(node2) != scc_edge[node1].end())
						continue;

					scc_edge[node1].insert(node2);
					in_order[node2]++;
					out_order[node1]++;
				}
			}
		}
	};
}

namespace HeavyLightDecomposition
{
	class HLD
	{
	private:
		vector<int> label, inv_label, sub_tree_size, heavy_edge;
		int n;

		void dfs1(const vector<vector<int>> &_tree, int cur, int par)
		{
			for (auto &ele : _tree[cur])
			{
				if (ele == par)
					continue;
				dfs1(_tree, ele, cur);
				sub_tree_size[cur] += sub_tree_size[ele];
			}
		}

		void dfs2(const vector<vector<int>> &_tree, int cur, int par, int &lab)
		{
			label[cur] = lab;
			inv_label[lab] = cur;

			lab++;

			// leaf node
			if (_tree[cur].size() == 1 && cur != 0)
				return;

			int mxval = -1, heavy_node = -1;

			for (auto &ele : _tree[cur])
			{
				if (ele == par)
					continue;
				if (mxval < sub_tree_size[ele])
				{
					mxval = sub_tree_size[ele];
					heavy_node = ele;
				}
			}

			dfs2(_tree, heavy_node, cur, lab);
			tree[label[cur]].push_back(label[heavy_node]);
			heavy_edge[label[cur]] = label[heavy_node];

			for (auto &ele : _tree[cur])
			{
				if (ele == heavy_node || ele == par)
					continue;
				dfs2(_tree, ele, cur, lab);
				tree[label[cur]].push_back(label[ele]);
			}
		}

		void dfs3(int cur, int par)
		{
			parent[cur] = par;
			for (auto &ele : tree[cur])
			{
				if (ele == par)
					continue;
				if (ele == heavy_edge[cur])
					chain_top[ele] = chain_top[cur];
				dfs3(ele, cur);
				if (ele == heavy_edge[cur])
					chain_length[cur] = 1 + chain_length[ele];
			}
		}

	public:
		vector<vector<int>> tree;
		vector<int> chain_top, chain_length, parent;

		HLD(vector<vector<int>> &_tree)
		{
			n = _tree.size();
			tree.resize(n);
			parent.resize(n);
			chain_length.resize(n, 1);
			label.resize(n);
			inv_label.resize(n);
			sub_tree_size.resize(n, 1);
			heavy_edge.resize(n, -1);

			chain_top.resize(n);
			iota(chain_top.begin(), chain_top.end(), 0);

			dfs1(_tree, 0, -1);
			int cnt = 0;
			dfs2(_tree, 0, -1, cnt);
			dfs3(0, -1);
		}

		/// @brief Gives node number in new labeled tree
		inline int get_label(const int &original_node)
		{
			return label[original_node];
		}

		/// @brief Gives node number of original tree from labeled value
		inline int get_original(const int &labeled_node)
		{
			return inv_label[labeled_node];
		}
	};
}

namespace Centroid_Decomposition
{
	class CentroidDecomposition
	{
	private:
		int n;
		vector<bool> vis;
		vector<int> sz;
		const vector<vector<int>> &tree;

		int find_size(int v, int p = -1)
		{
			if (vis[v])
				return 0;
			sz[v] = 1;
			for (const int &x : tree[v])
				if (x != p)
					sz[v] += find_size(x, v);
			return sz[v];
		}

		int find_centroid(int v, int p, int cur_sz)
		{
			for (const int &x : tree[v])
				if (x != p)
					if (!vis[x] && sz[x] > (cur_sz / 2))
						return find_centroid(x, v, cur_sz);
			return v;
		}

		void init_centroid(int v, int p)
		{
			find_size(v);
			int c = find_centroid(v, -1, sz[v]);
			vis[c] = true;
			centroid_par[c] = p;
			if (p == -1)
				root = c;
			else
				centorid_tree[p].push_back(c);
			for (const int &x : tree[c])
				if (!vis[x])
					init_centroid(x, c);
		}

	public:
		vector<vector<int>> centorid_tree;
		vector<int> centroid_par;
		int root;
		CentroidDecomposition(vector<vector<int>> &_tree) : tree(_tree)
		{
			root = 0;
			n = tree.size();
			centorid_tree.resize(n);
			vis.resize(n, false);
			sz.resize(n, 0);
			centroid_par.resize(n, -1);
			init_centroid(0, -1);
		}
	};
}

namespace FloydWarshall
{

}

namespace BellmanFord
{
	const long long inf = 1e17;

	// fills dist array; if -inf --> dist of some node; then there exists -ve cycle;
	void bellmanFord(const vector<tuple<int, int, long long>> &edge, vector<long long> &dist, int src = 0)
	{
		int n = dist.size();
		fill(dist.begin(), dist.end(), inf);
		dist[src] = 0;

		auto oneIteration = [&](bool last = false) -> bool
		{
			bool changed = 0;
			for (const auto &[u, v, w] : edge)
			{
				if (dist[u] == inf)
					continue;
				if (dist[v] > w + dist[u])
				{
					if (last)
						dist[v] = -inf;
					else
						dist[v] = w + dist[u];
					changed = 1;
				}
			}
			return changed;
		};

		int relax = n;
		for (int i = 0; i < relax; i++)
			if (!oneIteration())
				break;

		for (int i = 0; i < relax; i++)
			if (!oneIteration(true))
				break;
	}
}
