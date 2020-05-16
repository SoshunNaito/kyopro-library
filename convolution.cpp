/*
class convolutionClass {// 畳み込み
private:
	const ll prime0 = 167772161;
	const ll prime1 = 469762049;
	const ll prime2 = 1224736769;
	ll temporary_ans[3] = {//	garnerに入れる用のバッファ
		0,
		0,
		0
	};
	inline ll mod_inv(ll a, ll p) {//	逆元
		ll k = a % p;
		if (k == 0) { return 0; }
		if (k == 1) { return 1; }
		ll s = p, t = k, m = 0, n = 1, r, c;

		while (t > 1) {
			r = s % t;
			c = s / t;
			c = ((m - n * c) % p + p) % p;
			s = t, m = n, t = r, n = c;
		}
		return n % p;
	}
	inline ll mod_pow(ll x, ll n, ll p) {//	累乗
		x = x % p;
		if (n < 0) {
			return mod_pow(mod_inv(x, p), -n, p);
		}
		if (n == 0) {
			return 1;
		}
		if (n == 1) {
			return x;
		}
		if (n % 2 == 0) {
			ll k = mod_pow(x, n / 2, p);
			return (k * k) % p;
		}
		else {
			ll k = mod_pow(x, n / 2, p);
			return (((k * k) % p) * x) % p;
		}
	}
	inline ll garner(ll mod) {//	garnerのアルゴリズム
		ll c0 = temporary_ans[0] % prime0;
		ll c1 = ((temporary_ans[1] - c0 + prime1) % prime1 * mod_inv(prime0, prime1)) % prime1;
		ll c2 = ((((temporary_ans[2] - c0 - c1 * prime0) % prime2 + prime2) % prime2 * mod_inv(prime0 * prime1, prime2))) % prime2;

		return ((c2 * prime1 + c1) % mod * prime0 + c0) % mod;
	}
	inline void fft(int N, int n, ll** src, ll** dest, bool inverse = false) {//	各素数についてFFTを行う
		{
			int* rate = new int[n];
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
				dest[sum][0] = src[i][0] % prime0;
				dest[sum][1] = src[i][1] % prime1;
				dest[sum][2] = src[i][2] % prime2;
			}
			delete[] rate;
		}

		ll** base = new ll*[n];
		for (int i = 0; i < n; i++) { base[i] = new ll[3]; }
		if (inverse == true) {
			base[n - 1][0] = mod_pow(3, -(prime0 - 1) / N, prime0);
			base[n - 1][1] = mod_pow(3, -(prime1 - 1) / N, prime1);
			base[n - 1][2] = mod_pow(3, -(prime2 - 1) / N, prime2);
		}
		else {
			base[n - 1][0] = mod_pow(3, (prime0 - 1) / N, prime0);
			base[n - 1][1] = mod_pow(3, (prime1 - 1) / N, prime1);
			base[n - 1][2] = mod_pow(3, (prime2 - 1) / N, prime2);
		}
		for (int i = n - 2; i >= 0; i--) {
			base[i][0] = (base[i + 1][0] * base[i + 1][0]) % prime0;
			base[i][1] = (base[i + 1][1] * base[i + 1][1]) % prime1;
			base[i][2] = (base[i + 1][2] * base[i + 1][2]) % prime2;
		}

		int m = 1;
		for (int layer = 0; layer < n; layer++) {
			m *= 2;
			int M = N / m;
			int h = m / 2;
			int L = 0, R = h, block, i;
			ll w0, w1, w2, p0, p1, p2, q0, q1, q2;
			for (block = 0; block < M; block++) {
				w0 = 1;
				w1 = 1;
				w2 = 1;

				for (i = 0; i < h; i++, L++, R++) {
					p0 = dest[L][0];
					p1 = dest[L][1];
					p2 = dest[L][2];

					q0 = (dest[R][0] * w0) % prime0;
					q1 = (dest[R][1] * w1) % prime1;
					q2 = (dest[R][2] * w2) % prime2;

					dest[L][0] = p0 + q0;
					dest[L][1] = p1 + q1;
					dest[L][2] = p2 + q2;

					dest[R][0] = p0 - q0;
					dest[R][1] = p1 - q1;
					dest[R][2] = p2 - q2;

					w0 = (w0 * base[layer][0]) % prime0;
					w1 = (w1 * base[layer][1]) % prime1;
					w2 = (w2 * base[layer][2]) % prime2;

					if (dest[L][0] > prime0) { dest[L][0] -= prime0; }
					if (dest[L][1] > prime1) { dest[L][1] -= prime1; }
					if (dest[L][2] > prime2) { dest[L][2] -= prime2; }

					if (dest[R][0] < 0) { dest[R][0] += prime0; }
					if (dest[R][1] < 0) { dest[R][1] += prime1; }
					if (dest[R][2] < 0) { dest[R][2] += prime2; }
				}
				L += h;
				R += h;
			}
		}
		for (int i = 0; i < n; i++) { delete[] base[i]; }
		delete[] base;

		if (inverse == true) {
			ll M0 = mod_inv(N, prime0);
			ll M1 = mod_inv(N, prime1);
			ll M2 = mod_inv(N, prime2);

			for (int i = 0; i < N; i++) {
				dest[i][0] = (dest[i][0] * M0) % prime0;
				dest[i][1] = (dest[i][1] * M1) % prime1;
				dest[i][2] = (dest[i][2] * M2) % prime2;
			}
		}
	}
	inline void fft(int N, int n, complex<ll>* src, complex<ll>* dest, bool inverse = false) {//	複素数を使ったFFTを行う
		{
			int* rate = new int[n];
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
			delete[] rate;
		}

		complex<ll>* base = new complex<ll>[n];
		if (inverse == true) {
			for (int i = 0; i < n; i++) {
				int j = 1 << (i + 1);
				base[i] = polar(1.0, 2.0 * acos(-1.0) / j);
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				int j = 1 << (i + 1);
				base[i] = polar(1.0, -2.0 * acos(-1.0) / j);
			}
		}

		int m = 1;
		for (int layer = 0; layer < n; layer++) {
			m *= 2;
			int M = N / m;
			int h = m / 2;
			int L = 0, R = h, block, i;
			complex<ll> p, q, w;
			for (block = 0; block < M; block++) {
				w = 1.0;

				for (i = 0; i < h; i++, L++, R++) {
					p = dest[L];
					q = dest[R] * w;

					dest[L] = p + q;
					dest[R] = p - q;

					w *= base[layer];
				}
				L += h;
				R += h;
			}
		}
		delete[] base;

		if (inverse == true) {
			for (int i = 0; i < N; i++) {
				dest[i] /= N;
			}
		}
	}
	inline int getConvolutionSize(int x, int y) {// サイズの組からブロックサイズを得る
		int i = 1;
		int j = min(x, y);
		while (i < j) { i <<= 1; }
		return i;
	}
public:
	inline pair<ll*, int> convolution(vector<ll>& v1, vector<ll>& v2, ll mod = 1LL << 30) {// (誤差無し)畳み込みを行う
		int s1 = v1.size(), s2 = v2.size();

		while (s1 > 0 && v1[s1 - 1] == 0) { s1--; }
		while (s2 > 0 && v2[s2 - 1] == 0) { s2--; }

		if (s1 == 0 || s2 == 0) {
			return make_pair((ll*)NULL, 0);
		}

		int size = getConvolutionSize(s1, s2);
		int a = (s1 + size - 1) / size;
		int b = (s2 + size - 1) / size;
		int c = a + b;

		ll** ans = new ll*[size * c];
		for (int i = 0; i < (size * c); i++) {
			ans[i] = new ll[3];
			ans[i][0] = 0;
			ans[i][1] = 0;
			ans[i][2] = 0;
		}

		vector<ll**> x_src, y_src;
		vector<ll**> x_dest, y_dest;

		for (int i = 0; i < a; i++) {
			ll** buf = new ll * [size * 2];
			ll** dest = new ll * [size * 2];
			int k, l;
			for (int j = 0; j < size; j++) {
				k = j + size;
				l = i * size + j;

				buf[j] = new ll[3];
				buf[k] = new ll[3];
				dest[j] = new ll[3];
				dest[k] = new ll[3];
				if (l < s1) {
					buf[j][0] = v1[l];
					buf[j][1] = v1[l];
					buf[j][2] = v1[l];
				}
				else {
					buf[j][0] = 0;
					buf[j][1] = 0;
					buf[j][2] = 0;
				}
				buf[k][0] = 0;
				buf[k][1] = 0;
				buf[k][2] = 0;
			}
			x_src.push_back(buf);
			x_dest.push_back(dest);
		}

		for (int i = 0; i < b; i++) {
			ll** buf = new ll * [size * 2];
			ll** dest = new ll * [size * 2];
			int k, l;
			for (int j = 0; j < size; j++) {
				k = j + size;
				l = i * size + j;

				buf[j] = new ll[3];
				buf[k] = new ll[3];
				dest[j] = new ll[3];
				dest[k] = new ll[3];
				if (l < s2) {
					buf[j][0] = v2[l];
					buf[j][1] = v2[l];
					buf[j][2] = v2[l];
				}
				else {
					buf[j][0] = 0;
					buf[j][1] = 0;
					buf[j][2] = 0;
				}
				buf[k][0] = 0;
				buf[k][1] = 0;
				buf[k][2] = 0;
			}
			y_src.push_back(buf);
			y_dest.push_back(dest);
		}

		int N = size * 2;
		int n = 0;
		while ((1 << n) < N) { n++; }

		for (int i = 0; i < a; i++) {
			fft(N, n, x_src[i], x_dest[i]);
		}

		for (int i = 0; i < b; i++) {
			fft(N, n, y_src[i], y_dest[i]);
		}

		vector<ll**> z_src, z_dest;
		for (int i = 0; i < c - 1; i++) {
			ll** src = new ll * [N];
			ll** dest = new ll * [N];
			for (int j = 0; j < N; j++) {
				src[j] = new ll[3];
				dest[j] = new ll[3];
				src[j][0] = 0;
				src[j][1] = 0;
				src[j][2] = 0;
			}
			z_src.push_back(src);
			z_dest.push_back(dest);
		}

		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				ll** ptr1 = x_dest[i];
				ll** ptr2 = y_dest[j];
				ll** ptr3 = z_src[i + j];
				for (int k = 0; k < N; k++) {
					ptr3[k][0] += ptr1[k][0] * ptr2[k][0];
					ptr3[k][1] += ptr1[k][1] * ptr2[k][1];
					ptr3[k][2] += ptr1[k][2] * ptr2[k][2];
				}
			}
		}

		for (int i = 0; i < c - 1; i++) {
			fft(N, n, z_src[i], z_dest[i], true);
			int k = i * size;
			for (int j = 0; j < N; j++, k++) {
				ans[k][0] += z_dest[i][j][0];
				ans[k][1] += z_dest[i][j][1];
				ans[k][2] += z_dest[i][j][2];
			}
		}

		ll* r = new ll[size * c];
		for (int i = 0; i < size * c; i++) {
			temporary_ans[0] = ans[i][0];
			temporary_ans[1] = ans[i][1];
			temporary_ans[2] = ans[i][2];
			delete[] ans[i];
			r[i] = garner(mod);
		}

		delete[] ans;

		for (int j = 0; j < N; j++) {
			for (int i = 0; i < a; i++) {
				delete[] x_src[i][j];
				delete[] x_dest[i][j];
			}
			for (int i = 0; i < b; i++) {
				delete[] y_src[i][j];
				delete[] y_dest[i][j];
			}
			for (int i = 0; i < c - 1; i++) {
				delete[] z_src[i][j];
				delete[] z_dest[i][j];
			}
		}
		for (int i = 0; i < a; i++) {
			delete[] x_src[i];
			delete[] x_dest[i];
		}
		for (int i = 0; i < b; i++) {
			delete[] y_src[i];
			delete[] y_dest[i];
		}
		for (int i = 0; i < c - 1; i++) {
			delete[] z_src[i];
			delete[] z_dest[i];
		}

		return make_pair(r, size * c);
	}
	inline pair<ll*, int> convolution(vector<ll>& v1, vector<ll>& v2) {//	(誤差あるかもしれない)畳み込みを行う
		int s1 = v1.size(), s2 = v2.size();

		while (s1 > 0 && v1[s1 - 1] == 0) { s1--; }
		while (s2 > 0 && v2[s2 - 1] == 0) { s2--; }

		if (s1 == 0 || s2 == 0) {
			return make_pair((ll*)NULL, 0);
		}

		int size = getConvolutionSize(s1, s2);
		int a = (s1 + size - 1) / size;
		int b = (s2 + size - 1) / size;
		int c = a + b;

		complex<ll>* temp = new complex<ll>[size * c];
		ll* ans = new ll[size * c];
		for (int i = 0; i < (size * c); i++) {
			temp[i] = 0;
			ans[i] = 0;
		}

		vector<complex<ll>*> x_src, y_src;
		vector<complex<ll>*> x_dest, y_dest;

		for (int i = 0; i < a; i++) {
			complex<ll>* buf = new complex<ll>[size * 2];
			complex<ll>* dest = new complex<ll>[size * 2];
			int k, l;
			for (int j = 0; j < size; j++) {
				k = j + size;
				l = i * size + j;
				if (l < s1) {
					buf[j] = v1[l];
				}
				else {
					buf[j] = 0;
				}
				buf[k] = 0;
			}
			x_src.push_back(buf);
			x_dest.push_back(dest);
		}

		for (int i = 0; i < b; i++) {
			complex<ll>* buf = new complex<ll>[size * 2];
			complex<ll>* dest = new complex<ll>[size * 2];
			int k, l;
			for (int j = 0; j < size; j++) {
				k = j + size;
				l = i * size + j;
				if (l < s2) {
					buf[j] = v2[l];
				}
				else {
					buf[j] = 0;
				}
				buf[k] = 0;
			}
			y_src.push_back(buf);
			y_dest.push_back(dest);
		}

		int N = size * 2;
		int n = 0;
		while ((1 << n) < N) { n++; }

		for (int i = 0; i < a; i++) {
			fft(N, n, x_src[i], x_dest[i]);
		}

		for (int i = 0; i < b; i++) {
			fft(N, n, y_src[i], y_dest[i]);
		}

		vector<complex<ll>*> z_src, z_dest;
		for (int i = 0; i < c - 1; i++) {
			complex<ll>* src = new complex<ll>[N];
			complex<ll>* dest = new complex<ll>[N];

			for (int j = 0; j < N; j++) {
				src[j] = 0;
				dest[j] = 0;
			}
			z_src.push_back(src);
			z_dest.push_back(dest);
		}

		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				for (int k = 0; k < N; k++) {
					z_src[i + j][k] += x_dest[i][k] * y_dest[j][k];
				}
			}
		}

		for (int i = 0; i < c - 1; i++) {
			fft(N, n, z_src[i], z_dest[i], true);
			int k = i * size;
			for (int j = 0; j < N; j++, k++) {
				temp[k] += z_dest[i][j];
			}
		}

		for (int i = 0; i < size * c; i++) {
			ans[i] = temp[i].real();
		}
		delete[] temp;

		for (int i = 0; i < a; i++) {
			delete[] x_src[i];
			delete[] x_dest[i];
		}
		for (int i = 0; i < b; i++) {
			delete[] y_src[i];
			delete[] y_dest[i];
		}
		for (int i = 0; i < c - 1; i++) {
			delete[] z_src[i];
			delete[] z_dest[i];
		}

		return make_pair(ans, size * c);
	}
};

int main(){
	convolutionClass C;
	int N, M; cin >> N >> M;

	const bool USE_COMPLEX = false;

	if (USE_COMPLEX) {//	複素数を使った畳み込み
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