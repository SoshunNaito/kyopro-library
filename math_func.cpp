/*
/////////////         ”Šw

ll gcd(ll a, ll b) {// Å‘åŒö–ñ”
	a = abs(a);
	b = abs(b);
	if (a == 0) { return b; }
	if (b == 0) { return a; }

	ll c;
	if (a < b) { c = a; a = b; b = c; }
	while (1) {
		a %= b;
		if (a == 0) { return b; }
		c = a; a = b; b = c;
	}
}

inline ll lcm(ll a, ll b) {// Å¬Œö”{”
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	if (a == 0) { return b; }
	if (b == 0) { return a; }
	ll x = a;
	x /= gcd(a, b);
	x *= b;
	return x;
}

ll mod_multi(ll a, ll b, ll n) {
	return (a * b) % n;
}
ll mod_pow(ll a, ll d, ll n) {
	a = a % n;

	if (d == 0) {
		return 1;
	}
	if (d == 1) {
		return a;
	}
	if (d % 2 == 0) {
		ll k = mod_pow(a, d / 2, n);
		return mod_multi(k, k, n);
	}
	else {
		ll k = mod_pow(a, d / 2, n);
		ll b = mod_multi(k, k, n);

		return mod_multi(b, a, n);
	}
}
bool miller_rabin(ll n, ll a) {
	ll d = n - 1;
	int p = 0;

	while (d % 2 == 0) {
		p++;
		d /= 2;
	}
	ll m = mod_pow(a, d, n);
	if (m == 1) {
		return true;
	}
	for (int i = 0; i < p; i++) {
		if (m == n - 1) {
			return true;
		}
		m = mod_multi(m, m, n);
	}
	return false;
}
bool isPrime(ll n) {// ‘f””»’è
	if (n <= 1) {
		return false;
	}

	ll primes[] = {
		2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113
	};

	for (int i = 0; i < 30; i++) {
		if (n % primes[i] == 0) { return false; }
	}
	if (n < 120) {
		return false;
	}

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
void getPrimeTable(int N, vector<ll>& dest) {// ‘f”‚Ì•\‚ğ“¾‚é
	N = N / 2;
	vector<bool> flag(N, true);
	flag[0] = false;

	for (int i = 1; i < N; i++) {
		if (flag[i] == true) {
			int n = 1 + i * 2;
			for (int j = i + n; j < N; j += n) {
				flag[j] = false;
			}
		}
	}
	dest = { 2 };
	for (int i = 0; i < N; i++) {
		if (flag[i] == true) {
			dest.push_back(1 + i * 2);
		}
	}
}
int* euler_phi_table(int n) {
	if (n < 0) { return NULL; }
	int* a = new int[n + 1];
	for (int i = 0; i <= n; i++) {
		a[i] = i;
	}
	for (int i = 2; i <= n; i++) {
		if (a[i] == i) {
			for (int j = i; j <= n; j += i) {
				a[j] = a[j] / i * (i - 1);
			}
		}
	}
	return a;
}

inline ll l_sqrt(ll n) {//	Œë·–³‚µãn‚ğŒvZ‚·‚é
	if (n <= 0) { return 0; }

	if (n > 256) {
		ll k = l_sqrt(n / 4) * 2;
		while ((k + 1) * (k + 1) <= n) { k++; }
		return k;
	}
	else {
		for (ll i = 16; i >= 1; i--) {
			if (i * i <= n) { return i; }
		}
	}
	return 0;
}
class primeFactorClass {//	‘fˆö”•ª‰ğ‚ğ‚·‚é
public:
	primeFactorClass() {
		factorNum = 0;
	}
	~primeFactorClass() {
		reset();
	}

	ll factorNum;// ‘fˆö”‚ÌŒÂ”
	vector<ll> prime;// ‘fˆö”
	vector<ll> degree;// Ÿ”

	void factorize(ll n) {// ‘fˆö”•ª‰ğ
		reset();
		if (n < 0) { n = -n; }
		if (n <= 1) { return; }

		if (n % 2 == 0) {
			factorNum++;
			prime.push_back(2);
			ll count = 0;
			while (n % 2 == 0) { count++; n /= 2; }
			degree.push_back(count);
		}

		ll M = l_sqrt(n) + 1;
		for (ll i = 3; i < M; i += 2) {
			if (n % i == 0) {
				factorNum++;
				prime.push_back(i);
				ll count = 0;
				while (n % i == 0) { count++; n /= i; }
				degree.push_back(count);
				M = l_sqrt(n) + 1;
				if (n == 1) { break; }
			}
		}

		if (n != 1) {
			factorNum++;
			prime.push_back(n);
			degree.push_back(1);
		}
	}

private:
	void reset() {
		factorNum = 0;
		prime.clear();
		degree.clear();
	}
};


//////		g—p—á
int main() {
	int N; cin >> N;
	int* x = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> x[i];
	}


	//	Å‘åŒö–ñ”gcdEÅ¬Œö”{”lcm‚ÌŒvZ

	cout << "gcd(12, 18) = " << gcd(12, 18) << ", lcm(12, 18) = " << lcm(12, 18) << endl;
	cout << "gcd(432, 234) = " << gcd(432, 234) << ", lcm(432, 234) = " << lcm(432, 234) << endl;
	cout << endl;
	cout << "gcd(N, x) = " << gcd(N, x) << ", lcm(N, x) = " << lcm(N, x) << endl;
	cout << endl;


	//	‘fˆö”•ª‰ğ

	primeFactorClass p;
	p.factorize(3628800);

	cout << "3628800 = ";
	for (int i = 0; i < p.factorNum; i++) {//	o—Í
		if (i == 0) {
			cout << p.prime[i] << "^" << p.degree[i];
		}
		else {
			cout << " * "<< p.prime[i] << "^" << p.degree[i];
		}
	}

	return 0;
}

//////		ŒŸØ—p“ü—Íƒf[ƒ^
3
56 84 126




*/