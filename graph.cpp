/*
/////////////         UnionFind
//    �o���o���̗v�f���������ăO���[�v�ɂ܂Ƃ߂�ۂɎg����\���B
//    �O���[�v�ԍ��A�v�f���̎擾���\�����A�O���[�v�ɑ�����v�f�̗񋓂�O(N)������B

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

	void activate(int n) {// �v�f�̐�N
		N = n;
		parent = new int[N];
		size = new int[N];
		for (int i = 0; i < N; i++) {
			parent[i] = -1;
			size[i] = 1;
		}
	}

	int getParent(int x) {// �O���[�v�̐e�̔ԍ��𓾂�
		if (parent[x] == -1) {
			return x;
		}
		else {
			int y = getParent(parent[x]);
			parent[x] = y;
			return y;
		}
	}
	int getSize(int x) {// ������������O���[�v�̃T�C�Y�𓾂�
		x = getParent(x);
		return size[x];
	}
	bool connect(int x, int y) {// ��̗v�f�����ԁB�Q�O���[�v�Ԃ��q�����ꍇtrue��Ԃ�
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

	//�f�[�^
	int N;// ��
	int* parent;// �e�̔ԍ��B�������g���e�Ȃ�-1�B
	int* size;// �e�̂ݗL���B�����̃O���[�v�̃T�C�Y�B
};





/////////////		�O���t�������N���X

class graphClass {// �O���t���͂��󂯎��
public:
	graphClass() {
		N = 0;
		M = 0;
		next = NULL;
		weight = NULL;
		directedFlag = false;
	}

	void activate(int n, bool directed = false) {// ���_��n�̃O���t������������B
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
	void setNodeWeight(int n, ll weight) {// n�Ԃ̃m�[�h�̏d�݂�weight�ɐݒ�
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
	void addEdge(int x, int y, ll weight = 1) {// �G�b�W�ǉ�
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

	bool isTree() {// �؂ɂȂ��Ă��邩�ǂ������D��T���Œ��ׂ�
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

	graphClass* kruskal() {// �N���X�J���@�ɂ���čŏ��S��؂��\������
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

	ll* dijkstra(int n) {// �_�C�N�X�g���@�Ŏn�_n����̍ŒZ�����𓾂�
		if (n < 0 || n >= N) { return NULL; }

		ll* buf = new ll[N];
		for (int i = 0; i < N; i++) {
			buf[i] = 1LL << 60;
		}

		// pair<�d��, �ԍ�>����ׂĂ���
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

	ll* bellmanFord(int n) {// �x���}���t�H�[�h�@�Ŏn�_n����̍ŒZ�����𓾂�
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

		if (negativeFlag) {// ���̏d�݂�����΃x���}���t�H�[�h�@
			return bellmanFord(n);
		}
		else {// �S�Ĕ񕉂Ȃ�_�C�N�X�g���@
			return dijkstra(n);
		}
	}

	ll** getDistanceTable() {// �ŒZ�����̕\���󂯎��B�Ίp�����ɔ�[�����܂܂�Ă�����A�d�ݕ��̕H�����݂��Ă���B

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

		if (flag) {// �S��0�ȏゾ������_�C�N�X�g���@���g��
			for (int i = 0; i < N; i++) {
				ll* d = getDistanceFrom(i);
				for (int j = 0; j < N; j++) {
					buf[i][j] = d[j];
				}
				delete[] d;
			}

		}
		else {// ���̏d�݂��܂܂�Ă����烏�[�V�����t���C�h�@���g��
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

	void debugCout() {// �f�o�b�O�o�͗p
		cout << endl;
		cout << "�m�[�h�̌� = " << N << "��" << endl;
		cout << "�G�b�W�̖{�� = " << M << "�{" << endl;
		cout << endl;

		for (int i = 0; i < N; i++) {
			cout << "i = " << i << " (weight = " << weight[i] << "), �ڑ��� = ";
			if (next[i].size() == 0) { cout << "�Ȃ�" << endl; continue; }
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

	bool directedFlag;// �L���O���t���ǂ���
	int N, M;
	ll* weight;// �m�[�h�̏d��
	map<int, ll>* next;// �e�m�[�h�ɂ������
	vector<pair<pair<int,int>, ll>> edge;// �G�b�W
	vector<bool> edgeActiveFlag;// �G�b�W���L�����ǂ���(remove���ĂԂ�false��)
	map<pair<int, int>, int> edgeIndexTable;// �Ȃ��ӂ̃y�A����ӂ̔ԍ��𓾂�
};

void bfs(graphClass& G, int root) {// ���D��T��
	int N = G.N;
	bool* visited = new bool[N];
	for (int i = 0; i < N; i++) {
		visited[i] = (i == root);
	}

	queue<int> q; q.push(root);

	while (q.size() > 0) {
		int n = q.front(); q.pop();
		visited[n] = true;

		// �����Ɋe�m�[�h�ōs������������

		for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {

			// �����Ɋe�G�b�W�ōs������������

			if (visited[itr->first] == false) {// �܂��K��Ă��Ȃ�������
				q.push(itr->first);
			}
		}
	}

	delete[] visited;
}
bool* dfs_visited = NULL;
void dfs_process_main(graphClass& G, int n, int depth) {// �[���D��T��
	// �����Ɋe�m�[�h�ōs������������

	for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {

		// �����Ɋe�G�b�W�ōs������������

		if (dfs_visited[itr->first] == false) {// �܂��K��Ă��Ȃ�������
			dfs_visited[itr->first] = true;
			dfs_process_main(G, itr->first, depth + 1);
			dfs_visited[itr->first] = false;
		}
	}
}
void dfs(graphClass& G, int root) {// �[���D��T��
	int N = G.N;
	dfs_visited = new bool[N];
	for (int i = 0; i < N; i++) { dfs_visited[i] = false; }

	dfs_visited[root] = true;
	dfs_process_main(G, root, 0);

	delete[] dfs_visited;
	dfs_visited = NULL;
}

int main() {
	int N, M; cin >> N >> M;// �m�[�h�E�G�b�W�̐����󂯎��

	graphClass G;
	G.activate(N);// �m�[�h��N�ŏ�����
	// G.activate(N, true);// �m�[�h��N�ŏ�����

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		G.addEdge(a, b);// �G�b�W�̒ǉ�
	}

	cout << endl; G.debugCout();// �f�o�b�O�o��

	G.removeEdge(1, 3);
	G.removeEdge(5, 0);

	cout << endl; G.debugCout();// �f�o�b�O�o��

	graphClass* G1 = G.kruskal();// �ŏ��S���
	G1->debugCout(); cout << endl;
	delete G1;

	cout << "�ŒZ�����̕\" << endl;
	ll** buf = G.getDistanceTable();// �ŒZ�����̕\���󂯎��B�Ίp�����ɔ�[�����܂܂�Ă�����A�d�ݕ��̕H�����݂��Ă���B

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << buf[i][j] << " ";
		}
		cout << endl;
	}

	delete[] buf;

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