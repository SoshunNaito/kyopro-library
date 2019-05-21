/*
/////////////         ”Šw

template <typename T>
T gcd(T a, T b) {
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	if (a == 0) { return b; }
	if (b == 0) { return a; }
	if (a < b) {
		return gcd(a, b % a);
	}
	return gcd(b, a % b);
}
template <typename T>
T gcd(int size, T* a) {
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
long lcm(int a, int b) {
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	if (a == 0) { return b; }
	if (b == 0) { return a; }
	long x = a;
	x /= gcd(a, b);
	x *= b;
	return x;
}
long lcm(long a, long b) {
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }
	if (a == 0) { return b; }
	if (b == 0) { return a; }
	a /= gcd(a, b);
	a *= b;
	return a;
}
template <typename T>
long lcm(int size, T* a) {
	if (size <= 0 || a == NULL) { return 0; }
	long c = abs(a[0]);
	for (int i = 1; i < size; i++) {
		c = lcm(c, a[i]);
	}
	return c;
}

long l_sqrt(long n) {// (long)ãn ‚ğŒvZ‚·‚é
	if (n <= 0) { return 0; }

	if (n > 256) {
		long k = l_sqrt(n / 4) * 2;
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
class primeFactorClass {// ‘fˆö”•ª‰ğ‚ğ‚·‚é
public:
	primeFactorClass() {
		factorNum = 0;
	}
	~primeFactorClass() {
		reset();
	}

	int factorNum;// ‘fˆö”‚ÌŒÂ”
	vector<long> prime;// ‘fˆö”
	vector<int> degree;// Ÿ”

	void factorize(long n) {// ‘fˆö”•ª‰ğ
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

		long M = l_sqrt(n) + 1;
		for (long i = 3; i < M; i += 2) {
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




*/