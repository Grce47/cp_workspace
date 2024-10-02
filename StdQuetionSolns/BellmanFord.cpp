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