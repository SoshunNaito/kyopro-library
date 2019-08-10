/*
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
	int x = b.x - a.x;
	if (x > 0) { return true; }
	x = b.y - a.y;
	return x > 0;
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

	long* dijkstra(int n) {// �_�C�N�X�g���@�Ŏn�_n����̍ŒZ�����𓾂�
		if (n < 0 || n >= N) { return NULL; }

		long* buf = new long[N];
		for (int i = 0; i < N; i++) {
			buf[i] = 1001001001;
		}

		// �����ɏo��
		// pair<�d��, �ԍ�>����ׂĂ���
		priority_queue<pair<long, int>, vector<pair<long, int>>, greater<pair<long, int>>> q;

		buf[n] = 0;
		q.push(pair<long, int>(0, n));

		while (q.empty() == false) {
			pair<long, int> p = q.top(); q.pop();
			int k = p.second;
			if (p.first <= buf[k]) {
				for (auto itr = next[k].begin(); itr != next[k].end(); itr++) {
					if (buf[itr->y] > buf[k] + (long)itr->weight) {
						buf[itr->y] = buf[k] + (long)itr->weight;
						q.push(pair<long, int>(buf[itr->y], itr->y));
					}
				}
			}
		}

		return buf;
	}

	long* bellmanFord(int n) {// �x���}���t�H�[�h�@�Ŏn�_n����̍ŒZ�����𓾂�
		if (n < 0 || n >= N) { return NULL; }

		long* buf = new long[N];
		for (int i = 0; i < N; i++) {
			buf[i] = 1001001001;
		}
		buf[n] = 0;
		for (int i = 0; i < N; i++) {
			for (auto itr = edge.begin(); itr != edge.end(); itr++) {
				if (buf[itr->y] > buf[itr->x] + (long)(itr->weight)) {
					buf[itr->y] = buf[itr->x] + (long)(itr->weight);
					if (i == N - 1) {
						return NULL;
					}
				}
			}
		}
		return buf;
	}

	long* getDistanceFrom(int n) {
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

	long** getDistanceTable() {// �ŒZ�����̕\���󂯎��B�Ίp�����ɔ�[�����܂܂�Ă�����A�d�ݕ��̕H�����݂��Ă���B

		long** buf = new long* [N];
		for (int i = 0; i < N; i++) {
			buf[i] = new long[N];
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
				long* d = getDistanceFrom(i);
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
void dfs_process_main(graphClass& G, int n) {// �[���D��T��
	dfs_visited[n] = true;

	// �����Ɋe�m�[�h�ōs������������

	for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {

		// �����Ɋe�G�b�W�ōs������������

		if (dfs_visited[itr->y] == false) {// �܂��K��Ă��Ȃ�������
			dfs_process_main(G, itr->y);
		}
	}
}
void dfs(graphClass& G, int root) {// �[���D��T��
	int N = G.N;
	dfs_visited = new bool[N];
	for (int i = 0; i < N; i++) { dfs_visited[i] = false; }
	dfs_process_main(G, 0);

	delete[] dfs_visited;
	dfs_visited = NULL;
}

//////		�g�p��
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

	cout << endl; G.debugCout(); cout << endl;// �f�o�b�O�o��

	cout << "�ŒZ�����̕\" << endl;
	long** buf = G.getDistanceTable();// �ŒZ�����̕\���󂯎��B�Ίp�����ɔ�[�����܂܂�Ă�����A�d�ݕ��̕H�����݂��Ă���B

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