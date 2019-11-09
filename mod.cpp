/*
/////////////         modの計算

int mod = 1000000007;

ll mod_adjust(ll a) {//	余りをとる(0〜mod-1に調整する)
	if (a > mod) {
		return a % mod;
	}
	if (a < 0) {
		a *= -1;
		a %= mod;
		return mod - a;
	}
	return a;
}
int mod_add(int a, int b) {//	足し算
	ll k = mod_adjust((ll)a); k += mod_adjust((ll)b);
	k = mod_adjust(k);
	return (int)k;
}
int mod_sub(int a, int b) {//	引き算
	return mod_add(a, -b);
}
int mod_multi(int a, int b) {//	掛け算
	ll k = mod_adjust((ll)a);
	k *= mod_adjust((ll)b);
	k = mod_adjust(k);
	return (int)k;
}
int mod_inv(int a) {//	逆元
	ll k = (int)mod_adjust((ll)a);
	if (k == 0) { return 0; }
	if (k == 1) { return 1; }
	ll p = mod, q = k, m = 0, n = 1, r, c;

	while (q > 1) {
		r = p % q;
		c = p / q;
		c = mod_adjust(m - n * c);
		p = q, m = n, q = r, n = c;
	}
	return (int)mod_adjust(n);
}
int mod_div(int a, int b) {//	割り算
	return mod_multi(a, mod_inv(b));
}
int mod_pow(int x, int n) {//	累乗(logNオーダーなので速い)
	x = (int)mod_adjust((ll)x);
	n = n % (mod - 1);
	if (n < 0) {
		return mod_pow(mod_div(1, x), -n);
	}
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return (int)mod_adjust((ll)x);
	}
	if (n % 2 == 0) {
		int k = mod_pow(x, n / 2);
		return mod_multi(k, k);
	}
	else {
		int k = mod_pow(x, n / 2);
		return mod_multi(mod_multi(k, k), x);
	}
}

int* factorial = NULL;			//	階乗
int* factorial_inv = NULL;		//	階乗の逆元

//	階乗を事前に計算しておく関数。
//	Nはmod_combination(n, r)で呼び出されうる最大の数。
void calc_factorial(int N) {////////////////////////// 初めに必ず呼び出すこと！！！
	N = min(mod - 1, N);
	factorial = new int[N + 1];
	factorial_inv = new int[N + 1];

	factorial[0] = 1;
	factorial_inv[0] = 1;
	for (int i = 1; i <= N; i++) {
		factorial[i] = mod_multi(factorial[i - 1], i);
		factorial_inv[i] = mod_inv(factorial[i]);
	}
}
int mod_combination(int n, int r) {//	nCr	を計算する
	if (n < 0 || r < 0 || r > n) { return 0; }
	if (n >= mod) { return 0; }
	if (r < 0) { return 0; }
	return mod_multi(factorial[n], mod_multi(factorial_inv[n - r], factorial_inv[r]));
}

int main() {
	calc_factorial(100);//	mod_combinationを使うための事前準備

	for (int i = 0; i < 10; i++) {
		cout << "256^" << i << " = " << mod_pow(256, i) << endl;//	累乗
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i << "^-1 = " << mod_inv(i) << endl;//	逆元
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << 10 << "C" << i << " = " << mod_combination(10, i) << endl;//	二項係数
	}

	return 0;
}



*/