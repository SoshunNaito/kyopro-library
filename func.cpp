/*
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

class unionFindClass {
public:
	unionFindClass() {
		N = 0;
		parent = NULL;
		size = NULL;
	}
	~unionFindClass() {
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

	unionFindClass uf;				// クラスの作成
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







/////////////         xorで掃き出し法
//		数の集合が与えられたとき、掃き出し法によって上三角行列の形で保持する。
//		ある数がその集合の部分集合のxor和で表現できるかどうかの判定が高速にできる。

const int BITSIZE = 64; // 横幅のビット数

class bitGreaterClass {// 降順
public:
	bool operator() (const bitset<BITSIZE>& left, const bitset<BITSIZE>& right) const {
		return left.to_ullong() > right.to_ullong();
	}
};

class bitMatrixClass {
public:
	bitMatrixClass() {
		matrix.clear();
		pivot.clear();
	}

	int getSize() {// 縦のサイズ取得
		return matrix.size();
	}

	void add(bitset<BITSIZE> bit) {// 行の追加
		bit = sweep(bit);

		if (bit.any()) {
			bitset<BITSIZE> p = bit;
			{// 最上位ビットを取得
				int n = 1;
				for (int k = BITSIZE; k > 1; k=(k+1)/2) {
					p |= (p >> n);
					n *= 2;
				}
				p ^= (p >> 1);
			}

			auto itr = matrix.begin();
			for (; itr != matrix.end(); itr++) {
				if ((*itr & p).any()) {
					bitset<BITSIZE> q = *itr ^ bit;
					matrix.erase(itr);
					itr = matrix.insert(q).first;
				}
			}

			matrix.insert(bit);
			pivot.insert(p);
		}
	}
	void add(ll k) {
		bitset<BITSIZE> bit = k;
		add(bit);
	}

	bitset<BITSIZE> sweep(bitset<BITSIZE> bit) {// 掃き出し法で重複成分を消去
		auto itr1 = matrix.begin();
		auto itr2 = pivot.begin();
		for (; itr1 != matrix.end(); itr1++) {
			if ((bit & (*itr2)).any()) {
				bit ^= *itr1;
			}
			itr2++;
		}
		return bit;
	}
	bitset<BITSIZE> sweep(ll k) {
		bitset<BITSIZE> bit = k;
		return sweep(bit);
	}

	void debugCout() {// デバッグ出力用
		cout << endl;
		cout << "縦 " << getSize() << " 行, 横 " << BITSIZE << " 列" << endl;
		for (auto itr = matrix.begin(); itr != matrix.end(); itr++) {
			cout << *itr << endl;
		}
		cout << endl;
	}

	//データ
	set<bitset<BITSIZE>, bitGreaterClass> matrix;// 保持する行列
	set<bitset<BITSIZE>, bitGreaterClass> pivot;// 最上位ビット
};


//////		使用例
int main() {
	bitMatrixClass bm;

	int N; cin >> N;					// 行列に追加する要素の個数
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		bm.add(a);						// 追加
	}

	bm.debugCout();

	for (int k = 10; k <= 100; k+=10) {	// 追加した要素の組み合わせで表現できるときは0になる
		cout << "k = " << k << ", sweep(k) = " << bm.sweep(k).to_ullong() << endl;
	}

	return 0;
}
//////		検証用入力データ
5
43 36 12 97 68


*/