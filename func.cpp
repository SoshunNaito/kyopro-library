/////////	分数どうしを比べる
class fractionCompareType
{ // a / bを比較する
public:
	fractionCompareType(ll A, ll B)
	{
		set(A, B);
	}
	inline void set(ll A, ll B)
	{
		a = A, b = B;
		flush();
	}
	inline double getDouble() const
	{
		return (double)a / b;
	}
	inline void flush()
	{
		assert(b != 0);
		if (b < 0)
		{
			a *= -1, b *= -1;
		}
		if (a == 0)
		{
			b = 1;
			return;
		}

		{
			ll p = abs(a);
			ll q = b;
			ll c;
			if (p < q)
			{
				c = p;
				p = q;
				q = c;
			}
			while (1)
			{
				p %= q;
				if (p == 0)
				{
					if (q > 1)
					{
						a /= q;
						b /= q;
					}
					return;
				}
				c = p;
				p = q;
				q = c;
			}
		}
	}
	inline bool operator==(const fractionCompareType &another) const
	{
		return (a == another.a) & (b == another.b);
	}
	inline bool operator!=(const fractionCompareType &another) const
	{
		return !(*this == another);
	}
	inline bool operator<(const fractionCompareType &another) const
	{
		ll p1 = a, q1 = b;
		ll p2 = another.a, q2 = another.b;

		if (p1 < 0 && p2 >= 0)
		{
			return true;
		}
		if (p1 >= 0 && p2 < 0)
		{
			return false;
		}
		if (p1 < 0)
		{
			p1 *= -1;
			p2 *= -1;
			ll c = p1;
			p1 = p2;
			p2 = c;
			c = q1;
			q1 = q2;
			q2 = c;
		}

		while (1)
		{
			ll c1 = p1 / q1;
			ll c2 = p2 / q2;
			if (c1 != c2)
			{
				return c1 < c2;
			}
			p1 -= q1 * c1;
			p2 -= q2 * c2;
			if (p1 == 0 || p2 == 0)
			{
				return p1 < p2;
			}

			c1 = p1;
			p1 = q2;
			q2 = c1;
			c2 = p2;
			p2 = q1;
			q1 = c2;
		}
	};
	inline bool operator>=(const fractionCompareType &another) const
	{
		return !(*this < another);
	}
	inline bool operator>(const fractionCompareType &another) const
	{
		if (*this == another)
		{
			return false;
		}
		if (*this < another)
		{
			return false;
		}
		return true;
	};
	inline bool operator<=(const fractionCompareType &another) const
	{
		return !(*this > another);
	}

	ll a, b;
};

/////////	使用例
int main()
{
	set<fractionCompareType> st;
	for (int i = -10; i < 10; i++)
	{
		for (int j = -10; j < 10; j++)
		{
			if (j == 0)
			{
				break;
			}
			st.insert({i, j}); // 分数の値が同じ場合は1個にまとまる
		}
	}

	for (auto itr = st.begin(); itr != st.end(); itr++)
	{
		// 既約分数が出力される
		cout << itr->a << " / " << itr->b << " (" << itr->getDouble() << ")" << endl;
	}

	return 0;
}

/////////	ランレングス圧縮をして(要素, 個数)の形にする
template <typename T>
void runLengthCompression(vector<T> &src, vector<pair<T, int>> &dest)
{
	dest.clear();
	int N = src.size();
	if (N == 0)
	{
		return;
	}

	int count = 1;
	T temp = src[0];
	for (int i = 1; i <= N; i++)
	{
		if (i == N)
		{
			dest.push_back({temp, count});
		}
		else
		{
			if (src[i] != temp)
			{
				dest.push_back({temp, count});
				temp = src[i];
				count = 1;
			}
			else
			{
				count++;
			}
		}
	}
}

/////////	使用例
int main()
{
	vector<ll> src = {
		0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9};
	vector<pair<ll, int>> dest;

	runLengthCompression(src, dest);

	for (auto itr = dest.begin(); itr != dest.end(); itr++)
	{
		cout << itr->first << " が " << itr->second << " 個" << endl;
	}

	return 0;
}

/////////	座標圧縮
template <typename T>
class compressionClass
{
public:
	compressionClass()
	{
		st.clear();
	}
	void add(T element)
	{
		st.insert(element);
	}
	void execute()
	{
		v.clear();
		mmap.clear();

		v.resize(st.size());
		int i = 0;
		for (auto itr = st.begin(); itr != st.end(); itr++)
		{
			v[i] = *itr;
			mmap.insert({*itr, i});
			i++;
		}
		N = v.size();
	}

	int N;
	vector<T> v;
	unordered_map<T, int> mmap;

private:
	set<T> st;
};

/////////	使用例
int main()
{
	vector<ll> src = {
		274, 6, 134, 65, 6, 4, 362, 5, 2647, 3, 978, 7, 52, 57, 46, 5, 057, 75352, 5, 34, 8, 375645, 123452};

	compressionClass<ll> C;
	for (int i = 0; i < src.size(); i++)
	{
		C.add(src[i]);
	}
	C.execute();

	for (int i = 0; i < C.v.size(); i++)
	{
		cout << C.v[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < src.size(); i++)
	{
		cout << C.mmap[src[i]] << " ";
	}
	cout << endl;

	return 0;
}

////////////////	平面から直線への写像
struct HashMap2D
{
	HashMap2D()
	{
		Hmax = 1000000007, Hmin = -1000000007;
		Wmax = 1000000007, Wmin = -1000000007;
		Height = Hmax - Hmin;
		Width = Wmax - Wmin;
	}
	HashMap2D(ll H_max, ll W_max, ll H_min = 0, ll W_min = 0)
	{
		Hmax = H_max;
		Hmin = H_min;
		Wmax = W_max;
		Wmin = W_min;
		Height = Hmax - Hmin;
		Width = Wmax - Wmin;
	}
	ll hash(ll h, ll w)
	{
		h -= Hmin, w -= Wmin;
		return Width * h + w;
	}
	ll hash(pair<ll, ll> p)
	{
		return hash(p.first, p.second);
	}
	pair<ll, ll> inv(ll index)
	{
		pair<ll, ll> p;
		p.first = index / Width;
		p.second = index % Width;
		p.first += Hmin;
		p.second += Wmin;
		return p;
	}

private:
	ll Hmax, Hmin, Wmax, Wmin;
	ll Height, Width;
};

////////////////	使用例
int main()
{
	const int H = 100, W = 1000;
	HashMap2D hm(H, W);
	cout << hm.hash(0, 0) << endl;
	cout << hm.hash(1, 0) << endl;
	cout << hm.hash(0, 1) << endl;
	cout << endl;

	const ll H_min = -50, H_max = 50;
	const ll W_min = -500, W_max = 500;
	HashMap2D hm2(H_max, W_max, H_min, W_min);
	cout << hm2.hash({0, 0}) << endl;
	cout << hm2.hash({1, 0}) << endl;
	cout << hm2.hash({-1, 0}) << endl;
	cout << hm2.hash({0, 1}) << endl;
	cout << hm2.hash({0, -1}) << endl;
	cout << endl;

	pair<ll, ll> p = hm2.inv(76543);
	cout << p.first << " " << p.second << endl;

	return 0;
}

/////////	グリッドを扱うクラス
const int UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8;
class gridClass
{
public:
	gridClass()
	{
		W = 0;
		H = 0;
		direction.clear();
		active.clear();
	}
	gridClass(int H0, int W0)
	{
		init(H0, W0);
	}
	void init(int H0, int W0)
	{
		H = H0, W = W0;
		direction.clear();
		direction.resize(H);
		active.clear();
		active.resize(H);

		for (int y = 0; y < H; y++)
		{
			direction[y].clear();
			direction[y].resize(W);
			active[y].clear();
			active[y].resize(W);

			for (int x = 0; x < W; x++)
			{
				direction[y][x] = 0;
				if (y > 0)
				{
					direction[y][x] += UP;
				}
				if (y < H - 1)
				{
					direction[y][x] += DOWN;
				}
				if (x > 0)
				{
					direction[y][x] += LEFT;
				}
				if (x < W - 1)
				{
					direction[y][x] += RIGHT;
				}

				active[y][x] = true;
			}
		}
	}

	void enable(int y, int x, int command = 0, bool directedFlag = false)
	{
		if (command == 0)
		{
			active[y][x] = true;
			return;
		}
		if (command & UP)
		{
			if (y > 0)
			{
				direction[y][x] |= UP;
				if (directedFlag == false)
				{
					direction[y - 1][x] |= DOWN;
				}
			}
		}
		if (command & DOWN)
		{
			if (y < H - 1)
			{
				direction[y][x] |= DOWN;
				if (directedFlag == false)
				{
					direction[y + 1][x] |= UP;
				}
			}
		}
		if (command & LEFT)
		{
			if (x > 0)
			{
				direction[y][x] |= LEFT;
				if (directedFlag == false)
				{
					direction[y][x - 1] |= RIGHT;
				}
			}
		}
		if (command & RIGHT)
		{
			if (x < W - 1)
			{
				direction[y][x] |= RIGHT;
				if (directedFlag == false)
				{
					direction[y][x + 1] |= LEFT;
				}
			}
		}
	}
	void disable(int y, int x, int command = 0, bool directedFlag = false)
	{
		if (command == 0)
		{
			active[y][x] = false;
			return;
		}
		if (command & UP)
		{
			if (y > 0)
			{
				direction[y][x] &= (15 - UP);
				if (directedFlag == false)
				{
					direction[y - 1][x] &= (15 - DOWN);
				}
			}
		}
		if (command & DOWN)
		{
			if (y < H - 1)
			{
				direction[y][x] &= (15 - DOWN);
				if (directedFlag == false)
				{
					direction[y + 1][x] &= (15 - UP);
				}
			}
		}
		if (command & LEFT)
		{
			if (x > 0)
			{
				direction[y][x] &= (15 - LEFT);
				if (directedFlag == false)
				{
					direction[y][x - 1] &= (15 - RIGHT);
				}
			}
		}
		if (command & RIGHT)
		{
			if (x < W - 1)
			{
				direction[y][x] &= (15 - RIGHT);
				if (directedFlag == false)
				{
					direction[y][x + 1] &= (15 - LEFT);
				}
			}
		}
	}

	void getBfsOrder(
		vector<pair<pair<int, int>, int>> &dest, // { { y座標(i成分), x座標(j成分) }, 親ノード番号 }
		vector<pair<int, int>> src = {{0, 0}}	 // y座標(i成分)、x座標(j成分)の順
	)
	{
		dest.clear();

		vector<vector<int>> order(H);
		for (int i = 0; i < H; i++)
		{
			order[i].resize(W, -1);
		}

		queue<pair<pair<int, int>, int>> q;

		int counter = 0;

		for (int i = 0; i < src.size(); i++)
		{
			q.push({src[i], -1});
			order[src[i].first][src[i].second] = counter;
			counter++;
		}

		while (q.size() > 0)
		{
			dest.push_back(q.front());
			pair<int, int> p = q.front().first;
			q.pop();

			if (
				(direction[p.first][p.second] & UP) != 0 &&
				active[p.first - 1][p.second] == true &&
				order[p.first - 1][p.second] == -1)
			{
				q.push({{p.first - 1, p.second}, order[p.first][p.second]});
				order[p.first - 1][p.second] = counter;
				counter++;
			}
			if (
				(direction[p.first][p.second] & DOWN) != 0 &&
				active[p.first + 1][p.second] == true &&
				order[p.first + 1][p.second] == -1)
			{
				q.push({{p.first + 1, p.second}, order[p.first][p.second]});
				order[p.first + 1][p.second] = counter;
				counter++;
			}
			if (
				(direction[p.first][p.second] & LEFT) != 0 &&
				active[p.first][p.second - 1] == true &&
				order[p.first][p.second - 1] == -1)
			{
				q.push({{p.first, p.second - 1}, order[p.first][p.second]});
				order[p.first][p.second - 1] = counter;
				counter++;
			}
			if (
				(direction[p.first][p.second] & RIGHT) != 0 &&
				active[p.first][p.second + 1] == true &&
				order[p.first][p.second + 1] == -1)
			{
				q.push({{p.first, p.second + 1}, order[p.first][p.second]});
				order[p.first][p.second + 1] = counter;
				counter++;
			}
		}
	}

	int H, W;

private:
	vector<vector<int>> direction;
	vector<vector<bool>> active;
};

/////////	使用例
int main()
{
	char stage[5][6] = {
		".#..#",
		"...#.",
		"#.##.",
		"...#.",
		".#..."};

	gridClass G(5, 5);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (stage[i][j] == '.')
			{
				G.enable(i, j);
			}
			else
			{
				G.disable(i, j);
			}
		}
	}

	vector<pair<pair<int, int>, int>> v;
	G.getBfsOrder(v);

	for (auto itr = v.begin(); itr != v.end(); itr++)
	{
		if (itr->second == -1)
		{
			cout << "[source] -> [" << itr->first.first << ", " << itr->first.second << "]" << endl;
		}
		else
		{
			cout << "[" << v[itr->second].first.first << ", " << v[itr->second].first.second << "] -> [" << itr->first.first << ", " << itr->first.second << "]" << endl;
		}
	}

	return 0;
}

/////////	一般化した二分探索

const bool LEFT = false;
const bool RIGHT = true;
bool judgeLR(int i, int key); // 左に属するか右に属するかを判断する関数。下で定義する。

int nibutanL(int size, int key)
{ // LEFTグループに属するうち最も右側のindexを得る
	int L = -1;
	int R = size;
	while (abs(R - L) > 1)
	{
		int mid = (L + R) / 2;
		if (judgeLR(mid, key) == RIGHT)
			R = mid;
		else
			L = mid;
	}
	return L;
}
int nibutanR(int size, int key)
{ // RIGHTグループに属するうち最も左側のindexを得る
	return nibutanL(size, key) + 1;
}

/////////	使用例
int *x; // 昇順ソート済み配列

//	LEFTグループ	...	  要素がkeyより小さい
//	RIGHTグループ	...	  要素がkey以上
bool judgeLR(int i, int key)
{
	if (x[i] < key)
	{
		return LEFT;
	}
	return RIGHT;
}

int main()
{
	int N;
	cin >> N;
	x = new int[N];
	for (int i = 0; i < N; i++)
	{
		cin >> x[i];
	}

	cout << "LEFTグループ	...	  要素がkeyより小さい" << endl;
	cout << "RIGHTグループ	...	  要素がkey以上" << endl;

	for (int i = 0; i <= 20; i += 2)
	{
		cout << "key = " << i << ", nibutanL = " << nibutanL(N, i) << ", nibutanR = " << nibutanR(N, i) << endl;
	}
	return 0;
}
/////////	検証用入力データ
10 0 1 1 2 2 5 8 15 18 18

	/////////	UnionFind
	//    バラバラの要素を結合してグループにまとめる際に使える構造。
	//    グループ番号、要素数の取得が可能だが、グループに属する要素の列挙はO(N)かかる。

	class unionFindClass
{
public:
	unionFindClass()
	{
		N = 0;
		parent = NULL;
		size = NULL;
	}
	~unionFindClass()
	{
		if (parent != NULL)
		{
			delete[] parent;
		}
		if (size != NULL)
		{
			delete[] size;
		}
	}

	void activate(int n)
	{ // 要素の数N
		N = n;
		parent = new int[N];
		size = new int[N];
		for (int i = 0; i < N; i++)
		{
			parent[i] = -1;
			size[i] = 1;
		}
	}

	int getParent(int x)
	{ // グループの親の番号を得る
		if (parent[x] == -1)
		{
			return x;
		}
		else
		{
			int y = getParent(parent[x]);
			parent[x] = y;
			return y;
		}
	}
	int getSize(int x)
	{ // 自分が属するグループのサイズを得る
		x = getParent(x);
		return size[x];
	}
	bool connect(int x, int y)
	{ // 二つの要素を結ぶ。２グループ間を繋いだ場合trueを返す
		x = getParent(x);
		y = getParent(y);
		if (x == y)
		{
			return false;
		}
		int xsize = getSize(x), ysize = getSize(y);
		if (xsize < ysize)
		{
			parent[x] = y;
			size[y] += size[x];
			size[x] = 0;
		}
		else
		{
			parent[y] = x;
			size[x] += size[y];
			size[y] = 0;
		}
		return true;
	}

	//データ
	int N;		 // 個数
	int *parent; // 親の番号。自分自身が親なら-1。
	int *size;	 // 親のみ有効。自分のグループのサイズ。
};

/////////	使用例
int main()
{
	int N, M;
	cin >> N >> M; // ノードの個数、エッジの本数を取得

	unionFindClass uf; // クラスの作成
	uf.activate(N);	   // ノード数Nに初期化

	for (int i = 0; i < M; i++)
	{
		int x, y;
		cin >> x >> y;	  // それぞれのエッジが繋ぐ頂点を取得
		uf.connect(x, y); // つなげる
	}

	for (int i = 0; i < N; i++)
	{ // 全頂点についてチェック
		// 親番号とサイズを出力
		// 自分が親かどうか見たかったら uf.getParent(i) == i で判断する

		cout << "i = " << i << ", Parent = " << uf.getParent(i) << ", Size = " << uf.getSize(i) << endl;
	}

	return 0;
}
/////////	検証用入力データ
5 4 0 1 1 2 0 2 3 4

	/////////	xorで掃き出し法
	//		数の集合が与えられたとき、掃き出し法によって上三角行列の形で保持する。
	//		ある数がその集合の部分集合のxor和で表現できるかどうかの判定が高速にできる。

	const int BITSIZE = 64; // 横幅のビット数

class bitGreaterClass
{ // 降順
public:
	bool operator()(const bitset<BITSIZE> &left, const bitset<BITSIZE> &right) const
	{
		return left.to_ullong() > right.to_ullong();
	}
};

class bitMatrixClass
{
public:
	bitMatrixClass()
	{
		matrix.clear();
		pivot.clear();
	}

	int getSize()
	{ // 縦のサイズ取得
		return matrix.size();
	}

	void add(bitset<BITSIZE> bit)
	{ // 行の追加
		bit = sweep(bit);

		if (bit.any())
		{
			bitset<BITSIZE> p = bit;
			{ // 最上位ビットを取得
				int n = 1;
				for (int k = BITSIZE; k > 1; k = (k + 1) / 2)
				{
					p |= (p >> n);
					n *= 2;
				}
				p ^= (p >> 1);
			}

			auto itr = matrix.begin();
			for (; itr != matrix.end(); itr++)
			{
				if ((*itr & p).any())
				{
					bitset<BITSIZE> q = *itr ^ bit;
					matrix.erase(itr);
					itr = matrix.insert(q).first;
				}
			}

			matrix.insert(bit);
			pivot.insert(p);
		}
	}
	void add(ll k)
	{
		bitset<BITSIZE> bit = k;
		add(bit);
	}

	bitset<BITSIZE> sweep(bitset<BITSIZE> bit)
	{ // 掃き出し法で重複成分を消去
		auto itr1 = matrix.begin();
		auto itr2 = pivot.begin();
		for (; itr1 != matrix.end(); itr1++)
		{
			if ((bit & (*itr2)).any())
			{
				bit ^= *itr1;
			}
			itr2++;
		}
		return bit;
	}
	bitset<BITSIZE> sweep(ll k)
	{
		bitset<BITSIZE> bit = k;
		return sweep(bit);
	}

	void debugCout()
	{ // デバッグ出力用
		cout << endl;
		cout << "縦 " << getSize() << " 行, 横 " << BITSIZE << " 列" << endl;
		for (auto itr = matrix.begin(); itr != matrix.end(); itr++)
		{
			cout << *itr << endl;
		}
		cout << endl;
	}

	//データ
	set<bitset<BITSIZE>, bitGreaterClass> matrix; // 保持する行列
	set<bitset<BITSIZE>, bitGreaterClass> pivot;  // 最上位ビット
};

/////////	使用例
int main()
{
	bitMatrixClass bm;

	int N;
	cin >> N; // 行列に追加する要素の個数
	for (int i = 0; i < N; i++)
	{
		int a;
		cin >> a;
		bm.add(a); // 追加
	}

	bm.debugCout();

	for (int k = 10; k <= 100; k += 10)
	{ // 追加した要素の組み合わせで表現できるときは0になる
		cout << "k = " << k << ", sweep(k) = " << bm.sweep(k).to_ullong() << endl;
	}

	return 0;
}
/*
/////////	検証用入力データ
5 43 36 12 97 68
*/