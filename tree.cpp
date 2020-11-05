/*

///////////////// �e��ݒ� /////////////////

#define USE_SUBTREE_SIZE
#define USE_LCA

#define USE_TREE
class TreeClass {// �؂̓��͂��󂯎��
public:
	TreeClass(int n, int _root = 0) {// ���_��n�̃O���t������������B
		N = n; root = _root;
		nodeWeight.resize(N, 1); next.resize(N);
#ifdef USE_SUBTREE_SIZE
		subtree_size.resize(N);
#endif
#ifdef USE_LCA
		parent.resize(N);
#endif
	}
	inline void setNodeWeight(int n, ll weight) {// n�Ԃ̃m�[�h�̏d�݂�weight�ɐݒ�
		nodeWeight[n] = weight;
	}
	inline int getEdgeIndex(int x, int y) {// �ӂ̑g����G�b�W�̔ԍ��𓾂�
		assert(next[x].find(y) != next[x].end());
		return next[x][y];
	}
	inline void addEdge(int x, int y, ll weight = 1) {// �G�b�W�ǉ�
		int n = (int)edge.size();
		edge.push_back({ {x,y}, weight });
		next[x].insert({ y, n }); next[y].insert({ x, n });
		if (n == N - 2) {
			initProcess();
#ifdef USE_SUBTREE_SIZE
			dfs(&TreeClass::dfs_processSubtreeSize);
#endif
#ifdef USE_LCA
			bfs(&TreeClass::bfs_processDoubling);
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
					k -= (1 << i); a = parent[a][i];
				}
			}
		}
		if (depth[b] > d) {
			int k = depth[b] - d;
			for (int i = 0; k > 0; i++) {
				if ((1 << i) & k) {
					k -= (1 << i); b = parent[b][i];
				}
			}
		}
		if (a == b) { return a; }

		for (int k = parent[a].size() - 1; k >= 0; k--) {
			if (k < parent[a].size() && k < parent[b].size() && (parent[a][k] != parent[b][k])) {
				a = parent[a][k]; b = parent[b][k];
			}
		}
		return parent[a][0];
	}
#endif
	inline void changeRoot(int r, bool ProcessDoublingFlag = true) {
		assert(r >= 0 && r < N);
		root = r; initProcess();
#ifdef USE_SUBTREE_SIZE
		dfs(&TreeClass::dfs_processSubtreeSize);
#endif
#ifdef USE_LCA
		if (ProcessDoublingFlag)  bfs(&TreeClass::bfs_processDoubling);
#endif
	}
	inline pair<int, vector<int>> getDiameter_and_Center() {
		int r0 = root;
		int d1 = -1, k1 = -1;
		for (int i = 0; i < N; i++) {
			if (chmax(d1, depth[i])) { k1 = i; }
		}
		changeRoot(k1, false);

		int d2 = -1, k2 = -1;
		for (int i = 0; i < N; i++) {
			if (chmax(d2, depth[i])) { k2 = i; }
		}
		int i = k2;
		while (1) {
			int j = back[i].first;
			if (depth[j] == d2 / 2) {
				changeRoot(r0, false);
				if (d2 % 2 == 0) { return { d2, { j } }; }
				else { return { d2, { i, j } }; }
			}
			i = j;
		}
	}
private:
	inline void initProcess() {// bfs�̏��Ԃ��擾����Ɠ����ɁA������̐[���𓾂�B
		depth.clear(); depth.resize(N, -1);
		back.clear(); back.resize(N, { -1,-1 });

		queue<pair<int, int>> q; q.push({ root, 0 });
		bfs_order.clear();
		while (q.size() > 0) {
			int n = q.front().first, d = q.front().second; q.pop();
			bfs_order.push_back(n); depth[n] = d;

			auto _erase = next[n].end();// ���Ɍ�������
			for (auto itr = next[n].begin(); itr != next[n].end(); itr++) {
				int m = itr->first;
				if (depth[m] == -1) { q.push({ m, d + 1 }); }
				else {
					_erase = itr;
					back[n] = { itr->first, itr->second };
				}
			}
			if (_erase != next[n].end()) { next[n].erase(_erase); }
		}
	}
	inline void dfs(void (TreeClass::* dfs_process)(int n)) {
		for (int i = N - 1; i >= 0; i--) { (this->*dfs_process)(bfs_order[i]); }
	}
	inline void bfs(void (TreeClass::* bfs_process)(int n)) {
		for (int i = 0; i < N; i++) { (this->*bfs_process)(bfs_order[i]); }
	}
#ifdef USE_SUBTREE_SIZE
	void dfs_processSubtreeSize(int n) {// �����؂̃T�C�Y�𓾂�
		subtree_size[n] = 1;
		for (auto itr = next[n].begin(); itr != next[n].end(); itr++) {
			subtree_size[n] += subtree_size[itr->first];
		}
	}
#endif
#ifdef USE_LCA
	void bfs_processDoubling(int n) {// �_�u�����O
		parent[n].clear();
		if (n == root) { return; }

		parent[n].push_back(back[n].first);
		for (int k = 0; depth[n] >= (1 << (k + 1)); k++) {
			parent[n].push_back(parent[parent[n][k]][k]);
		}
	}
#endif

public:
	void debugCout() {// �f�o�b�O�o�͗p
		cout << endl;
		cout << "�m�[�h�̌� = " << N << "��" << endl;
		cout << "�� = " << root << endl;
		cout << endl;

		for (int i = 0; i < N; i++) {
			cout << "i = " << i << " (nodeWeight = " << nodeWeight[i] << "), �e = " <<
				((i == root) ? "�Ȃ�" : to_string(back[i].first)) << ", �ڑ��� = ";
			if (next[i].size() == 0) { cout << "�Ȃ�" << endl; continue; }

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

	int N, root;
	vector<ll> nodeWeight;// �m�[�h�̏d��
	vector<pair<pair<int, int>, ll>> edge;// �G�b�W(���_�y�A�Əd��)
	vector<pair<int, int>> back;// ���ɋ߂��m�[�h�ƁA�G�b�W�ԍ�
	vector<unordered_map<int, int>> next;// �e�m�[�h����̍s����ƃG�b�W�ԍ�

	vector<int> depth;// �����猩���[��
	vector<int> bfs_order;// bfs�̍ۂɖK��鏇��(dfs�͋t��)
#ifdef USE_SUBTREE_SIZE
	vector<int> subtree_size;// �����؂̃T�C�Y
#endif
#ifdef USE_LCA
	vector<vector<int>> parent;//1�ԖځA2�ԖځA4�ԖځA8�Ԗ�...�̐e
#endif
};

inline void dfs(TreeClass &T, void (*dfs_process)(TreeClass& T, int n)) {
	for (int i = T.N - 1; i >= 0; i--) {
		dfs_process(T, T.bfs_order[i]);
	}
}
inline void bfs(TreeClass& T, void (*bfs_process)(TreeClass& T, int n)) {
	for (int i = 0; i < T.N; i++) {
		bfs_process(T, T.bfs_order[i]);
	}
}

class TreeDP_data {
public:
	TreeDP_data() {

	}
	void init(TreeClass& T, int _n) {
		n = _n;
	}
	inline void forward_ans_tie(TreeClass& T, TreeDP_data& Other) {
		int m = Other.n;

		////////////�ȉ��ɏ���������////////////
	}
	inline void backward_ans_tie(TreeClass& T, TreeDP_data& Other) {
		int m = Other.n;

		////////////�ȉ��ɏ���������////////////
	}

	int n;
	ll forward_ans, ans;
};
vector<TreeDP_data> DP_data;

void TreeDP_forwardProcess(TreeClass &T, int n) {
	for (auto itr = T.next[n].begin(); itr != T.next[n].end(); itr++) {
		int m = itr->first;
		DP_data[n].forward_ans_tie(T, DP_data[m]);
	}
}
void TreeDP_backwardProcess(TreeClass& T, int n) {
	if (n == T.root) { DP_data[n].ans = DP_data[n].forward_ans; return; }
	int m = T.back[n].first;
	DP_data[n].backward_ans_tie(T, DP_data[m]);
}
inline void TreeDP(TreeClass &T) {
	DP_data.clear();
	DP_data.resize(T.N);
	for (int i = 0; i < T.N; i++) {
		DP_data[i].init(T, i);
	}
	dfs(T, TreeDP_forwardProcess);
	bfs(T, TreeDP_backwardProcess);
}

class TreeHash {// ���t���؂̃n�b�V�����v�Z����
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

			if (T.depth[m] > T.depth[n]) {// �܂��K��Ă��Ȃ�������
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
	inline pair<ll, ll> treeHash(TreeClass& T) {// ���t���؂̃n�b�V�����v�Z����
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