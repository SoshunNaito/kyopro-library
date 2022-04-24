template <typename Cap, typename Cost>
class MincostflowSolver
{
public:
	MincostflowSolver(int N)
	{
		V = N;
		G.resize(N);
		h.resize(N);
		dist.resize(N);
		prevv.resize(N);
		preve.resize(N);
	}

	typedef pair<int, int> P;
	struct edge
	{
		int to;
		Cap cap;
		Cost cost;
		int rev;
	};

	int V;
	vector<vector<edge>> G;
	vector<int> h;
	vector<int> dist;
	vector<int> prevv, preve;

	void add_edge(int from, int to, Cap cap, Cost cost)
	{
		G[from].push_back({to, cap, cost, (int)G[to].size()});
		G[to].push_back({from, 0, -cost, (int)G[from].size() - 1});
	}

	vector<pair<Cap, Cost>> min_cost_flow(int s, int t, Cap f)
	{
		Cost res = 0;
		vector<pair<Cap, Cost>> ans;
		ans.push_back({0, 0});

		h.clear();
		h.resize(V, 0);
		while (f > 0)
		{
			priority_queue<P, vector<P>, greater<P>> que;
			dist.clear();
			dist.resize(V, 1 << 30);
			dist[s] = 0;
			que.push(P(0, s));
			while (que.size() > 0)
			{
				P p = que.top();
				que.pop();
				int v = p.second;
				if (dist[v] < p.first)
				{
					continue;
				}
				for (int i = 0; i < G[v].size(); i++)
				{
					edge &e = G[v][i];
					if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to])
					{
						dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
						prevv[e.to] = v;
						preve[e.to] = i;
						que.push(P(dist[e.to], e.to));
					}
				}
			}
			if (dist[t] == (1 << 30))
			{
				break;
			}
			for (int v = 0; v < V; v++)
			{
				h[v] += dist[v];
			}

			Cap d = f;
			for (int v = t; v != s; v = prevv[v])
			{
				d = min(d, G[prevv[v]][preve[v]].cap);
			}
			f -= d;
			res += d * h[t];
			ans.push_back({ans[ans.size() - 1].first + d, res});

			for (int v = t; v != s; v = prevv[v])
			{
				edge &e = G[prevv[v]][preve[v]];
				e.cap -= d;
				G[v][e.rev].cap += d;
			}
		}
		return ans;
	}
};

template <typename Cap, typename Cost>
class mincostflowClass
{
public:
	mincostflowClass() { N = 0, M = 0; }
	mincostflowClass(int _N)
	{
		N = 0, M = 0;
		for (int i = 0; i < _N; i++)
		{
			addNode(i);
		}
	}

	struct edge
	{
		int from, to;
		Cap cap;
		Cost cost;
	};
	struct result
	{
		int from, to;
		Cap flow;
		Cost total;
	};

	void addNode(int n)
	{
		assert(mp.find(n) == mp.end());
		mp.insert({n, N});
		imap.push_back(n);
		N++;
		next.resize(N);
		back.resize(N);
	}
	void addEdge(int from, int to, Cap cap, Cost cost)
	{
		assert(mp.find(from) != mp.end());
		assert(mp.find(to) != mp.end());
		from = mp[from];
		to = mp[to];

		edgeData.push_back({from, to, cap, cost});
		next[from].push_back({to, M});
		back[to].push_back({from, M});
		M++;
	}

	vector<pair<Cap, Cost>> solve(int s, int t, Cap f = (1 << 30))
	{
		assert(mp.find(s) != mp.end());
		assert(mp.find(t) != mp.end());
		s = mp[s];
		t = mp[t];

		MincostflowSolver<Cap, Cost> solver(N);
		for (int i = 0; i < M; i++)
		{
			solver.add_edge(edgeData[i].from, edgeData[i].to, edgeData[i].cap, edgeData[i].cost);
		}

		return solver.min_cost_flow(s, t, f);
	}

	void Debug(vector<pair<Cap, Cost>> &ans)
	{
		for (int i = 0; i < ans.size(); i++)
		{
			cout << "( " << ans[i].first << ", " << ans[i].second << " )" << endl;
		}
	}

	int N, M;
	unordered_map<int, int> mp; // 外部のIDから内部の通し番号に
	vector<int> imap;			// 内部の通し番号から外部のIDに

	vector<edge> edgeData;				 // 始点と終点と保持するデータ
	vector<vector<pair<int, int>>> next; // 行き先とエッジ番号
	vector<vector<pair<int, int>>> back; // 戻る先とエッジ番号
};

int main()
{
	ios::sync_with_stdio(false);
	std::cin.tie(0);

	int V, E, F;
	cin >> V >> E >> F;
	mincostflowClass<int, int> MF(V);
	for (int i = 0; i < E; i++)
	{
		int u, v, c, d;
		cin >> u >> v >> c >> d;
		MF.addEdge(u, v, c, d);
	}

	auto ans = MF.solve(0, V - 1);

	if (ans.back().first < F)
	{
		cout << -1 << endl;
	}
	else
	{
		for (int i = 1; i < ans.size(); i++)
		{
			if (ans[i - 1].first <= F && F <= ans[i].first)
			{
				cout << ans[i - 1].second + (ans[i].second - ans[i - 1].second) *
												(F - ans[i - 1].first) / (ans[i].first - ans[i - 1].first)
					 << endl;
				break;
			}
		}
	}

	return 0;
}