/*
/////////////         modの計算

int mod = 1000000007;

long long mod_adjust(long long a) {
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
int mod_adjust(int a) {
	return (int)mod_adjust((long long)a);
}
int mod_add(int a, int b) {
	a = mod_adjust(a), b = mod_adjust(b);
	long long k = a % mod; k += b % mod; k %= mod;
	return (int)k;
}
int mod_sub(int a, int b) {
	long long k = mod_adjust((long long)a); k += mod_adjust((long long)b); k %= mod;
	return (int)k;
}
int mod_multi(int a, int b) {
	long long k = mod_adjust((long long)a); k *= mod_adjust((long long)b); k %= mod;
	return (int)k;
}
int mod_inv(int a) {
	a = mod_adjust(a);
	if (a == 1) { return 1; }
	long long p = mod, q = a, m = 0, n = 1, r, c;

	while (q > 1) {
		r = p % q;
		c = p/q;
		c = mod_adjust(m - n * c);
		p = q, m = n, q = r, n = c;
	}
	return n;
}
int mod_div(int a, int b) {
	return mod_multi(a, mod_inv(b));
}
int mod_pow(int x, int n) {
	if (n < 0) {
		return mod_pow(mod_div(1, x), -n);
	}
	if (n == 0) {
		return 1;
	}
	if (n == 1) {
		return x;
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
int *factorial;
int *factorial_inv;
void calc_factorial(int N) {////////////////////////// 初めに必ず呼び出すこと！！！
	factorial = new int[N + 1];
	factorial_inv = new int[N + 1];

	factorial[0] = 1;
	factorial_inv[0] = 1;
	for (int i = 1; i <= N; i++) {
		factorial[i] = mod_multi(factorial[i - 1], i);
		factorial_inv[i] = mod_inv(factorial[i]);
	}
}
int mod_combination(int n, int r) {
	return mod_multi(factorial[n], mod_multi(factorial_inv[n - r], factorial_inv[r]));
}




*/