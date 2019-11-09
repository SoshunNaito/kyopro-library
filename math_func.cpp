/*
/////////////         ���w

template <typename T>//	T��int��ll
T gcd(T a, T b) {//	�ő����
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	if (a == 0) { return b; }
	if (b == 0) { return a; }
	if (a < b) {
		return gcd(a, b % a);
	}
	return gcd(b, a % b);
}
template <typename T>//	T��int��ll
T gcd(int size, T* a) {//	�z��̍ő����
	if (size <= 0 || a == NULL) { return 0; }
	T c = abs(a[0]);
	for (int i = 1; i < size; i++) {
		c = gcd(c, a[i]);
		if (c == 1) {
			break;
		}
	}
	return c;
}

template <typename T>//	T��int��ll
ll lcm(T a, T b) {//	�ŏ����{��
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	if (a == 0) { return b; }
	if (b == 0) { return a; }
	ll x = a;
	x /= gcd(a, b);
	x *= b;
	return x;
}
template <typename T>//	T��int��ll
ll lcm(int size, T* a) {//	�z��̍ŏ����{��
	if (size <= 0 || a == NULL) { return 0; }
	ll c = abs(a[0]);
	for (int i = 1; i < size; i++) {
		c = lcm(c, (ll)a[i]);
	}
	return c;
}

int mod_multi(int a, int b, int n) {
	ll A = a; ll B = b;
	return (int)((A * B) % n);
}
int mod_pow(int a, int d, int n) {
	a = a % n;

	if (d == 0) {
		return 1;
	}
	if (d == 1) {
		return a;
	}
	if (d % 2 == 0) {
		int k = mod_pow(a, d / 2, n);
		return mod_multi(k, k, n);
	}
	else {
		int k = mod_pow(a, d / 2, n);
		int b = mod_multi(k, k, n);

		return mod_multi(b, a, n);
	}
}
bool miller_rabin(int n, int a) {
	int d = n - 1;
	int p = 0;

	while (d % 2 == 0) {
		p++;
		d /= 2;
	}
	int m = mod_pow(a, d, n);
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
bool isPrime(int n) {
	if (n <= 1) {
		return false;
	}

	int primes[] = {
		2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113
	};

	if (n < 120) {
		for (int i = 0; i < 30; i++) {
			if (n == primes[i]) { return true; }
		}
		return false;
	}
	for (int i = 0; i < 30; i++) {
		if (n % primes[i] == 0) { return false; }
	}

	int k = 0;
	if (n < 2047) { k = 1; }
	else if (n < 1373653) { k = 2; }
	else if (n < 25326001) { k = 3; }
	else { k = 4; }

	for (int i = 0; i < k; i++) {
		if (miller_rabin(n, primes[i]) == false) {
			return false;
		}
	}

	return true;
}

//	(ll)��n ���v�Z����BO(logn)�Ōv�Z���邩�瑬����
//	���� double sqrt(double x) ���g�����������������ǁA�v�Z�덷���C�ɂȂ�...
//	l_sqrt�͐����̂܂܌v�Z���Ă邩��덷�̐S�z�͂Ȃ���
ll l_sqrt(ll n) {
	if (n <= 0) { return 0; }

	if (n > 256) {
		ll k = l_sqrt(n / 4) * 2;
		while ((k + 1) * (k + 1) <= n) { k++; }
		return k;
	}
	else {
		for (int i = 16; i >= 1; i--) {
			if (i * i <= n) { return i; }
		}
	}
	return 0;
}
class primeFactorClass {// �f��������������
public:
	primeFactorClass() {
		factorNum = 0;
	}
	~primeFactorClass() {
		reset();
	}

	int factorNum;// �f�����̌�
	vector<ll> prime;// �f����
	vector<int> degree;// ����

	void factorize(ll n) {// �f��������
		reset();
		if (n < 0) { n = -n; }
		if (n <= 1) { return; }

		if (n % 2 == 0) {
			factorNum++;
			prime.push_back(2);
			int count = 0;
			while (n % 2 == 0) { count++; n /= 2; }
			degree.push_back(count);
		}

		ll M = l_sqrt(n) + 1;
		for (ll i = 3; i < M; i += 2) {
			if (n % i == 0) {
				factorNum++;
				prime.push_back(i);
				int count = 0;
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


//////		�g�p��
int main() {
	int N; cin >> N;
	int* x = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> x[i];
	}


	//	�ő����gcd�E�ŏ����{��lcm�̌v�Z

	cout << "gcd(12, 18) = " << gcd(12, 18) << ", lcm(12, 18) = " << lcm(12, 18) << endl;
	cout << "gcd(432, 234) = " << gcd(432, 234) << ", lcm(432, 234) = " << lcm(432, 234) << endl;
	cout << endl;
	cout << "gcd(N, x) = " << gcd(N, x) << ", lcm(N, x) = " << lcm(N, x) << endl;
	cout << endl;


	//	�f��������

	primeFactorClass p;
	p.factorize(3628800);

	cout << "3628800 = ";
	for (int i = 0; i < p.factorNum; i++) {//	�o��
		if (i == 0) {
			cout << p.prime[i] << "^" << p.degree[i];
		}
		else {
			cout << " * "<< p.prime[i] << "^" << p.degree[i];
		}
	}

	return 0;
}

//////		���ؗp���̓f�[�^
3
56 84 126




*/