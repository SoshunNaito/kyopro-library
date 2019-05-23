/*
/////////////         mod‚ÌŒvZ

int mod = 1000000007;

long long mod_adjust(long long a) {//	—]‚è‚ğ‚Æ‚é(0`mod-1‚É’²®‚·‚é)
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
int mod_adjust(int a) {//	—]‚è‚ğ‚Æ‚é(0`mod-1‚É’²®‚·‚é)
	return (int)mod_adjust((long long)a);
}
int mod_add(int a, int b) {//	‘«‚µZ
	a = mod_adjust(a), b = mod_adjust(b);
	long long k = a % mod; k += b % mod; k %= mod;
	return (int)k;
}
int mod_sub(int a, int b) {//	ˆø‚«Z
	long long k = mod_adjust((long long)a); k += mod_adjust((long long)b); k %= mod;
	return (int)k;
}
int mod_multi(int a, int b) {//	Š|‚¯Z
	long long k = mod_adjust((long long)a); k *= mod_adjust((long long)b); k %= mod;
	return (int)k;
}
int mod_inv(int a) {//	‹tŒ³
	a = mod_adjust(a);
	if (a == 1) { return 1; }
	long long p = mod, q = a, m = 0, n = 1, r, c;

	while (q > 1) {
		r = p % q;
		c = p / q;
		c = mod_adjust(m - n * c);
		p = q, m = n, q = r, n = c;
	}
	return n;
}
int mod_div(int a, int b) {//	Š„‚èZ
	return mod_multi(a, mod_inv(b));
}
int mod_pow(int x, int n) {//	—İæ(logNƒI[ƒ_[‚È‚Ì‚Å‘¬‚¢)
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

int* factorial = NULL;			//	ŠKæ
int* factorial_inv = NULL;		//	ŠKæ‚Ì‹tŒ³

//	ŠKæ‚ğ–‘O‚ÉŒvZ‚µ‚Ä‚¨‚­ŠÖ”B
//	N‚Ímod_combination(n, r)‚ÅŒÄ‚Ño‚³‚ê‚¤‚éÅ‘å‚Ì”B
void calc_factorial(int N) {////////////////////////// ‰‚ß‚É•K‚¸ŒÄ‚Ño‚·‚±‚ÆIII
	factorial = new int[N + 1];
	factorial_inv = new int[N + 1];

	factorial[0] = 1;
	factorial_inv[0] = 1;
	for (int i = 1; i <= N; i++) {
		factorial[i] = mod_multi(factorial[i - 1], i);
		factorial_inv[i] = mod_inv(factorial[i]);
	}
}
int mod_combination(int n, int r) {//	nCr	‚ğŒvZ‚·‚é
	if (n < 0 || r < 0 || r > n) { return 0; }
	return mod_multi(factorial[n], mod_multi(factorial_inv[n - r], factorial_inv[r]));
}


//////		g—p—á
int main() {
	calc_factorial(100);//	mod_combination‚ğg‚¤‚½‚ß‚Ì–‘O€”õ

	for (int i = 0; i < 10; i++) {
		cout << "256^" << i << " = " << mod_pow(256, i) << endl;//	—İæ
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i << "^-1 = " << mod_inv(i) << endl;//	‹tŒ³
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << 10 << "C" << i <<" = " << mod_combination(10, i) << endl;//	“ñ€ŒW”
	}

	return 0;
}



*/