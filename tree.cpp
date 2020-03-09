/*

// #define USE_LCA
class TreeClass {// 木の入力を受け取る
public:
	TreeClass() {
		N = 0, root = 0;
		next = NULL;
		weight = NULL;
#ifdef USE_LCA
		parent = NULL;
#endif
	}
	TreeClass(int _N, int _root = 0) {
		next = NULL;
		weight = NULL;
#ifdef USE_LCA
		parent = NULL;
#endif
		activate(_N, _root);
	}

	~TreeClass() {
		if (weight != NULL) { delete[] weight; }
		if (next != NULL) { delete[] next; }
#ifdef USE_LCA
		if (parent != NULL) { delete[] parent; }
#endif
	}

	void activate(int n, int _root = 0) {// 頂点数nのグラフを初期化する。
		N = n;
		root = _root;

		if (weight != NULL) { delete[] weight; }
		weight = new ll[N];
		for (int i = 0; i < N; i++) { weight[i] = 1; }

		if (next != NULL) { delete[] next; }
		next = new unordered_map<int, int>[N];
		edge.clear();

		depth.clear();
		depth.resize(N);
		distanceTable.clear();
		distanceTable.resize(N);
#ifdef USE_LCA
		if (parent != NULL) { delete[] parent; }
		parent = new vector<int>[N];
		for (int i = 0; i < N; i++) { parent[i].clear(); }
#endif
	}
	inline void setNodeWeight(int n, ll weight) {// n番のノードの重みをweightに設定
		this->weight[n] = weight;
	}

	inline int getEdgeIndex(int x, int y) {// 辺の組からエッジの番号を得る
		if (next[x].find(y) != next[x].end()) {
			return next[x][y];
		}
		return -1;
	}
	inline void addEdge(int x, int y, ll _weight = 1) {// エッジ追加
		int M = (int)edge.size();
		edge.push_back({ {x,y}, _weight });

		next[x].insert({ y, M });
		next[y].insert({ x, M });

		if (edge.size() == N - 1) {
			processDepth();
#ifdef USE_LCA
			processDoubling();
#endif
		}
	}
#ifdef USE_LCA
	inline int LCA(int a, int b) {
		int d = min(depth[a], depth[b]);

		if (depth[a] > d) {
			int k = depth[a] - d;
			for (int i = 0; k > 0; i++) {
				if ((1 << i) & k) {
					k -= (1 << i);
					a = parent[a][i];
				}
			}
		}
		if (depth[b] > d) {
			int k = depth[b] - d;
			for (int i = 0; k > 0; i++) {
				if ((1 << i) & k) {
					k -= (1 << i);
					b = parent[b][i];
				}
			}
		}
		if (a == b) { return a; }

		for (int k = parent[a].size() - 1; k >= 0; k--) {
			if (k < parent[a].size() && k < parent[b].size() && (parent[a][k] != parent[b][k])) {
				a = parent[a][k];
				b = parent[b][k];
			}
		}
		return parent[a][0];
	}
#endif

	inline void changeRoot(int r, bool ProcessDoublingFlag = true) {
		assert(r >= 0 && r < N);
		root = r;
		processDepth();
#ifdef USE_LCA
		if (ProcessDoublingFlag) {
			processDoubling();
		}
#endif
	}

	inline pair<int, vector<int>> getDiameter_and_Center() {
		int r0 = root;
		int d1 = -1, k1 = -1;
		for (int i = 0; i < N; i++) {
			if (chmax(d1, depth[i])) {
				k1 = i;
			}
		}
		changeRoot(k1, false);

		int d2 = -1, k2 = -1;
		for (int i = 0; i < N; i++) {
			if (chmax(d2, depth[i])) {
				k2 = i;
			}
		}
		int i = k2;
		if (d2 % 2 == 0) {
			while (depth[i] > d2 / 2) {
				for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
					int j = itr->first;

					if (depth[i] > depth[j]) {
						if (depth[j] == d2 / 2) {
							changeRoot(r0, false);
							return { d2, { j } };
						}
						i = j;
						break;
					}
				}
			}
		}
		else {
			while (1) {
				for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
					int j = itr->first;

					if (depth[i] > depth[j]) {
						if (depth[j] == d2 / 2) {
							changeRoot(r0, false);
							return { d2, { i, j } };
						}
						i = j;
						break;
					}
				}
			}
		}
		return { d2, { root } };
	}

private:
	inline void processDepth() {// bfsで根からの深さと距離を得る
		for (int i = 0; i < N; i++) {
			depth[i] = -1;
		}

		queue<pair<int, pair<int, ll>>> q; q.push({ root, {0, 0} });

		while (q.size() > 0) {
			int n = q.front().first;
			int d = q.front().second.first;
			ll w = q.front().second.second;
			q.pop();

			depth[n] = d;
			weight[n] = w;

			for (auto itr = next[n].begin(); itr != next[n].end(); itr++) {
				int m = itr->first;

				if (depth[m] == -1) {
					q.push({ m, {d + 1, w + edge[itr->second].second} });
				}
			}
		}
	}
#ifdef USE_LCA
	inline void processDoubling() {// ダブリング
		for (int i = 0; i < N; i++) {
			parent[i].clear();
		}
		for (int i = 0; i < N - 1; i++) {
			int a = edge[i].first.first;
			int b = edge[i].first.second;

			if (depth[a] < depth[b]) {
				parent[b].push_back(a);
			}
			else {
				parent[a].push_back(b);
			}
		}
		queue<int> q;
		for (int i = 0; i < N; i++) {
			if (i == root) { continue; }
			q.push(i);
		}
		while (q.size() > 0) {
			int n = q.front();
			q.pop();

			int k = parent[n].size() - 1;
			if (depth[n] >= (1 << (k + 1))) {
				parent[n].push_back(parent[parent[n][k]][k]);
				q.push(n);
			}
		}
	}
#endif

public:
	int N, root;
	ll* weight;// ノードの重み
	unordered_map<int, int>* next;// 各ノードからの行き先とエッジ番号
	vector<pair<pair<int, int>, ll>> edge;// エッジ(頂点ペアと重み)

	vector<int> depth;// 根から見た深さ
	vector<ll> distanceTable;// 根からの距離
#ifdef USE_LCA
	vector<int>* parent;//1番目、2番目、4番目、8番目...の親
#endif
};

class TreeHash {// 根付き木のハッシュを計算する
public:
	TreeHash() {
		MT.seed((unsigned int)time(NULL));
	}
	TreeHash(unsigned int seed) {
		MT.seed(seed);
	}

private:
	inline void treeHash_process_main(TreeClass& T, int n, int depth, ll mod) {
		ll temp = 1;
		h[n] = rnd[depth] % mod;
		bool flag = false;
		for (auto itr = T.next[n].begin(); itr != T.next[n].end(); itr++) {
			int m = itr->first;

			if (T.depth[m] > T.depth[n]) {// まだ訪れていなかったら
				treeHash_process_main(T, m, depth + 1, mod);
				flag = true;
				temp *= h[m];
				temp %= mod;
			}
		}
		if (flag) {
			h[n] += temp;
			if (h[n] >= mod) { h[n] -= mod; }
		}
	}

public:
	inline pair<ll, ll> treeHash(TreeClass& T) {// 根付き木のハッシュを計算する
		int N = T.N;
		if (h.size() < N) {
			int n = h.size();
			h.resize(N);
			hash.resize(N);
			rnd.resize(N);

			uniform_int_distribution<ll> dis(0, 1LL << 60);
			for (int i = n; i < N; i++) {
				rnd[i] = dis(MT);
			}
		}

		treeHash_process_main(T, T.root, 0, 1000000007);
		for (int i = 0; i < N; i++) {
			hash[i].first = h[i] << 30;
		}
		treeHash_process_main(T, T.root, 0, 1000000009);
		for (int i = 0; i < N; i++) {
			hash[i].first += h[i];
		}
		treeHash_process_main(T, T.root, 0, 998244353);
		for (int i = 0; i < N; i++) {
			hash[i].second = h[i] << 30;
		}
		treeHash_process_main(T, T.root, 0, 1000000021);
		for (int i = 0; i < N; i++) {
			hash[i].second += h[i];
		}
		return hash[T.root];
	}

	mt19937_64 MT;
	vector<ll> h, rnd;
	vector<pair<ll, ll>> hash;
};

*/