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

class edgeClass {// �ӂ̃N���X
public:
	edgeClass() {
		x = 0, y = 0, weight = 1;
	}
	void swap() {
		int c = x;
		x = y;
		y = c;
	}
	int x, y, weight;
};
bool edgeClass_compare(const edgeClass& a, const edgeClass& b) {// key������ׂ�
	if (a.x != b.x) { return a.x < b.x; }
	return a.y < b.y;
}
bool edgeClass_compare_by_weight(const edgeClass& a, const edgeClass& b) {// weight������ׂ�
	if (a.weight != b.weight) { return a.weight < b.weight; }
	if (a.x != b.x) { return a.x < b.x; }
	return a.y < b.y;
}
class graphClass {// �O���t���͂��󂯎��
public:
	graphClass() {
		N = 0;
		M = 0;
		next = NULL;
		edge.clear();
		weight = NULL;
		directedFlag = false;
	}

	void activate(int n, bool directed = false) {// ���_��n�̃O���t������������B
		directedFlag = directed;
		N = n;
		M = 0;
		edge.clear();
		if (next != NULL) { delete[] next; }
		if (weight != NULL) { delete[] weight; }
		next = new vector<edgeClass>[N];
		weight = new int[N];
		for (int i = 0; i < N; i++) { weight[i] = 1; }
	}
	void setNodeWeight(int n, int weight) {// n�Ԃ̃m�[�h�̏d�݂�weight�ɐݒ�
		this->weight[n] = weight;
	}
	void addEdge(int x, int y, int weight = 1) {// �G�b�W�ǉ�
		edgeClass e;
		e.x = x;
		e.y = y;
		e.weight = weight;

		if (e.x < 0 || e.x >= N) { return; }

		edge.push_back(e); M++;
		next[e.x].push_back(e);

		if (directedFlag == false) {
			e.swap();
			next[e.x].push_back(e);
		}

	}
	void sortEdge() {// �e�m�[�h�ɂ��āA�ڑ���̔ԍ��������\�[�g
		for (int i = 0; i < N; i++) {
			if (next[i].size() > 1) {
				sort(next[i].begin(), next[i].end(), edgeClass_compare);
			}
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
				if (visited[itr->y] == false) {
					q.push(itr->y);
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

		vector<edgeClass> E;
		for (auto itr = edge.begin(); itr != edge.end(); itr++) {
			E.push_back(*itr);
		}
		sort(E.begin(), E.end(), edgeClass_compare_by_weight);

		for (auto itr = E.begin(); itr != E.end(); itr++) {
			if (uf.getParent(itr->x) != uf.getParent(itr->y)) {
				G->addEdge(itr->x, itr->y, itr->weight);
				uf.connect(itr->x, itr->y);
			}
		}

		return G;
	}

	ll* dijkstra(int n) {// �_�C�N�X�g���@�Ŏn�_n����̍ŒZ�����𓾂�
		if (n < 0 || n >= N) { return NULL; }

		ll* buf = new ll[N];
		for (int i = 0; i < N; i++) {
			buf[i] = 1001001001;
		}

		// �����ɏo��
		// pair<�d��, �ԍ�>����ׂĂ���
		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;

		buf[n] = 0;
		q.push(pair<ll, int>(0, n));

		while (q.empty() == false) {
			pair<ll, int> p = q.top(); q.pop();
			int k = p.second;
			if (p.first <= buf[k]) {
				for (auto itr = next[k].begin(); itr != next[k].end(); itr++) {
					if (buf[itr->y] > buf[k] + (ll)itr->weight) {
						buf[itr->y] = buf[k] + (ll)itr->weight;
						q.push(pair<ll, int>(buf[itr->y], itr->y));
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
			buf[i] = 1001001001;
		}
		buf[n] = 0;
		for (int i = 0; i < N; i++) {
			for (auto itr = edge.begin(); itr != edge.end(); itr++) {
				if (buf[itr->y] > buf[itr->x] + (ll)(itr->weight)) {
					buf[itr->y] = buf[itr->x] + (ll)(itr->weight);
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
		for (auto itr = edge.begin(); itr != edge.end(); itr++) {
			if (itr->weight < 0) {
				negativeFlag = true;
				break;
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

		ll** buf = new ll* [N];
		for (int i = 0; i < N; i++) {
			buf[i] = new ll[N];
			for (int j = 0; j < N; j++) {
				buf[i][j] = 1000000000;
			}
			buf[i][i] = 0;
		}

		bool flag = true;
		for (auto itr = edge.begin(); itr != edge.end(); itr++) {
			if (itr->weight < 0) { flag = false; break; }
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
					buf[i][itr->y] = itr->weight;
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
			cout << itr->y << "(weight = " << itr->weight << ")";
			itr++;

			for (; itr != next[i].end(); itr++) {
				cout << ", " << itr->y << "(weight = " << itr->weight << ")";
			}
			cout << endl;
		}
		cout << endl;
	}

	bool directedFlag;// �L���O���t���ǂ���
	int N, M;
	int* weight;// �m�[�h�̏d��
	vector<edgeClass>* next;// �e�m�[�h�ɂ������
	vector<edgeClass> edge;// �G�b�W
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

			if (visited[itr->y] == false) {// �܂��K��Ă��Ȃ�������
				q.push(itr->y);
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

		if (dfs_visited[itr->y] == false) {// �܂��K��Ă��Ȃ�������
			dfs_visited[itr->y] = true;
			dfs_process_main(G, itr->y, depth + 1);
			dfs_visited[itr->y] = false;
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

	graphClass G; G.activate(N);// �m�[�h��N�ŏ�����
	// G.activate(N, true); �ŗL���O���t�ɁB

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		a--; b--;
		G.addEdge(a, b);// �G�b�W�̒ǉ�
	}
	G.sortEdge();// �e�m�[�h�ɂ�����G�b�W�̏��Ԃ𐮗�����

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
7 7
1 3
2 7
3 4
4 5
4 6
5 6
6 7


*/