/*
/////////////         UnionFind
//    バラバラの要素を結合してグループにまとめる際に使える構造。
//    グループ番号、要素数の取得が可能だが、グループに属する要素の列挙はO(N)かかる。

class UnionFindClass {
public:
	UnionFindClass() {
		N = 0;
		parent = NULL;
		size = NULL;
	}
	~UnionFindClass() {
		if (parent != NULL) {
			delete[] parent;
		}
		if (size != NULL) {
			delete[] size;
		}
	}

	void activate(int n) {// 要素の数N
		N = n;
		parent = new int[N];
		size = new int[N];
		for (int i = 0; i < N; i++) {
			parent[i] = -1;
			size[i] = 1;
		}
	}

	int getParent(int x) {// グループの親の番号を得る
		if (parent[x] == -1) {
			return x;
		}
		else {
			int y = getParent(parent[x]);
			parent[x] = y;
			return y;
		}
	}
	int getSize(int x) {// 自分が属するグループのサイズを得る
		x = getParent(x);
		return size[x];
	}
	bool connect(int x, int y) {// 二つの要素を結ぶ。２グループ間を繋いだ場合trueを返す
		x = getParent(x);
		y = getParent(y);
		if (x == y) { return false; }
		int xsize = getSize(x), ysize = getSize(y);
		if (xsize < ysize) {
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

	//データ
	int N;// 個数
	int* parent;// 親の番号。自分自身が親なら-1。
	int* size;// 親のみ有効。自分のグループのサイズ。
};





/////////////		グラフを扱うクラス

class graphClass {// グラフ入力を受け取る
public:
	graphClass() {
		N = 0;
		M = 0;
		next = NULL;
		weight = NULL;
		directedFlag = false;
	}

	void activate(int n, bool directed = false) {// 頂点数nのグラフを初期化する。
		directedFlag = directed;
		N = n;
		M = 0;
		edge.clear();
		edgeActiveFlag.clear();
		edgeIndexTable.clear();

		if (next != NULL) { delete[] next; }
		if (weight != NULL) { delete[] weight; }
		next = new map<int, ll>[N];
		weight = new ll[N];
		for (int i = 0; i < N; i++) { weight[i] = 1; }
	}
	void setNodeWeight(int n, ll weight) {// n番のノードの重みをweightに設定
		this->weight[n] = weight;
	}
	int getEdgeIndex(int x, int y) {
		if (edgeIndexTable.find({ x,y }) != edgeIndexTable.end()) {
			return edgeIndexTable.find({ x,y })->second;
		}
		if (edgeIndexTable.find({ y,x }) != edgeIndexTable.end()) {
			return edgeIndexTable.find({ y,x })->second;
		}
		return -1;
	}
	void addEdge(int x, int y, ll weight = 1) {// エッジ追加
		edge.push_back({ {x,y}, weight });
		edgeActiveFlag.push_back(true);

		edgeIndexTable.insert({ { x,y }, M });

		M++;

		next[x].insert({ y, weight });
		if (directedFlag == false) {
			next[y].insert({ x, weight });
		}
	}
	void removeEdge(int x, int y) {
		int k = getEdgeIndex(x, y);
		if (k == -1) { return; }

		x = edge[k].first.first;
		y = edge[k].first.second;

		M--;
		edgeActiveFlag[k] = false;
		edgeIndexTable.erase({ x, y });

		next[x].erase(next[x].find(y));
		if (directedFlag == false) {
			next[y].erase(next[y].find(x));
		}
	}

	bool isTree() {// 木になっているかどうか幅優先探索で調べる
		if (N <= 0 || M != N - 1) { return false; }

		bool* visited = new bool[N];
		for (int i = 0; i < N; i++) {
			visited[i] = (i == 0);
		}

		queue<int> q; q.push(0);

		while (q.size() > 0) {
			int n = q.front(); q.pop();
			visited[n] = true;

			for (auto itr = next[n].begin(); itr != next[n].end(); itr++) {
				if (visited[itr->first] == false) {
					q.push(itr->first);
				}
			}
		}

		for (int i = 0; i < N; i++) {
			if (visited[i] == false) { delete[] visited; return false; }
		}

		delete[] visited;
		return true;
	}

	graphClass* kruskal() {// クラスカル法によって最小全域木を構成する
		graphClass* G = new graphClass(); G->activate(N, directedFlag);
		UnionFindClass uf; uf.activate(N);

		vector<pair<ll, pair<int,int>>> E;
		{
			int i = 0;
			for (auto itr = edge.begin(); itr != edge.end(); itr++, i++) {
				if (edgeActiveFlag[i] == false) { continue; }
				E.push_back({ itr->second, {itr->first.first, itr->first.second} });
			}
		}

		sort(E.begin(), E.end());

		for (auto itr = E.begin(); itr != E.end(); itr++) {
			int x = itr->second.first, y = itr->second.second;
			ll w = itr->first;

			if (uf.getParent(x) != uf.getParent(y)) {
				G->addEdge(x, y, w);
				uf.connect(x, y);
			}
		}

		return G;
	}

	ll* dijkstra(int n) {// ダイクストラ法で始点nからの最短距離を得る
		if (n < 0 || n >= N) { return NULL; }

		ll* buf = new ll[N];
		for (int i = 0; i < N; i++) {
			buf[i] = 1LL << 60;
		}

		// pair<重み, 番号>を並べておく
		set<pair<ll, int>> st;

		buf[n] = 0;
		st.insert({ 0, n });

		while (st.empty() == false) {
			pair<ll, int> p = *st.begin(); st.erase(st.begin());
			int k = p.second;

			if (p.first <= buf[k]) {
				for (auto itr = next[k].begin(); itr != next[k].end(); itr++) {
					if (buf[itr->first] > buf[k] + itr->second) {
						buf[itr->first] = buf[k] + itr->second;
						st.insert({ buf[itr->first], itr->first });
					}
				}
			}
		}

		return buf;
	}

	ll* bellmanFord(int n) {// ベルマンフォード法で始点nからの最短距離を得る
		if (n < 0 || n >= N) { return NULL; }

		ll* buf = new ll[N];
		for (int i = 0; i < N; i++) {
			buf[i] = 1LL << 60;
		}
		buf[n] = 0;
		for (int i = 0; i < N; i++) {
			int j = 0;
			for (auto itr = edge.begin(); itr != edge.end(); itr++, j++) {
				if (edgeActiveFlag[j] == false) { continue; }
				int x = itr->first.first, y = itr->first.second;
				ll w = itr->second;

				if (buf[y] > buf[x] + w) {
					buf[y] = buf[x] + w;
					if (i == N - 1) {
						return NULL;
					}
				}
			}
		}
		return buf;
	}

	ll* getDistanceFrom(int n) {
		if (n < 0 || n >= N) { return NULL; }

		bool negativeFlag = false;
		{
			int i = 0;
			for (auto itr = edge.begin(); itr != edge.end(); itr++, i++) {
				if (edgeActiveFlag[i] == false) { continue; }
				if (itr->second < 0) {
					negativeFlag = true;
					break;
				}
			}
		}

		if (negativeFlag) {// 負の重みがあればベルマンフォード法
			return bellmanFord(n);
		}
		else {// 全て非負ならダイクストラ法
			return dijkstra(n);
		}
	}

	ll** getDistanceTable() {// 最短距離の表を受け取る。対角成分に非ゼロが含まれていたら、重み負の閉路が存在している。

		ll** buf = new ll * [N];
		for (int i = 0; i < N; i++) {
			buf[i] = new ll[N];
			for (int j = 0; j < N; j++) {
				buf[i][j] = 1LL << 60;
			}
			buf[i][i] = 0;
		}

		bool flag = true;
		{
			int i = 0;
			for (auto itr = edge.begin(); itr != edge.end(); itr++, i++) {
				if (itr->second < 0) { flag = false; break; }
			}
		}

		if (flag) {// 全て0以上だったらダイクストラ法を使う
			for (int i = 0; i < N; i++) {
				ll* d = getDistanceFrom(i);
				for (int j = 0; j < N; j++) {
					buf[i][j] = d[j];
				}
				delete[] d;
			}

		}
		else {// 負の重みが含まれていたらワーシャルフロイド法を使う
			for (int i = 0; i < N; i++) {
				for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
					buf[i][itr->first] = itr->second;
				}
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					for (int k = 0; k < N; k++) {
						buf[j][k] = min(buf[j][k], buf[j][i] + buf[i][k]);
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
			cout << "i = " << i << " (weight = " << weight[i] << "), 接続先 = ";
			if (next[i].size() == 0) { cout << "なし" << endl; continue; }
			auto itr = next[i].begin();
			cout << itr->first << "(weight = " << itr->second << ")";
			itr++;

			for (; itr != next[i].end(); itr++) {
				cout << ", " << itr->first << "(weight = " << itr->second << ")";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool directedFlag;// 有向グラフかどうか
	int N, M;
	ll* weight;// ノードの重み
	map<int, ll>* next;// 各ノードにおける辺
	vector<pair<pair<int,int>, ll>> edge;// エッジ
	vector<bool> edgeActiveFlag;// エッジが有効かどうか(removeを呼ぶとfalseに)
	map<pair<int, int>, int> edgeIndexTable;// つなぐ辺のペアから辺の番号を得る
};

void bfs(graphClass& G, int root) {// 幅優先探索
	int N = G.N;
	bool* visited = new bool[N];
	for (int i = 0; i < N; i++) {
		visited[i] = (i == root);
	}

	queue<int> q; q.push(root);

	while (q.size() > 0) {
		int n = q.front(); q.pop();
		visited[n] = true;

		// ここに各ノードで行う処理を書く

		for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {

			// ここに各エッジで行う処理を書く

			if (visited[itr->first] == false) {// まだ訪れていなかったら
				q.push(itr->first);
			}
		}
	}

	delete[] visited;
}
bool* dfs_visited = NULL;
void dfs_process_main(graphClass& G, int n, int depth) {// 深さ優先探索
	// ここに各ノードで行う処理を書く

	for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {

		// ここに各エッジで行う処理を書く

		if (dfs_visited[itr->first] == false) {// まだ訪れていなかったら
			dfs_visited[itr->first] = true;
			dfs_process_main(G, itr->first, depth + 1);
			dfs_visited[itr->first] = false;
		}
	}
}
void dfs(graphClass& G, int root) {// 深さ優先探索
	int N = G.N;
	dfs_visited = new bool[N];
	for (int i = 0; i < N; i++) { dfs_visited[i] = false; }

	dfs_visited[root] = true;
	dfs_process_main(G, root, 0);

	delete[] dfs_visited;
	dfs_visited = NULL;
}

int main() {
	int N, M; cin >> N >> M;// ノード・エッジの数を受け取る

	graphClass G;
	G.activate(N);// ノード数Nで初期化
	// G.activate(N, true);// ノード数Nで初期化

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		G.addEdge(a, b);// エッジの追加
	}

	cout << endl; G.debugCout();// デバッグ出力

	G.removeEdge(1, 3);
	G.removeEdge(5, 0);

	cout << endl; G.debugCout();// デバッグ出力

	graphClass* G1 = G.kruskal();// 最小全域木
	G1->debugCout(); cout << endl;
	delete G1;

	cout << "最短距離の表" << endl;
	ll** buf = G.getDistanceTable();// 最短距離の表を受け取る。対角成分に非ゼロが含まれていたら、重み負の閉路が存在している。

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << buf[i][j] << " ";
		}
		cout << endl;
	}

	delete[] buf;

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