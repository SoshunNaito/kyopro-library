/*
///////////////   セグメント木

// ここでセグ木の設定をする

// #define SEGTREE_DATA_ADD			// 和をとるセグ木
#define SEGTREE_DATA_MAX			// 最大値をとるセグ木
// #define SEGTREE_DATA_MIN			// 最小値をとるセグ木

// #define SEGTREE_LAZY_SET			// 区間代入する遅延セグ木
#define SEGTREE_LAZY_ADD			// 区間加算する遅延セグ木
// #define SEGTREE_LAZY_MAX			// 最大値を更新する遅延セグ木
// #define SEGTREE_LAZY_MIN			// 最小値を更新する遅延セグ木


const ll INF = 1LL << 60;
#ifdef SEGTREE_DATA_ADD
const ll segtree_data_init = 0;
inline ll segtree_data_merge(ll a, ll b) {// 要素aのbの和
	return a + b;
}
#endif
#ifdef SEGTREE_DATA_MAX
const ll segtree_data_init = -INF;
inline ll segtree_data_merge(ll a, ll b) {// 要素aのbの最大値
	return max(a, b);
}
#endif
#ifdef SEGTREE_DATA_MIN
const ll segtree_data_init = INF;
inline ll segtree_data_merge(ll a, ll b) {// 要素aのbの最小値
	return min(a, b);
}
#endif

#ifdef SEGTREE_LAZY_SET
const ll segtree_lazy_init = 0;
inline ll segtree_lazy_merge(ll a, ll b) {// 演算子aとbのマージ
	return b;
}
inline ll segtree_lazy_multi(ll a, ll n) {// 演算子aをn個つなげたもの
	return a;
}
inline ll segtree_lazy_divide(ll a) {// 演算子aを二個に分ける
	return a;
}
inline ll segtree_lazy_apply(ll a, ll x) {// aに演算子xを適用する
	return x;
}
#endif
#ifdef SEGTREE_LAZY_ADD
const ll segtree_lazy_init = 0;
inline ll segtree_lazy_merge(ll a, ll b) {// 演算子aとbのマージ
	return a + b;
}
inline ll segtree_lazy_multi(ll a, ll n) {// 演算子aをn個つなげたもの
	return a * n;
}
inline ll segtree_lazy_divide(ll a) {// 演算子aを二個に分ける
	return a / 2;
}
inline ll segtree_lazy_apply(ll a, ll x) {// aに演算子xを適用する
	return a + x;
}
#endif
#ifdef SEGTREE_LAZY_MAX
const ll segtree_lazy_init = -INF;
inline ll segtree_lazy_merge(ll a, ll b) {// 演算子aとbのマージ
	return max(a, b);
}
inline ll segtree_lazy_multi(ll a, ll n) {// 演算子aをn個つなげたもの
	return a;
}
inline ll segtree_lazy_divide(ll a) {// 演算子aを二個に分ける
	return a;
}
inline ll segtree_lazy_apply(ll a, ll x) {// aに演算子xを適用する
	return max(a, x);
}
#endif
#ifdef SEGTREE_LAZY_MIN
const ll segtree_lazy_init = INF;
inline ll segtree_lazy_merge(ll a, ll b) {// 演算子aとbのマージ
	return min(a, b);
}
inline ll segtree_lazy_multi(ll a, ll n) {// 演算子aをn個つなげたもの
	return a;
}
inline ll segtree_lazy_divide(ll a) {// 演算子aを二個に分ける
	return a;
}
inline ll segtree_lazy_apply(ll a, ll x) {// aに演算子xを適用する
	return min(a, x);
}
#endif

class SegmentTree {
public:
	SegmentTree() {
		N = 0;
		node = NULL;
	}
	inline void activate(int N, ll value = segtree_data_init) {// 初期化
		if (node != NULL) { delete[] node; }

		this->N = N;
		size = 1; while (size < N) { size *= 2; }

		node = new ll[2 * size - 1];
		for (int i = 0; i < 2 * size - 1; i++) { node[i] = value; }
	}

	inline void activate(vector<ll> v) {
		if (node != NULL) { delete[] node; }

		N = (int)v.size();
		size = 1; while (size < N) { size *= 2; }

		node = new ll[2 * size - 1];

		for (ll i = 0; i < N; i++) node[i + size - 1] = v[i];
		for (ll i = size - 2; i >= 0; i--) node[i] = segtree_data_merge(node[i * 2 + 1], node[i * 2 + 2]);
	}

	inline void set(int pos, ll v) {// posの値をvに更新する
		int k = pos + size - 1;
		node[k] = v;
		while (k > 0) {
			k = (k - 1) / 2;
			node[k] = segtree_data_merge(node[k * 2 + 1], node[k * 2 + 2]);
		}
	}

	inline ll get(ll pos) {// posの値を取得する
		if (pos < 0 || pos >= N) {
			return 0;
		}
		ll k = pos + size - 1;
		return node[k];
	}
	inline ll get(ll L, ll R) {// 半開区間 [L, R) における最小値/最大値取得などに答える
		if (L > R) {
			ll s = L; L = R; R = s;
		}
		L = max(L, (ll)0);
		R = min(R, (ll)N);

		if (L == R) {
			return 0;
		}
		return query(L, R, 0, 0, size);
	}

	inline void DebugCout() {// デバッグ用
		cout << endl << endl;
		cout << "範囲 : " << 0 << " to " << N - 1 << endl;
		int k = 2;
		for (int i = 0; i < size * 2 - 1; i++) {
			if (node[i] == segtree_data_init) {
				cout << "INIT ";
			}
			else {
				cout << node[i] << " ";
			}
			if (i + 2 == k) {
				cout << endl;
				k *= 2;
			}
		}
		cout << endl << endl;
	}
private:
	int size, N;// 確保しているサイズ、使うサイズ
	ll* node;// 管理用

	ll query(ll a, ll b, int k, int l, int r) {
		if (a <= l && r <= b) return node[k];

		int c = (l + r) / 2;

		if (b <= c) { return query(a, b, k * 2 + 1, l, c); }
		if (c <= a) { return query(a, b, k * 2 + 2, c, r); }

		return segtree_data_merge(query(a, b, k * 2 + 1, l, c), query(a, b, k * 2 + 2, c, r));
	}
};

///////////////   遅延伝播セグメント木
class LazySegmentTree {
public:
	LazySegmentTree(vector<ll> v) {
		N = (int)v.size();
		size = 1; while (size < N) size *= 2;
		node.resize(2 * size - 1, segtree_data_init);
		lazy.resize(2 * size - 1, segtree_lazy_init);

		for (int i = 0; i < N; i++) node[i + size - 1] = v[i];
		for (int i = size - 2; i >= 0; i--) node[i] = segtree_data_merge(node[i * 2 + 1], node[i * 2 + 2]);
	}
	LazySegmentTree(int N0, ll init) {
		N = N0;
		size = 1; while (size < N) size *= 2;
		node.resize(2 * size - 1, segtree_data_init);
		lazy.resize(2 * size - 1, segtree_lazy_init);

		for (int i = 0; i < N; i++) node[i + size - 1] = init;
		for (int i = size - 2; i >= 0; i--) node[i] = segtree_data_merge(node[i * 2 + 1], node[i * 2 + 2]);
	}


	inline void set(int a, int b, ll x) {// [a, b) に演算子xを設定する
		set(a, b, x, 0, 0, size);
	}
	inline ll get(int a, int b) {// [a, b) の要素の合計を得る
		return get(a, b, 0, 0, size);
	}

	void DebugCout() {// デバッグ用
		cout << endl << endl;
		cout << "範囲 : " << 0 << " to " << N - 1 << endl;
		int k = 2;
		for (int i = 0; i < size * 2 - 1; i++) {
			cout << node[i] << "(" << lazy[i] << ") ";
			if (i + 2 == k) {
				cout << endl;
				k *= 2;
			}
		}
		cout << endl << endl;
	}
private:
	inline void eval(int k, int l, int r) {
		if (lazy[k] != segtree_lazy_init) {
			node[k] = segtree_lazy_apply(node[k], lazy[k]);
			if (r - l > 1) {
				lazy[2 * k + 1] = segtree_lazy_merge(lazy[2 * k + 1], segtree_lazy_divide(lazy[k]));
				lazy[2 * k + 2] = segtree_lazy_merge(lazy[2 * k + 2], segtree_lazy_divide(lazy[k]));
			}
			lazy[k] = segtree_lazy_init;
		}
	}
	void set(int a, int b, ll x, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = segtree_lazy_merge(lazy[k], segtree_lazy_multi(x, r - l));
			eval(k, l, r);
		}
		else {
			set(a, b, x, 2 * k + 1, l, (l + r) / 2);
			set(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = segtree_data_merge(node[2 * k + 1], node[2 * k + 2]);
		}
	}
	ll get(int a, int b, int k, int l, int r) {
		eval(k, l, r);
		if (b <= l || r <= a) return 0;
		if (a <= l && r <= b) return node[k];
		ll vl = get(a, b, 2 * k + 1, l, (l + r) / 2);
		ll vr = get(a, b, 2 * k + 2, (l + r) / 2, r);
		return segtree_data_merge(vl, vr);
	}

	int N, size;
	vector<ll> node, lazy;
};

///////////////   BIT
ll BIT_FUNCTION(ll a, ll b) {// 和を計算する関数
	return a + b;
}
ll BIT_INVERSE(ll a) {// 逆元(ここでは-1倍)を求める関数
	return -a;
}
class BIT {// 左端からの和の取得、一点更新がO(logN)でできるデータ構造。
public:
	BIT() {
		N = 0;
		bit = NULL;
	}
	~BIT() {
		if (bit != NULL) {
			delete[] bit;
		}
	}
	void activate(int N, ll init = 0) {
		if (bit != NULL) { delete[] bit; }
		bit = new ll[N];
		this->N = N;
		for (int i = 0; i < N; i++) {
			bit[i] = 0;
		}
		for (int i = 0; i < N; i++) {
			add(i, init);
		}
	}
	ll sum(int i) {// i番目までの和を計算する
		if (i < 0) { return 0; }
		if (i >= N) { return bit[N - 1]; }

		i++;
		ll s = 0;
		while (i > 0) {
			s = BIT_FUNCTION(s, bit[i - 1]);
			i -= i & -i;
		}
		return s;
	}
	void add(int i, ll x) {// i番目の要素にxを加える
		if (i < 0 || i >= N) {
			return;
		}
		i++;
		while (i <= N) {
			bit[i - 1] = BIT_FUNCTION(bit[i - 1], x);
			i += i & -i;
		}
	}
	ll get(int i) {
		return BIT_FUNCTION(sum(i), BIT_INVERSE(sum(i - 1)));
	}
	void set(int i, ll x) {// i番目の要素をxに変更する
		ll diff = BIT_FUNCTION(x, BIT_INVERSE(get(i)));
		add(i, diff);
	}

	int N;
	ll* bit;
};

int main() {
	int N, M; cin >> N >> M;
	SegmentTree ST; ST.activate(N);

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		ST.set(a, b);
	}

	ST.DebugCout();

	cout << "[0, 3) : " << ST.get(0, 3) << endl;
	cout << "[4, 6) : " << ST.get(4, 6) << endl;
	cout << "[0, 5) : " << ST.get(0, 5) << endl;
	cout << "[0, 8) : " << ST.get(0, 8) << endl;

	return 0;
}
//////		検証用入力データ
8 6
0 5
2 9
4 3
5 2
7 5
6 1
*/