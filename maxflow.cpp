/*
class Ford_Fulkerson {
public:
	Ford_Fulkerson(int _N) {
		N = _N;
		G.resize(N);
		used.resize(N, false);
	}
	struct edge { int to, cap, rev; };

	int N;
	vector<vector<edge>> G;
	vector<bool> used;

	void add_edge(int from, int to, int cap) {
		G[from].push_back({ to, cap, (int)G[to].size() });
		G[to].push_back({ from, 0, (int)G[from].size() - 1 });
	}
	int dfs(int v, int t, int f, vector <unordered_map<int, int>>& result) {
		if (v == t) { return f; }
		used[v] = true;
		for (int i = 0; i < G[v].size(); i++) {
			edge& e = G[v][i];
			if (!used[e.to] && e.cap > 0) {
				int d = dfs(e.to, t, min(f, e.cap), result);
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					if (result[v].find(e.to) == result[v].end()) {
						result[v].insert({ e.to, d });
					}
					else { result[v][e.to] += d; }
					return d;
				}
			}
		}
		return 0;
	}

	pair<vector<unordered_map<int, int>>, int> max_flow(int s, int t) {
		vector<unordered_map<int, int>> result(N);
		int flow = 0;
		while (true) {
			used.clear(); used.resize(N, false);
			int f = dfs(s, t, 1 << 30, result);
			if (f == 0) { return { result, flow }; }
			flow += f;
		}
	}
};

class Dinic {
public:
	Dinic(int _N) {
		N = _N;
		G.resize(N);
	}
	struct edge { int to, cap, rev; };

	int N;
	vector<vector<edge>> G;
	vector<int> level;
	vector<int> iter;

	void add_edge(int from, int to, int cap) {
		G[from].push_back({ to, cap, (int)G[to].size() });
		G[to].push_back({ from, 0, (int)G[from].size() - 1 });
	}
	void bfs(int s) {
		level.clear(); level.resize(N, -1);
		queue<int> que;
		level[s] = 0;
		que.push(s);
		while (que.size() > 0) {
			int v = que.front(); que.pop();
			for (int i = 0; i < G[v].size(); i++) {
				edge& e = G[v][i];
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}
	int dfs(int v, int t, int f, vector <unordered_map<int, int>>& result) {
		if (v == t) { return f; }
		for (int& i = iter[v]; i < G[v].size(); i++) {
			edge& e = G[v][i];
			if (e.cap > 0 && level[v] < level[e.to]) {
				int d = dfs(e.to, t, min(f, e.cap), result);
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					if (result[v].find(e.to) == result[v].end()) {
						result[v].insert({ e.to, d });
					}
					else { result[v][e.to] += d; }
					return d;
				}
			}
		}
		return 0;
	}

	pair<vector<unordered_map<int, int>>, int> max_flow(int s, int t) {
		vector<unordered_map<int, int>> result(N);
		int flow = 0;
		while(true) {
			bfs(s);
			if (level[t] < 0) { return { result, flow }; }
			iter.clear(); iter.resize(N, 0);
			int f;
			while ((f = dfs(s, t, 1 << 30, result)) > 0) { flow += f; }
		}
	}
};

class maxflowClass {
public:
	maxflowClass() { N = 0, M = 0; }
	maxflowClass(int _N) {
		N = 0, M = 0;
		for (int i = 0; i < _N; i++) { addNode(i); }
	}

	struct edge { int from, to; ll cap; };
	struct result { int from, to; ll flow; };

	void addNode(int n) {
		assert(mp.find(n) == mp.end());
		mp.insert({ n, N }); imap.push_back(n); N++;
		next.resize(N); back.resize(N);
	}
	void addEdge(int from, int to, ll cap) {
		assert(mp.find(from) != mp.end());
		assert(mp.find(to) != mp.end());
		from = mp[from]; to = mp[to];

		edgeData.push_back({ from, to, cap });
		next[from].push_back({ to, M }); back[to].push_back({ from, M });
		M++;
	}

	pair<vector<result>, int> ford_fulkerson(int s, int t) {
		assert(mp.find(s) != mp.end());
		assert(mp.find(t) != mp.end());
		s = mp[s]; t = mp[t];

		Ford_Fulkerson F(N);
		for (int i = 0; i < M; i++) {
			F.add_edge(edgeData[i].from, edgeData[i].to, edgeData[i].cap);
		}

		auto res = F.max_flow(s, t);
		vector<result> ans;
		for (int i = 0; i < res.first.size(); i++) {
			for (auto itr = res.first[i].begin(); itr != res.first[i].end(); itr++) {
				ans.push_back({ imap[i], itr->first,itr->second });
			}
		}
		return { ans, res.second };
	}

	pair<vector<result>, int> dinic(int s, int t) {
		assert(mp.find(s) != mp.end());
		assert(mp.find(t) != mp.end());
		s = mp[s]; t = mp[t];

		Dinic D(N);
		for (int i = 0; i < M; i++) {
			D.add_edge(edgeData[i].from, edgeData[i].to, edgeData[i].cap);
		}

		auto res = D.max_flow(s, t);
		vector<result> ans;
		for (int i = 0; i < res.first.size(); i++) {
			for (auto itr = res.first[i].begin(); itr != res.first[i].end(); itr++) {
				ans.push_back({ imap[i], itr->first,itr->second });
			}
		}
		return { ans, res.second };
	}

	void Debug(pair<vector<result>, int>& ans) {
		for (int i = 0; i < ans.first.size(); i++) {
			result& r = ans.first[i];
			cout << r.from << " --> " << r.to << " : " << r.flow << endl;
		}
		cout << "合計 = " << ans.second << endl;
	}

	int N, M;
	unordered_map<int, int> mp; // 外部のIDから内部の通し番号に
	vector<int> imap; // 内部の通し番号から外部のIDに

	vector<edge> edgeData; // 始点と終点と保持するデータ
	vector<vector<pair<int, int>>> next; // 行き先とエッジ番号
	vector<vector<pair<int, int>>> back; // 戻る先とエッジ番号
};

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(0);

	int V, E; cin >> V >> E;
	flowClass F(V);
	for (int i = 0; i < E; i++) {
		int a, b, c; cin >> a >> b >> c;
		F.addEdge(a, b, c);
	}

	cout << F.Ford_Fulkerson(0, V - 1) << endl;

	return 0;
}
*/