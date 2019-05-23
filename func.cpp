/*

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>

using namespace std;

#define arraySize(A) (sizeof(A)/sizeof(A[0]))





/////////////         最大・最小

int arrayMax(int size, int *array, int *dest) {
	if (size <= 0 || array == NULL) { return -1; }
	int p = 0;
	for (int i = 0; i < size; i++) {
		if (array[p] < array[i]) { p = i; }
	}
	if (dest != NULL) { *dest = array[p]; }
	return p;
}
int arrayMin(int size, int *array, int *dest) {
	if (size <= 0 || array == NULL) { return -1; }
	int p = 0;
	for (int i = 0; i < size; i++) {
		if (array[p] > array[i]) { p = i; }
	}
	if (dest != NULL) { *dest = array[p]; }
	return p;
}







//////////一般化した二分探索

const bool LEFT = false;
const bool RIGHT = true;
bool judgeLR(int i, int key);// 左に属するか右に属するかを判断する関数。下で定義する。

int nibutanL(int size, int key) {// LEFTグループに属するうち最も右側のindexを得る
	int L = -1;
	int R = size;
	while (abs(R - L) > 1) {
		int mid = (L + R) / 2;
		if (judgeLR(mid, key) == RIGHT) R = mid;
		else L = mid;
	}
	return L;
}
int nibutanR(int size, int key) {//RIGHTグループに属するうち最も左側のindexを得る
	return nibutanL(size, key) + 1;
}


//////   使用例
int* x;// 昇順ソート済み配列

//	LEFTグループ	...	  要素がkeyより小さい
//	RIGHTグループ	...	  要素がkey以上
bool judgeLR(int i, int key) {
	if (x[i] < key) {
		return LEFT;
	}
	return RIGHT;
}

int main() {
	int N; cin >> N;
	x = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> x[i];
	}

	cout << "LEFTグループ	...	  要素がkeyより小さい" << endl;
	cout << "RIGHTグループ	...	  要素がkey以上" << endl;

	for (int i = 0; i <= 20; i += 2) {
		cout << "key = " << i << ", nibutanL = " << nibutanL(N, i) << ", nibutanR = " << nibutanR(N, i) << endl;
	}
	return 0;
}
//////		検証用入力データ
10
0 1 1 2 2 5 8 15 18 18







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
		int xsize = getSize(x), ysize=getSize(y);
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
	int *parent;// 親の番号。自分自身が親なら-1。
	int *size;// 親のみ有効。自分のグループのサイズ。
};


//////		使用例
int main() {
	int N, M; cin >> N >> M;		// ノードの個数、エッジの本数を取得

	UnionFindClass uf;				// クラスの作成
	uf.activate(N);					// ノード数Nに初期化
	
	for (int i = 0; i < M; i++) {
		int x, y;
		cin >> x >> y;				// それぞれのエッジが繋ぐ頂点を取得
		uf.connect(x, y);			// つなげる
	}
	
	for (int i = 0; i < N; i++) {	// 全頂点についてチェック
		// 親番号とサイズを出力
		// 自分が親かどうか見たかったら uf.getParent(i) == i で判断する

		cout <<"i = "<< i << ", Parent = " << uf.getParent(i) << ", Size = " << uf.getSize(i) << endl;
	}
	
	return 0;
}
//////		検証用入力データ
5 4
0 1
1 2
0 2
3 4







/////////////         備忘録

優先度付きキューの構文
	priority_queue<int> que; // 降順に出力
	priority_queue<int, vector<int>, greater<int>> que; // 昇順に出力

	que.push(int n); で数字を追加
	que.top(); で最大値/最小値を見る
	que.pop(); で最大値/最小値を消去
	que.size(); でサイズ取得
	que.empty(); で空かどうかチェック
*/