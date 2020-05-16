/*
/////////////         mod‚ÌŒvŽZ

#define MOD_IS_PRIME
const ll mod = 1000000007LL;

class modlong {
public:
	modlong() {
		x = 0;
	}
	modlong(ll num) {
		x = adjust(num);
	}
	inline operator ll() const {
		return x;
	}
	inline bool operator ==(ll num) {
		return this->x == num;
	}
	inline bool operator !=(ll num) {
		return !(*this == num);
	}
	inline void operator = (ll num) {
		x = adjust(num);
	}
	inline void operator += (ll num) {
		x = adjust(x + num);
	}
	inline void operator ++() {
		this->operator+=(1);
	}
	inline modlong operator + (ll num) const {
		modlong m(this->x);
		m += num;
		return m;
	}
	inline void operator -= (ll num) {
		x = adjust(x - num);
	}
	inline void operator --() {
		this->operator-=(1);
	}
	inline modlong operator - (ll num) {
		modlong m(this->x);
		m -= num;
		return m;
	}
	inline void operator *= (ll num) {
		x = adjust(x * num);
	}
	inline modlong operator * (ll num) {
		modlong m(this->x);
		m *= num;
		return m;
	}
	inline void operator /=(ll num);
	inline modlong operator /(ll num);
private:
	inline ll adjust(ll a) {
		if (a >= mod) {
			return a % mod;
		}
		if (a < 0) {
			return mod - 1 + ((a + 1) % mod);
		}
		return a;
	}
	ll x;
};

inline modlong mod_inv(modlong a) {
	const ll inv_max = 300000;
	static vector<ll> inv;
	ll k = a;
	assert(k > 0);

	if (k <= inv_max) {
		ll M = inv.size();
		if (M <= k) {
			if (M == 0) { inv.push_back(0); M++; }
			if (M == 1) { inv.push_back(1); M++; }

			for (ll i = M; i <= k; i++) {
				ll p = mod / i;
				ll q = mod - (p * i);
				inv.push_back(((mod - p) * inv[q]) % mod);
			}
		}
		return inv[k];
	}

	ll p = mod, q = k;
	modlong m = 0, n = 1, r, c;

	ll s = inv.size();
	while (q > 1) {
		if (q < s) {
			return n * inv[q];
		}
		c = p / q;
		r = p - (q * c);
		c = m - n * c;
		p = q, m = n, q = r, n = c;
	}
	return n;
}
inline modlong mod_div(modlong a, modlong b) {
	return a * mod_inv(b);
}
inline void modlong::operator /=(ll num) {
	x = mod_div(*this, num);
}
inline modlong modlong::operator /(ll num) {
	modlong m(this->x);
	m /= num;
	return m;
}

inline modlong mod_pow(modlong x, ll n) {
	if (n < 0) {
		x = mod_inv(x);
		n = -n;
	}

#ifdef MOD_IS_PRIME
	n = n % (mod - 1);
#endif

	modlong temp = x, ans = 1;
	while (n > 0) {
		if (n & 1) {
			ans *= temp;
		}
		temp *= temp;
		n >>= 1;
	}
	return ans;
}
inline modlong mod_log(modlong a, modlong x) {
	ll A = sqrt(mod);
	ll B = (mod + A - 1) / A;
	map<ll, ll> mp1, mp2;
	ll p0 = a;
	ll q0 = mod_pow(a, -A);
	ll p = 1;
	ll q = x;
	for (int i = 0; i < A; i++) {
		mp1.insert({ p, i });
		p = (p * p0) % mod;
	}
	for (int i = 0; i < B; i++) {
		mp2.insert({ q, A * i });
		q = (q * q0) % mod;
	}
	auto itr1 = mp1.begin();
	auto itr2 = mp2.begin();
	while (itr1 != mp1.end() && itr2 != mp2.end()) {
		if (itr1->first < itr2->first) {
			itr1++;
		}
		else if (itr1->first == itr2->first) {
			return itr1->second + itr2->second;
		}
		else {
			itr2++;
		}
	}
	return 0;
}

inline modlong mod_factorial(modlong n, bool inverse = false) {
	static vector<ll> factorial, factorial_inv;

	ll M = factorial.size();
	if (M <= n) {
		if (M == 0) { factorial.push_back(1); factorial_inv.push_back(1); M++; }
		if (M == 1) { factorial.push_back(1); factorial_inv.push_back(1); M++; }

		for (ll i = M; i <= n; i++) {
			factorial.push_back((factorial.back() * i) % mod);
			factorial_inv.push_back((factorial_inv.back() * mod_inv(i)) % mod);
		}
	}
	if (inverse == true) {
		return factorial_inv[n];
	}
	else {
		return factorial[n];
	}
}
inline modlong mod_combination(modlong n, modlong r) {
	assert(r <= n);
	return mod_factorial(n) * mod_factorial(n - r, true) * mod_factorial(r, true);
}

int main() {
	for (int i = 0; i < 10; i++) {
		cout << "256^" << i << " = " << mod_pow(256, i) << endl;//	—Ýæ
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << i << "^-1 = " << mod_inv(i) << endl;//	‹tŒ³
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << 10 << "C" << i << " = " << mod_combination(10, i) << endl;//	“ñ€ŒW”
	}

	return 0;
}



*/