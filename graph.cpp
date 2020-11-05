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

class GraphClass {// グラフ入力を受け取る
public:
	GraphClass(int n, bool directed) {// 頂点数nのグラフを初期化する。
		directedFlag = directed;
		N = n; M = 0;
		next.resize(N);
		nodeWeight.resize(N, 1);
	}
	inline void setNodeWeight(int m, ll weight) {// n番のノードの重みをweightに設定
		nodeWeight[m] = weight;
	}
	inline int getEdgeIndex(int x, int y) {// 辺の組からエッジの番号を得る
		assert(next[x].find(y) != next[x].end());
		return next[x][y];
	}
	inline void addEdge(int x, int y, ll weight = 1) {// エッジ追加
		int n = (int)edge.size();
		edge.push_back({ {x,y}, weight }); edgeActiveFlag.push_back(true); M++;
		next[x].insert({ y, n });
		if (directedFlag == false) { next[y].insert({ x, n }); }
	}
	inline void removeEdge(int x, int y) {// エッジ除去
		int k = getEdgeIndex(x, y); assert(k >= 0);
		edgeActiveFlag[k] = false; M--;

		x = edge[k].first.first, y = edge[k].first.second;
		next[x].erase(next[x].find(y));
		if (directedFlag == false) { next[y].erase(next[y].find(x)); }
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
		TreeClass* T = new TreeClass(); T->activate(N);
		UnionFindClass uf; uf.activate(N);

		vector<pair<ll, pair<int, int>>> E;
		for (int i = 0; i < edge.size(); i++) {
			if (edgeActiveFlag[i] == false) { continue; }
			E.push_back({ edge[i].second, {edge[i].first.first, edge[i].first.second} });
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
		while (st.empty() == false) {
			pair<ll, int> p = *st.begin(); st.erase(st.begin());
			int k = p.second;

			if (p.first <= buf[k]) {
				for (auto itr = next[k].begin(); itr != next[k].end(); itr++) {
					if (buf[itr->first] > buf[k] + edge[itr->second].second) {
						buf[itr->first] = buf[k] + edge[itr->second].second;
						st.insert({ buf[itr->first], itr->first });
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
			int p = que.front(); que.pop();
			wait[p] = false;
			for (auto itr = next[p].begin(); itr != next[p].end(); itr++) {
				int x = itr->first; ll w = edge[itr->second].second;
				if (buf[x] <= buf[p] + w) { continue; }
				buf[x] = buf[p] + w;
				if (wait[x] == false) {
					wait[x] = true; count[x]++; que.push(x);
					if (count[x] == N) { return false; }
				}
			}
		}
		return true;
	}

	bool getDistanceFrom(int n, vector<ll> &buf) {// ある点からの最短距離の表を受け取る。
		assert(n >= 0 && n < N);

		bool negativeFlag = false;
		for (int i = 0; i < edge.size(); i++) {
			if (edgeActiveFlag[i] == false) { continue; }
			if (edge[i].second < 0) { negativeFlag = true; break; }
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
			if (edgeActiveFlag[i] == false) { continue; }
			if (edge[i].second < 0) { negativeFlag = true; break; }
		}
		if (negativeFlag == false) {// 全て0以上だったらダイクストラ法を使う
			for (int i = 0; i < N; i++) { dijkstra(i, buf[i]); }
		}
		else {// 負の重みが含まれていたらワーシャルフロイド法を使う
			for (int i = 0; i < N; i++) {
				for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
					buf[i][itr->first] = edge[itr->second].second;
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
			cout << itr->first << "(weight = " << edge[itr->second].second << ")";
			itr++;

			for (; itr != next[i].end(); itr++) {
				cout << ", " << itr->first << "(weight = " << edge[itr->second].second << ")";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool directedFlag;// 有向グラフかどうか
	int N, M;
	vector<ll> nodeWeight;// ノードの重み
	vector<unordered_map<int, int>> next;// 各ノードからの行き先とエッジ番号
	vector<pair<pair<int, int>, ll>> edge;// エッジ(頂点ペアと重み)
	vector<bool> edgeActiveFlag;// エッジが有効かどうか(removeを呼ぶとfalseに)
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