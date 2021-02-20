/*
////////////////	UnionFind
#define UnionFind dsu


/////////////         UnionFind
//    バラバラの要素を結合してグループにまとめる際に使える構造。
//    グループ番号、要素数の取得が可能だが、グループに属する要素の列挙はO(N)かかる。

#define USE_UNIONFIND
class UnionFindClass {
public:
	UnionFindClass() { N = 0; }
	UnionFindClass(int n) { activate(n); }

	void activate(int n) {// 要素の数N
		N = n;
		parent.clear(); parent.resize(N, -1);
		size.clear(); size.resize(N, 1);
	}
	inline int getParent(int x) {// グループの親の番号を得る
		if (parent[x] == -1) { return x; }
		int y = getParent(parent[x]);
		parent[x] = y;
		return y;
	}
	inline int getSize(int x) {// 自分が属するグループのサイズを得る
		return size[getParent(x)];
	}
	inline bool connect(int x, int y) {// 二つの要素を結ぶ。２グループ間を繋いだ場合trueを返す
		x = getParent(x), y = getParent(y);
		if (x == y) { return false; }
		if (size[x] < size[y]) {
			parent[x] = y;
			size[y] += size[x];
			size[x] = 0;
		}
		else {
			parent[y] = x;
			size[x] += size[y];
			size[y] = 0;
		}
		return true;
	}

	int N;// 個数
	vector<int> parent;// 親の番号。自分自身が親なら-1。
	vector<int> size;// 親のみ有効。自分のグループのサイズ。
};



/////////////		グラフを扱うクラス
struct EdgeType {
	EdgeType() {
		from = 0, to = 0;
		weight = 1LL;
	}
	EdgeType(int _from, int _to, ll _weight) {
		from = _from; to = _to; weight = _weight;
	}
	int from, to;
	ll weight;
};
class GraphClass {// グラフ入力を受け取る
public:
	GraphClass(int n, bool directed) {// 頂点数nのグラフを初期化する
		directedFlag = directed;
		N = n; M = 0;
		next.resize(N);
	}
	inline void addEdge(EdgeType e) {// エッジ追加
		int n = (int)edge.size();
		edge.push_back(e); M++;
		next[e.from].push_back({ e.to, n });
		if (directedFlag == false) { next[e.to].push_back({ e.from, n }); }
	}
	inline void addEdge(int x, int y, ll weight = 1) {// エッジ追加
		addEdge({ x,y,weight });
	}
	bool isTree() {// 木になっているかどうか幅優先探索で調べる
		if (N <= 0 || M != N - 1) { return false; }

		vector<bool> visited(N, false); visited[0] = true;
		queue<int> q; q.push(0);
		while (q.size() > 0) {
			int n = q.front(); q.pop();
			visited[n] = true;
			for (auto itr = next[n].begin(); itr != next[n].end(); itr++) {
				if (visited[itr->first] == false) { q.push(itr->first); }
			}
		}
		for (int i = 0; i < N; i++) {
			if (visited[i] == false) { return false; }
		}
		return true;
	}
#ifdef USE_TREE
#ifdef USE_UNIONFIND
	TreeClass* kruskal() {// クラスカル法によって最小全域木を構成する
		TreeClass* T = new TreeClass(N);
		UnionFindClass uf; uf.activate(N);

		vector<pair<ll, pair<int, int>>> E;
		for (int i = 0; i < edge.size(); i++) {
			E.push_back({ edge[i].weight, {edge[i].from, edge[i].to} });
		}
		sort(E.begin(), E.end());

		for (auto itr = E.begin(); itr != E.end(); itr++) {
			int x = itr->second.first, y = itr->second.second; ll w = itr->first;
			if (uf.getParent(x) != uf.getParent(y)) {
				T->addEdge(x, y, w); uf.connect(x, y);
			}
		}
		return T;
	}
#endif
#endif
	void dijkstra(int n, vector<ll>& buf) {// ダイクストラ法で始点nからの最短距離を得る
		assert(n >= 0 && n < N);

		buf.clear(); buf.resize(N, INF); buf[n] = 0;
		set<pair<ll, int>> st; st.insert({ 0, n });
		while (st.size() > 0) {
			const pair<ll, int> p = *st.begin(); st.erase(st.begin());
			const int x = p.second;

			if (p.first <= buf[x]) {
				for (auto itr = next[x].begin(); itr != next[x].end(); itr++) {
					const int y = itr->first;
					const EdgeType e = edge[itr->second];
					if (buf[y] > buf[x] + e.weight) {
						buf[y] = buf[x] + e.weight;
						st.insert({ buf[y], y });
					}
				}
			}
		}
	}

	bool bellmanFord(int n, vector<ll>& buf) {// ベルマンフォード法で始点nからの最短距離を得る
		assert(n >= 0 && n < N);

		buf.clear(); buf.resize(N, INF); buf[n] = 0;
		vector<bool> wait(N, false); wait[0] = true;
		vector<int> count(N, 0); count[0]++;
		queue<int> que; que.push(0);

		while (que.size() > 0) {
			const int x = que.front(); que.pop();
			wait[x] = false;
			for (auto itr = next[x].begin(); itr != next[x].end(); itr++) {
				const int y = itr->first;
				const EdgeType e = edge[itr->second];
				if (buf[y] <= buf[x] + e.weight) { continue; }
				buf[y] = buf[x] + e.weight;
				if (wait[y] == false) {
					wait[y] = true; count[y]++; que.push(y);
					if (count[y] == N) { return false; }
				}
			}
		}
		return true;
	}

	bool getDistanceFrom(int n, vector<ll>& buf) {// ある点からの最短距離の表を受け取る。
		assert(n >= 0 && n < N);

		bool negativeFlag = false;
		for (int i = 0; i < edge.size(); i++) {
			if (edge[i].weight < 0) { negativeFlag = true; break; }
		}
		if (negativeFlag) {// 負の重みがあればベルマンフォード法
			return bellmanFord(n, buf);
		}
		else {// 全て非負ならダイクストラ法
			dijkstra(n, buf); return true;
		}
	}

	vector<vector<ll>> getDistanceTable() {// 最短距離の表を受け取る。対角成分に非ゼロが含まれていたら、重み負の閉路が存在している。
		vector<vector<ll>> buf(N);
		for (int i = 0; i < N; i++) {
			buf[i].resize(N, INF);
			buf[i][i] = 0;
		}

		bool negativeFlag = false;
		for (int i = 0; i < edge.size(); i++) {
			if (edge[i].weight < 0) { negativeFlag = true; break; }
		}
		if (negativeFlag == false) {// 全て0以上だったらダイクストラ法を使う
			for (int i = 0; i < N; i++) { dijkstra(i, buf[i]); }
		}
		else {// 負の重みが含まれていたらワーシャルフロイド法を使う
			for (int i = 0; i < N; i++) {
				for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
					buf[i][itr->first] = edge[itr->second].weight;
				}
			}
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					for (int k = 0; k < N; k++) {
						chmin(buf[j][k], buf[j][i] + buf[i][k]);
					}
				}
			}
		}
		return buf;
	}

	void debugCout() {// デバッグ出力用
		cout << endl;
		cout << "ノードの個数 = " << N << "個" << endl;
		cout << "エッジの本数 = " << M << "本" << endl;
		cout << endl;

		for (int i = 0; i < N; i++) {
			cout << "i = " << i << " (nodeWeight = " << nodeWeight[i] << "), 接続先 = ";
			if (next[i].size() == 0) { cout << "なし" << endl; continue; }
			auto itr = next[i].begin();
			cout << itr->first << "(weight = " << edge[itr->second].weight << ")";
			itr++;

			for (; itr != next[i].end(); itr++) {
				cout << ", " << itr->first << "(weight = " << edge[itr->second].weight << ")";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool directedFlag;// 有向グラフかどうか
	int N, M;
	vector<ll> nodeWeight;// ノードの重み
	vector<vector<pair<int, int>>> next;// 各ノードからの行き先とエッジ番号
	vector<EdgeType> edge;// エッジ(頂点ペアと重み)
};

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(0);

	int N, M; cin >> N >> M;
	GraphClass G(N, false);
	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b; a--, b--;
		G.addEdge(a, b);
	}

	G.debugCout();// デバッグ出力

	G.removeEdge(1, 3);
	G.removeEdge(3, 5);

	G.debugCout();// デバッグ出力

	cout << "最短距離の表" << endl;
	auto table = G.getDistanceTable();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
//////		検証用入力データ
7 10
1 3
1 5
1 6
2 4
2 7
3 4
4 5
4 6
5 6
6 7


*/