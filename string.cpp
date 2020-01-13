/*

class Z_algorithm {// O(N)で先頭からの共通部分列の長さを求める
public:
	void process(const char* str, int n) {
		v.resize(n);
		v[0] = n;
		int i = 1, j = 0;
		while (i < n) {
			while (i + j < n && str[j] == str[i + j]) ++j;
			v[i] = j;
			if (j == 0) { ++i; continue; }
			int k = 1;
			while (i + k < n && k + v[k] < j) v[i + k] = v[k], ++k;
			i += k; j -= k;
		}
	}
	void process(string S) {
		process(S.c_str(), S.length());
	}
	vector<int> v;
};

class Rolling_Hash {// ローリングハッシュ
public:
	Rolling_Hash() {
		v.clear();
	}
	void process(const char* str, int n, int width) {// 文字列と、全長と、切り出す長さを指定
		if (width > n) { return; }
		v.resize(n - width + 1);
		ll p1 = 0, p2 = 0;
		ll t1 = 1, t2 = 1;
		{
			ll k = width;
			ll d1 = digit1;
			ll d2 = digit2;
			while (k > 0) {
				if (k & 1) {
					t1 *= d1;
					t1 %= mod1;
					t2 *= d2;
					t2 %= mod2;
				}
				k /= 2;
				d1 = (d1 * d1) % mod1;
				d2 = (d2 * d2) % mod2;
			}
		}
		for (int i = 0; i < width; i++) {
			p1 *= digit1; p1 += str[i]; p1 %= mod1;
			p2 *= digit2; p2 += str[i]; p2 %= mod2;
		}
		int j = 0;
		v[j] = (p1 << 30) + p2; j++;
		for (int i = width; i < n; i++, j++) {
			p1 *= digit1; p1 += str[i] - str[i - width] * t1; p1 %= mod1;
			p2 *= digit2; p2 += str[i] - str[i - width] * t2; p2 %= mod2;
			if (p1 < 0) { p1 += mod1; }
			if (p2 < 0) { p2 += mod2; }
			v[j] = (p1 << 30) + p2;
		}
	}
	void process(string S, int width) {// 文字列と、切り出す長さを指定
		process(S.c_str(), S.length(), width);
	}

private:
	const ll digit1 = 10007LL;
	const ll digit2 = 10009LL;
	const ll mod1 = 1000000007LL;
	const ll mod2 = 1000000009LL;

public:
	vector<ll> v;
};

*/