/*
class convolutionClass {// 畳み込み
private:
	const ll primes[3] = { 167772161, 469762049, 1224736769 };

	inline ll mod_inv(ll a, const ll p) {// 逆元
		ll k = a;
		if (k >= p) { k %= p; }

		if (k == 0) { return 0; }
		if (k == 1) { return 1; }
		ll s = p, t = k, m = 0, n = 1, r, c;

		while (t > 1) {
			c = s / t;
			r = s - c * t;
			c = (m - n * c) % p + p;
			if (c >= p) { c -= p; }
			s = t, m = n, t = r, n = c;
		}
		return n;
	}
	inline ll mod_multi(ll a, ll b, ll p) {// かけ算
		return (a * b) % p;
	}
	inline ll mod_pow(ll x, ll n, ll p) {// 累乗
		if (x >= p) { x = x % p; }

		if (n < 0) { return mod_pow(mod_inv(x, p), -n, p); }

		ll ans = 1, k = x;
		while (n > 0) {
			if (n & 1) { ans = mod_multi(ans, k, p); }
			k = mod_multi(k, k, p);
			n >>= 1;
		}
		return ans;
	}
	inline bool miller_rabin(ll n, ll p) {
		ll a = n - 1;
		int k = 0;

		while (a % 2 == 0) {
			k++;
			a /= 2;
		}
		ll m = mod_pow(p, a, n);
		if (m == 1) {
			return true;
		}
		for (int i = 0; i < k; i++) {
			if (m == n - 1) {
				return true;
			}
			m = mod_multi(m, m, n);
		}
		return false;
	}
	inline bool isPrime(ll n) {// 素数判定
		if (n <= 1) { return false; }

		const vector<ll> primes = {
			2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113
		};

		for (int i = 0; i < primes.size(); i++) {
			if (n % primes[i] == 0) { return false; }
		}
		if (n < 120) { return false; }

		int k = 0;
		if (n < 2047) { k = 1; }
		else if (n < 1373653) { k = 2; }
		else if (n < 25326001) { k = 3; }
		else if (n < 3215031751LL) { k = 4; }
		else if (n < 2152302898747LL) { k = 5; }
		else if (n < 3474749660383LL) { k = 6; }
		else if (n < 341550071728321LL) { k = 7; }
		else if (n < 3825123056546413051LL) { k = 9; }
		else { k = 12; }

		for (int i = 0; i < k; i++) {
			if (miller_rabin(n, primes[i]) == false) {
				return false;
			}
		}

		return true;
	}
	inline ll garner(ll a0, ll a1, ll a2, ll mod) {//	garnerのアルゴリズム
		ll c0 = a0;
		if (c0 >= primes[0]) { c0 %= primes[0]; }

		ll c1 = a1 - c0 + primes[1];
		if (c1 >= primes[1]) { c1 %= primes[1]; }
		c1 = (c1 * mod_inv(primes[0], primes[1])) % primes[1];

		ll c2 = (((a2 - c0 - c1 * primes[0]) % primes[2] * mod_inv(primes[0] * primes[1], primes[2]))) % primes[2];
		if (c2 < 0) { c2 += primes[2]; }

		return ((c2 * primes[1] + c1) % mod * primes[0] + c0) % mod;
	}

	void fft(int N, int n, vector<ll>& src, vector<ll>& dest, const ll prime, bool inverse, bool optimized = false) {// 各素数についてFFTを行う
		if (optimized) {
			for (int i = 0; i < N; i++) {
				dest[i] = src[i];
				if (dest[i] >= prime) { dest[i] %= prime; }
			}
		}
		else {
			vector<int> rate(n);
			int k = N / 2;
			for (int i = 0; i < n; i++) {
				rate[i] = k;
				k /= 2;
			}
			for (int i = 0; i < N; i++) {
				int k = i;
				int sum = 0;
				for (int j = 0; j < n; j++) {
					if (k & 1) { sum += rate[j]; }
					k >>= 1;
				}
				dest[sum] = src[i] % prime;
			}
		}

		vector<ll> W(N / 2 + 1);
		{
			const ll w = mod_pow(3, (prime - 1) / N * (inverse ? (-1) : 1), prime);
			W[0] = 1;
			for (int i = 1; i <= N / 2; i++) {
				W[i] = (W[i - 1] * w) % prime;
			}
		}

		bool flag = optimized & !inverse;
		for (int layer = 0; layer < n; layer++) {
			const int m = flag ? (N >> layer) : (1 << (layer + 1));
			const int M = flag ? (1 << layer) : (1 << (n - 1 - layer));
			const int h = m >> 1;

			int L = 0, R = h;
			for (int block = 0; block < M; block++) {
				for (int i = 0; i < h; i++, L++, R++) {
					const ll w0 = W[M * i];
					const ll p0 = dest[L];
					const ll q0 = flag ? (dest[R]) : ((dest[R] * w0) % prime);

					dest[L] = p0 + q0;
					dest[R] = p0 - q0;

					if (dest[L] >= prime) { dest[L] -= prime; }
					if (dest[R] < 0) { dest[R] += prime; }

					if (flag) { dest[R] = (dest[R] * w0) % prime; }
				}
				L += h;
				R += h;
			}
		}

		if (inverse == true) {
			const ll M0 = mod_inv(N, prime);

			for (int i = 0; i < N; i++) {
				dest[i] = (dest[i] * M0) % prime;
			}
		}
	}
	inline void fft(int N, int n, vector<complex<double>>& src, vector<complex<double>>& dest, bool inverse, bool optimized = false) {//	複素数を使ったFFTを行う
		if (optimized) {
			for (int i = 0; i < N; i++) {
				dest[i] = src[i];
			}
		}
		else {
			vector<int> rate(n);
			int k = N / 2;
			for (int i = 0; i < n; i++) {
				rate[i] = k;
				k /= 2;
			}
			for (int i = 0; i < N; i++) {
				int k = i;
				int sum = 0;
				for (int j = 0; j < n; j++) {
					if (k & 1) { sum += rate[j]; }
					k >>= 1;
				}
				dest[sum] = src[i];
			}
		}

		vector<complex<double>> W(N / 2 + 1);
		{
			const double theta = 2.0 * acos(-1.0) * (inverse ? (-1) : 1) / N;
			const complex<double> w1 = polar(1.0, theta);
			const complex<double> w2 = polar(1.0, theta * 2);
			const complex<double> w4 = polar(1.0, theta * 4);
			for (int i = 0; i < N / 2; i += 8) {
				W[i] = polar(1.0, theta * i); W[i + 4] = W[i] * w4;
				W[i + 2] = W[i] * w2; W[i + 6] = W[i + 4] * w2;
				W[i + 1] = W[i] * w1; W[i + 3] = W[i + 2] * w1;
				W[i + 5] = W[i + 4] * w1; W[i + 7] = W[i + 6] * w1;
			}
			W[N / 2] = -1;
		}

		bool flag = optimized & !inverse;
		for (int layer = 0; layer < n; layer++) {
			const int m = flag ? (N >> layer) : (1 << (layer + 1));
			const int M = flag ? (1 << layer) : (1 << (n - 1 - layer));
			const int h = m >> 1;

			int L = 0, R = h;
			for (int block = 0; block < M; block++) {
				for (int i = 0; i < h; i++, L++, R++) {
					const complex<double> w0 = W[M * i];
					const complex<double> p0 = dest[L];
					const complex<double> q0 = flag ? (dest[R]) : (dest[R] * w0);

					dest[L] = p0 + q0;
					dest[R] = p0 - q0;

					if (flag) { dest[R] = dest[R] * w0; }
				}
				L += h;
				R += h;
			}
		}

		if (inverse == true) {
			const double p = 1.0 / N;
			for (int i = 0; i < N; i++) { dest[i] *= p; }
		}
	}
	inline int getConvolutionSize(int x, int y, bool ntt = false) {// サイズの組からブロックサイズを得る
		int k = 0, K = 1;
		const int N = min(x, y);
		while (K < N) { K <<= 1; k++; }

		ll s = 1LL << 60, ans = 1;

		for (ll i = 0, I = 1; i <= k; i++, I <<= 1) {
			const ll a = (x + I - 1) / I;
			const ll b = (y + I - 1) / I;
			const ll score = (ntt ? 0 : (a + b) * I * i * 6) + (a * b) * I;///////////// 計算時間の評価関数
			if (chmin(s, score)) { ans = I; }
		}

		return ans;
	}
	vector<ll> convolution_main(const int size, const int a, const int b, const vector<ll>& v1, const vector<ll>& v2, const ll prime) {
		const int c = a + b;
		vector<ll> ans(size * c, 0);

		if (size <= 64) {
			for (int i = 0; i < v1.size(); i++) {
				for (int j = 0; j < v2.size(); j++) {
					ans[i + j] += v1[i] * v2[j];
				}
			}
		}
		else {
			const int N = size * 2;
			int n = 0;
			while ((1 << n) < N) { n++; }

			vector<vector<ll>> x_src(a), x_dest(a);
			vector<vector<ll>> y_src(b), y_dest(b);
			vector<vector<ll>> z_src(c - 1), z_dest(c - 1);

			for (int j = 0; j < a; j++) {
				x_src[j].resize(N, 0);
				x_dest[j].resize(N);

				for (int k = 0, l = j * size; k < size; k++, l++) {
					if (l >= v1.size()) { break; }
					x_src[j][k] = v1[l];
				}
				fft(N, n, x_src[j], x_dest[j], prime, false, true);
			}
			for (int j = 0; j < b; j++) {
				y_src[j].resize(N, 0);
				y_dest[j].resize(N);

				for (int k = 0, l = j * size; k < size; k++, l++) {
					if (l >= v2.size()) { break; }
					y_src[j][k] = v2[l];
				}
				fft(N, n, y_src[j], y_dest[j], prime, false, true);
			}
			for (int j = 0; j < c - 1; j++) {
				z_src[j].resize(N, 0);
				z_dest[j].resize(N);
			}

			for (int _a = 0; _a < a; _a++) {
				for (int _b = 0; _b < b; _b++) {
					for (int j = 0; j < N; j++) {
						z_src[_a + _b][j] += (x_dest[_a][j] * y_dest[_b][j]) % prime;
					}
				}
			}

			for (int j = 0; j < c - 1; j++) {
				fft(N, n, z_src[j], z_dest[j], prime, true, true);
				int l = j * size;
				for (int k = 0; k < N; k++, l++) {
					ans[l] += z_dest[j][k];
				}
			}
		}

		for (int i = 0; i < ans.size(); i++) {
			if (ans[i] >= prime) {
				ans[i] %= prime;
			}
		}
		return ans;
	}
public:
	vector<ll> convolution(vector<ll>& v1, vector<ll>& v2, ll mod) {// (誤差無し)畳み込みを行う
		int s1 = v1.size(), s2 = v2.size();

		while (s1 > 0 && v1[s1 - 1] == 0) { s1--; }
		while (s2 > 0 && v2[s2 - 1] == 0) { s2--; }

		if (s1 == 0 || s2 == 0) {
			return {};
		}

		const int size = getConvolutionSize(s1, s2, true);
		const int a = (s1 + size - 1) / size;
		const int b = (s2 + size - 1) / size;
		const int c = a + b;

		const int N = size * 2;
		int n = 0;
		while ((1 << n) < N) { n++; }

		if (isPrime(mod) && mod % N == 1) {
			return convolution_main(size, a, b, v1, v2, mod);
		}

		vector<vector<ll>> temp(3);
		for (int i = 0; i < 3; i++) {
			temp[i] = convolution_main(size, a, b, v1, v2, primes[i]);
		}

		vector<ll> ans(size * c, 0);
		for (int j = 0; j < size * c; j++) {
			ans[j] = garner(temp[0][j], temp[1][j], temp[2][j], mod);
		}

		return ans;
	}
	inline vector<double> convolution(vector<double>& v1, vector<double>& v2) {//	(誤差あるかもしれない)畳み込みを行う
		int s1 = v1.size(), s2 = v2.size();

		while (s1 > 0 && v1[s1 - 1] == 0) { s1--; }
		while (s2 > 0 && v2[s2 - 1] == 0) { s2--; }

		if (s1 == 0 || s2 == 0) {
			return {};
		}

		const int size = getConvolutionSize(s1, s2);
		const int a = (s1 + size - 1) / size;
		const int b = (s2 + size - 1) / size;
		const int c = a + b;

		const int N = size * 2;
		int n = 0;
		while ((1 << n) < N) { n++; }

		vector<complex<double>> temp(size * c, 0);
		vector<double> ans(size * c, 0);

		if (size <= 64) {
			for (int i = 0; i < s1; i++) {
				for (int j = 0; j < s2; j++) {
					ans[i + j] += v1[i] * v2[j];
				}
			}
		}
		else {
			vector<vector<complex<double>>> x_src(a), x_dest(a);
			vector<vector<complex<double>>> y_src(b), y_dest(b);
			vector<vector<complex<double>>> z_src(c - 1), z_dest(c - 1);

			for (int i = 0; i < a; i++) {
				x_src[i].resize(N, 0);
				x_dest[i].resize(N);
				for (int j = 0, k = i * size; j < size; j++, k++) {
					if (k >= s1) { break; }
					x_src[i][j] = v1[k];
				}
				fft(N, n, x_src[i], x_dest[i], false, true);
			}
			for (int i = 0; i < b; i++) {
				y_src[i].resize(N, 0);
				y_dest[i].resize(N);
				for (int j = 0, k = i * size; j < size; j++, k++) {
					if (k >= s2) { break; }
					y_src[i][j] = v2[k];
				}
				fft(N, n, y_src[i], y_dest[i], false, true);
			}
			for (int i = 0; i < c - 1; i++) {
				z_src[i].resize(N, 0);
				z_dest[i].resize(N);
			}

			for (int i = 0; i < a; i++) {
				for (int j = 0; j < b; j++) {
					for (int k = 0; k < N; k++) {
						z_src[i + j][k] += x_dest[i][k] * y_dest[j][k];
					}
				}
			}
			for (int i = 0; i < c - 1; i++) {
				fft(N, n, z_src[i], z_dest[i], true, true);
				int k = i * size;
				for (int j = 0; j < N; j++, k++) {
					temp[k] += z_dest[i][j];
				}
			}
			for (int i = 0; i < size * c; i++) {
				ans[i] = temp[i].real();
			}
		}

		return ans;
	}
};

int main() {
	convolutionClass C;
	int N, M; cin >> N >> M;

	const bool USE_COMPLEX = true;

	if (USE_COMPLEX) {//	複素数を使った畳み込み
		vector<double> A(N), B(M);

		for (int i = 0; i < N; i++) {
			cin >> A[i];
		}
		for (int i = 0; i < M; i++) {
			cin >> B[i];
		}

		pair<double*, int> p = C.convolution(A, B);//	畳み込み
		int size = p.second;//	サイズ取得(2^nじゃない場合もある)

		cout << "size = " << size << endl;

		for (int i = 0; i < size; i++) {
			cout << (ll)(p.first[i] + 0.5) << endl;
		}
	}
	else {//	誤差無し畳み込み
		vector<ll> A, B;

		for (int i = 0; i < N; i++) {
			ll a; cin >> a;
			A.push_back(a);
		}
		for (int i = 0; i < M; i++) {
			ll b; cin >> b;
			B.push_back(b);
		}

		pair<ll*, int> p = C.convolution(A, B);//	畳み込み
		int size = p.second;//	サイズ取得(2^nじゃない場合もある)

		cout << "size = " << size << endl;

		for (int i = 0; i < size; i++) {
			cout << p.first[i] << endl;
		}
	}

	return 0;
}
//////		検証用入力データ

//	入力例１
4 4
1 0 2 3
4 3 2 1


//	サイズが大きく異なる場合はブロックごとに処理が行われる
3 15
1 2 3
1 2 3 1 2 3 1 2 3 1 2 3 1 2 3


//	末尾に0が連続している場合は削って入力される
50 17
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
7 6 5 4 3 2 1 0 0 0 0 0 0 0 0 0 0

*/