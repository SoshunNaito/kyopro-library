/*
/////////////         グラフを扱うクラス

class edgeClass {// 辺のクラス
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
bool edgeClass_compare(const edgeClass& a, const edgeClass& b) {//keyを見比べる
	int x = b.x - a.x;
	if (x > 0) { return true; }
	x = b.y - a.y;
	return x > 0;
}
class graphClass {// グラフ入力を受け取る
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
	void activateMain(bool nodeWeigh, bool edgeWeigh, bool subFlag, bool directed) {// subFlag==trueなら入力から1を引く。direted==trueなら有向グラフ
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

		for (int i = 0; i < M; i++) {// 入力を受け取っておく
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
				sort(next[i].begin(), next[i].end(), edgeClass_compare);// vectorのソートってこんな簡単なの！？
			}
		}
	}
	void activate(const char* nodeWeigh, const char* edgeWeigh, const char* subFlag, const char* directed) {// subFlagは入力から1を引くかどうか
		cin >> N >> M;
		activateMain(strcmp(nodeWeigh, "weighed") == 0, strcmp(edgeWeigh, "weighed") == 0, strcmp(subFlag, "subtract") == 0, strcmp(directed, "directed") == 0);
	}

	void debugCout() {// デバッグ出力用
		cout << endl;
		cout << "ノードの個数 = " << N << "個" << endl;
		cout << "エッジの本数 = " << M << "本" << endl;
		cout << "重み" << (nodeWeighedFlag ? "つき" : "なし") << "ノード " << "重み" << (edgeWeighedFlag ? "つき" : "なし") << "エッジ " << (directedFlag ? "有向" : "無向") << "グラフ" << endl;
		cout << endl;
		for (int i = 0; i < N; i++) {
			if (nodeWeighedFlag) {
				cout << "i = " << i << " (weigh = " << weigh[i] << "), 接続先 = ";
			}
			else {
				cout << "i = " << i << ", 接続先 = ";
			}
			if (next[i].size() == 0) { cout << "なし" << endl; continue; }
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
	bool nodeWeighedFlag;// ノードに重みがついているか
	bool edgeWeighedFlag;// エッジに重みがついているか
	bool directedFlag;// 有向かどうか
};
class treeClass : public graphClass {// 木
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
	void getDepth(int i, int d) {// 深さ優先探索で根からの距離を得る
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
	void setRoot(int n) {// 根を設定する。同時に根からの距離を得る。
		getDepth(n, 0);
	}
	void debugCout() {// デバッグ出力用
		cout << endl;
		cout << "ノードの個数 = " << N << "個" << endl;
		cout << "エッジの本数 = " << M << "本" << endl;
		cout << "重み" << (nodeWeighedFlag ? "つき" : "なし") << "ノード " << "重み" << (edgeWeighedFlag ? "つき" : "なし") << "エッジ " << (directedFlag ? "有向" : "無向") << "グラフ" << endl;
		cout << endl;
		for (int i = 0; i < N; i++) {
			if (nodeWeighedFlag) {
				cout << "i = " << i << " (weigh = " << weigh[i] << "), 深さ = " << depth[i] << ", 接続先 = ";
			}
			else {
				cout << "i = " << i << ", 深さ = " << depth[i] << ", 接続先 = ";
			}
			if (next[i].size() == 0) { cout << "なし" << endl; continue; }
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

	int* depth;//根からの深さ
};

void bfs(graphClass & G, int root) {// 幅優先探索
	int N = G.N;
	bool* visited = new bool[N];
	for (int i = 0; i < N; i++) {
		visited[i] = (i == root);
	}

	queue<int> q; q.push(root);

	while (q.size() > 0) {
		int n = q.front(); q.pop();
		visited[n] = true;


		//	ここに各ノードで行う処理を書く


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


	//	ここに各ノードで行う処理を書く


	for (auto itr = G.next[n].begin(); itr != G.next[n].end(); itr++) {
		if (dfs_visited[itr->y] == false) {
			dfs_process_main(G, itr->y);
		}
	}
}
void dfs(graphClass & G, int root) {// 深さ優先探索
	int N = G.N;
	dfs_visited = new bool[N];
	for (int i = 0; i < N; i++) { dfs_visited[i] = false; }
	dfs_process_main(G, 0);
}
void dfs(treeClass & T, int root) {
	dfs((graphClass&)T, root);
}




*/