/*
////////////////	UnionFind
#define UnionFind dsu


/////////////         UnionFind
//    �o���o���̗v�f���������ăO���[�v�ɂ܂Ƃ߂�ۂɎg����\���B
//    �O���[�v�ԍ��A�v�f���̎擾���\�����A�O���[�v�ɑ�����v�f�̗񋓂�O(N)������B

#define USE_UNIONFIND
class UnionFindClass {
public:
	UnionFindClass() { N = 0; }
	UnionFindClass(int n) { activate(n); }

	void activate(int n) {// �v�f�̐�N
		N = n;
		parent.clear(); parent.resize(N, -1);
		size.clear(); size.resize(N, 1);
	}
	inline int getParent(int x) {// �O���[�v�̐e�̔ԍ��𓾂�
		if (parent[x] == -1) { return x; }
		int y = getParent(parent[x]);
		parent[x] = y;
		return y;
	}
	inline int getSize(int x) {// ������������O���[�v�̃T�C�Y�𓾂�
		return size[getParent(x)];
	}
	inline bool connect(int x, int y) {// ��̗v�f�����ԁB�Q�O���[�v�Ԃ��q�����ꍇtrue��Ԃ�
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

	int N;// ��
	vector<int> parent;// �e�̔ԍ��B�������g���e�Ȃ�-1�B
	vector<int> size;// �e�̂ݗL���B�����̃O���[�v�̃T�C�Y�B
};



/////////////		�O���t�������N���X
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
class GraphClass {// �O���t���͂��󂯎��
public:
	GraphClass(int n, bool directed) {// ���_��n�̃O���t������������
		directedFlag = directed;
		N = n; M = 0;
		next.resize(N);
	}
	inline void addEdge(EdgeType e) {// �G�b�W�ǉ�
		int n = (int)edge.size();
		edge.push_back(e); M++;
		next[e.from].push_back({ e.to, n });
		if (directedFlag == false) { next[e.to].push_back({ e.from, n }); }
	}
	inline void addEdge(int x, int y, ll weight = 1) {// �G�b�W�ǉ�
		addEdge({ x,y,weight });
	}
	bool isTree() {// �؂ɂȂ��Ă��邩�ǂ������D��T���Œ��ׂ�
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
	TreeClass* kruskal() {// �N���X�J���@�ɂ���čŏ��S��؂��\������
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
	void dijkstra(int n, vector<ll>& buf) {// �_�C�N�X�g���@�Ŏn�_n����̍ŒZ�����𓾂�
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

	bool bellmanFord(int n, vector<ll>& buf) {// �x���}���t�H�[�h�@�Ŏn�_n����̍ŒZ�����𓾂�
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

	bool getDistanceFrom(int n, vector<ll>& buf) {// ����_����̍ŒZ�����̕\���󂯎��B
		assert(n >= 0 && n < N);

		bool negativeFlag = false;
		for (int i = 0; i < edge.size(); i++) {
			if (edge[i].weight < 0) { negativeFlag = true; break; }
		}
		if (negativeFlag) {// ���̏d�݂�����΃x���}���t�H�[�h�@
			return bellmanFord(n, buf);
		}
		else {// �S�Ĕ񕉂Ȃ�_�C�N�X�g���@
			dijkstra(n, buf); return true;
		}
	}

	vector<vector<ll>> getDistanceTable() {// �ŒZ�����̕\���󂯎��B�Ίp�����ɔ�[�����܂܂�Ă�����A�d�ݕ��̕H�����݂��Ă���B
		vector<vector<ll>> buf(N);
		for (int i = 0; i < N; i++) {
			buf[i].resize(N, INF);
			buf[i][i] = 0;
		}

		bool negativeFlag = false;
		for (int i = 0; i < edge.size(); i++) {
			if (edge[i].weight < 0) { negativeFlag = true; break; }
		}
		if (negativeFlag == false) {// �S��0�ȏゾ������_�C�N�X�g���@���g��
			for (int i = 0; i < N; i++) { dijkstra(i, buf[i]); }
		}
		else {// ���̏d�݂��܂܂�Ă����烏�[�V�����t���C�h�@���g��
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

	void debugCout() {// �f�o�b�O�o�͗p
		cout << endl;
		cout << "�m�[�h�̌� = " << N << "��" << endl;
		cout << "�G�b�W�̖{�� = " << M << "�{" << endl;
		cout << endl;

		for (int i = 0; i < N; i++) {
			cout << "i = " << i << " (nodeWeight = " << nodeWeight[i] << "), �ڑ��� = ";
			if (next[i].size() == 0) { cout << "�Ȃ�" << endl; continue; }
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

	bool directedFlag;// �L���O���t���ǂ���
	int N, M;
	vector<ll> nodeWeight;// �m�[�h�̏d��
	vector<vector<pair<int, int>>> next;// �e�m�[�h����̍s����ƃG�b�W�ԍ�
	vector<EdgeType> edge;// �G�b�W(���_�y�A�Əd��)
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

	G.debugCout();// �f�o�b�O�o��

	G.removeEdge(1, 3);
	G.removeEdge(3, 5);

	G.debugCout();// �f�o�b�O�o��

	cout << "�ŒZ�����̕\" << endl;
	auto table = G.getDistanceTable();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
//////		���ؗp���̓f�[�^
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