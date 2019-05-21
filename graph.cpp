/*
/////////////         �O���t�������N���X

class edgeClass {// �ӂ̃N���X
public:
	edgeClass() {
		x = 0, y = 0, weigh = 1;
	}
	void swap() {
		int c = x;
		x = y;
		y = c;
	}
	void input(bool weighedFlag) {
		if (weighedFlag) {
			cin >> x >> y >> weigh;
		}
		else {
			cin >> x >> y;
		}
	}
	int x, y, weigh;
};
bool edgeClass_compare(const edgeClass& a, const edgeClass& b) {//key������ׂ�
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
		edge = NULL;
		weigh = NULL;
		nodeWeighedFlag = false;
		edgeWeighedFlag = false;
		directedFlag = false;
	}
	void activateMain(bool nodeWeigh, bool edgeWeigh, bool subFlag, bool directed) {// subFlag==true�Ȃ���͂���1�������Bdireted==true�Ȃ�L���O���t
		if (next != NULL) { delete[] next; }
		if (edge != NULL) { delete[] edge; }
		if (weigh != NULL) { delete[] weigh; }

		next = new vector<edgeClass>[N];
		weigh = new int[N];
		edge = new edgeClass[M];

		nodeWeighedFlag = nodeWeigh;
		edgeWeighedFlag = edgeWeigh;
		directedFlag = directed;

		for (int i = 0; i < N; i++) {
			weigh[i] = 1;
		}
		if (nodeWeigh) {
			for (int i = 0; i < N; i++) {
				cin >> weigh[i];
			}
		}

		for (int i = 0; i < M; i++) {// ���͂��󂯎���Ă���
			edge[i].input(edgeWeigh);
			if (subFlag) {
				edge[i].x--;
				edge[i].y--;
			}

			next[edge[i].x].push_back(edge[i]);
			if (directedFlag == false) {
				edge[i].swap();
				next[edge[i].x].push_back(edge[i]);
				edge[i].swap();
			}
		}
		for (int i = 0; i < N; i++) {
			if (next[i].size() > 1) {
				sort(next[i].begin(), next[i].end(), edgeClass_compare);// vector�̃\�[�g���Ă���ȊȒP�Ȃ́I�H
			}
		}
	}
	void activate(const char* nodeWeigh, const char* edgeWeigh, const char* subFlag, const char* directed) {// subFlag�͓��͂���1���������ǂ���
		cin >> N >> M;
		activateMain(strcmp(nodeWeigh, "weighed") == 0, strcmp(edgeWeigh, "weighed") == 0, strcmp(subFlag, "subtract") == 0, strcmp(directed, "directed") == 0);
	}

	void debugCout() {// �f�o�b�O�o�͗p
		cout << endl;
		cout << "�m�[�h�̌� = " << N << "��" << endl;
		cout << "�G�b�W�̖{�� = " << M << "�{" << endl;
		cout << "�d��" << (nodeWeighedFlag ? "��" : "�Ȃ�") << "�m�[�h " << "�d��" << (edgeWeighedFlag ? "��" : "�Ȃ�") << "�G�b�W " << (directedFlag ? "�L��" : "����") << "�O���t" << endl;
		cout << endl;
		for (int i = 0; i < N; i++) {
			if (nodeWeighedFlag) {
				cout << "i = " << i << " (weigh = " << weigh[i] << "), �ڑ��� = ";
			}
			else {
				cout << "i = " << i << ", �ڑ��� = ";
			}
			if (next[i].size() == 0) { cout << "�Ȃ�" << endl; continue; }
			auto itr = next[i].begin();
			if (edgeWeighedFlag) {
				cout << itr->y << "(" << itr->weigh << ")";
			}
			else {
				cout << itr->y;
			}
			itr++;

			for (; itr != next[i].end(); itr++) {
				if (edgeWeighedFlag) {
					cout << ", " << itr->y << "(" << itr->weigh << ")";
				}
				else {
					cout << ", " << itr->y;
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	int N, M;
	int* weigh;
	vector<edgeClass>* next;
	edgeClass* edge;
	bool nodeWeighedFlag;// �m�[�h�ɏd�݂����Ă��邩
	bool edgeWeighedFlag;// �G�b�W�ɏd�݂����Ă��邩
	bool directedFlag;// �L�����ǂ���
};
class treeClass : public graphClass {// ��
public:
	treeClass() {
		depth = NULL;
	}
	void activate(const char* nodeWeigh, const char* edgeWeigh, const char* subFlag, const char* directed) {
		cin >> N, M = N - 1;
		depth = new int[N];
		for (int i = 0; i < N; i++) {
			depth[i] = N + 1;
		}
		activateMain(strcmp(nodeWeigh, "weighed") == 0, strcmp(edgeWeigh, "weighed") == 0, strcmp(subFlag, "subtract") == 0, strcmp(directed, "directed") == 0);
	}
private:
	void getDepth(int i, int d) {// �[���D��T���ō�����̋����𓾂�
		depth[i] = d;
		if (edgeWeighedFlag) {
			for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
				if (depth[itr->y] > d + itr->weigh) {
					getDepth(itr->y, d + itr->weigh);
				}
			}
		}
		else {
			for (auto itr = next[i].begin(); itr != next[i].end(); itr++) {
				if (depth[itr->y] > d + 1) {
					getDepth(itr->y, d + 1);
				}
			}
		}
	}
public:
	void setRoot(int n) {// ����ݒ肷��B�����ɍ�����̋����𓾂�B
		getDepth(n, 0);
	}
	void debugCout() {// �f�o�b�O�o�͗p
		cout << endl;
		cout << "�m�[�h�̌� = " << N << "��" << endl;
		cout << "�G�b�W�̖{�� = " << M << "�{" << endl;
		cout << "�d��" << (nodeWeighedFlag ? "��" : "�Ȃ�") << "�m�[�h " << "�d��" << (edgeWeighedFlag ? "��" : "�Ȃ�") << "�G�b�W " << (directedFlag ? "�L��" : "����") << "�O���t" << endl;
		cout << endl;
		for (int i = 0; i < N; i++) {
			if (nodeWeighedFlag) {
				cout << "i = " << i << " (weigh = " << weigh[i] << "), �[�� = " << depth[i] << ", �ڑ��� = ";
			}
			else {
				cout << "i = " << i << ", �[�� = " << depth[i] << ", �ڑ��� = ";
			}
			if (next[i].size() == 0) { cout << "�Ȃ�" << endl; continue; }
			auto itr = next[i].begin();
			if (edgeWeighedFlag) {
				cout << itr->y << "(" << itr->weigh << ")";
			}
			else {
				cout << itr->y;
			}
			itr++;

			for (; itr != next[i].end(); itr++) {
				if (edgeWeighedFlag) {
					cout << ", " << itr->y << "(" << itr->weigh << ")";
				}
				else {
					cout << ", " << itr->y;
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	int* depth;//������̐[��
};

void bfs(graphClass & G, int root) {// ���D��T��
	int N = G.N;
	bool* visited = new bool[N];
	for (int i = 0; i < N; i++) {
		visited[i] = (i == root);
	}

	queue<int> q; q.push(root);

	while (q.size() > 0) {
		int n = q.front(); q.pop();
		visited[n] = true;


		//	�����Ɋe�m�[�h�ōs������������


		for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {
			if (visited[itr->y] == false) {
				q.push(itr->y);
			}
		}
	}

	delete[] visited;
}
void bfs(treeClass & T, int root) {
	bfs((graphClass&)T, root);
}
bool* dfs_visited = NULL;
void dfs_process_main(graphClass & G, int n) {
	dfs_visited[n] = true;


	//	�����Ɋe�m�[�h�ōs������������


	for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {
		if (dfs_visited[itr->y] == false) {
			dfs_process_main(G, itr->y);
		}
	}
}
void dfs(graphClass & G, int root) {// �[���D��T��
	int N = G.N;
	dfs_visited = new bool[N];
	for (int i = 0; i < N; i++) { dfs_visited[i] = false; }
	dfs_process_main(G, 0);
}
void dfs(treeClass & T, int root) {
	dfs((graphClass&)T, root);
}




*/