#include <iostream>

using namespace std;

///////     longをmodの計算をするように拡張

#define MOD (long)(1e9 + 7)
#define MAX 1000000  // 階乗をいくつまで計算するか

class modlong;
void computeAll(long n);
modlong modComb(long n, long k);
modlong modFact(long n);

class modlong {
    long val;
    const long mod = MOD;

public:
    // 初期化 値を引数に与えなかった場合はval=0としておく
    modlong(long init = 0) {
        while (init < 0) init += mod;  // 0以上であることを保証
        val = init % mod;
    }

    // longへのキャスト operator long()で定義すると modlong +
    // longとかができなくなる
    long tol() { return this->val; }

    // 代入
    void operator=(const modlong &r) { this->val = r.val; }
    void operator=(const long &r) {
        long rr = r;
        while (rr < 0) rr += mod;  // 0以上であることを保証
        this->val = rr % mod;
    }

    //比較
    bool operator<(const modlong &r) { return this->val < r.val; }
    bool operator>(const modlong &r) { return this->val > r.val; }
    bool operator==(const modlong &r) { return this->val == r.val; }
    bool operator!=(const modlong &r) { return !(*this == r); }
    bool operator<=(const modlong &r) { return !(*this > r); }
    bool operator>=(const modlong &r) { return !(*this < r); }

    // 足し算; 符号反転; 引き算
    modlong operator+(const modlong &r) {
        long aval = (this->val + r.val) % mod;
        modlong ans(aval);
        return ans;
    }
    modlong operator-() {
        long aval = (mod - this->val) % mod;
        modlong ans(aval);
        return ans;
    }
    modlong operator-(const modlong &r) {
        modlong rr = r;
        return *this + (-rr);
    }

    //かけ算; 逆元; わり算
    modlong operator*(const modlong &r) {
        long aval = (this->val * r.val) % mod;
        modlong ans(aval);
        return ans;
    }
    modlong inv() {
        if (*this == 1) return modlong(1);
        if (*this == 0) cerr << "warning: dividebyzero!!!" << '\n';

        modlong p, q = *this, m(0), n(1), r, c;
        p.val = mod;  // p=modとかくとp.val=mod%mod=0となってしまう
        while (q > 1) {
            r = p.val %
                q.val;  // r.val=p.val / q.val
                        // とかくよりもこのほうが代入時に%modされるので安全
            c = m.val - n.val * (p.val / q.val);
            p = q, q = r, m = n, n = c;
        }
        return n;
    }
    modlong operator/(const modlong &r) {
        modlong rr = r;
        return *this * rr.inv();
    }

    // ++ -- 前付きと後ろ付き
    void operator++() { ++this->val; }
    void operator++(int a) {
        a = 0;
        this->val++;
    }  // a使ってなくねっていうwarningをsilenceするためにaをいじってる
    void operator--() { --this->val; }
    void operator--(int a) {
        a = 0;
        this->val--;
    }

    // 四則演算&代入
    void operator+=(const modlong &r) { *this = *this + r; }
    void operator-=(const modlong &r) { *this = *this - r; }
    void operator*=(const modlong &r) { *this = *this * r; }
    void operator/=(const modlong &r) { *this = *this / r; }

    // べき乗
    modlong pow(long n) {
        if (n < 0)
            return inv().pow(-n);  // 逆元の-n乗
        else if (n == 0)
            return modlong(1);

        modlong half = pow(n / 2);
        if (n % 2)
            return *this * half * half;
        else
            return half * half;
    }

    // コンビネーション modCombは少し下に書いてある
    modlong C(modlong k) { return modComb(this->val, k.val); }
    modlong fact() { return modFact(this->val); }

    friend ostream &operator<<(ostream &os, const modlong &out);
    friend istream &operator>>(istream &is, modlong &out);
};

// cout、cerr、cin用の演算子たち
ostream &operator<<(ostream &os, const modlong &out) {
    os << out.val;
    return os;
}
istream &operator>>(istream &is, modlong &in) {
    long inl;
    is >> inl;
    in.val = inl % MOD;
    return is;
}

//////      階乗を全て求める -> 二項係数を求める

long invs[MAX], facts[MAX], finvs[MAX];
long listlen = 0;  // invs, facts, finvsの配列長
void computeAll(long n) {
    long i;
    if (listlen == 0) {
        invs[1] = 1;
        facts[0] = 1;
        facts[1] = 1;
        finvs[0] = 1;
        finvs[1] = 1;
        i = 2;
    } else {
        i = listlen;
    }
    for (; i <= n; i++) {
        invs[i] = -invs[MOD % i] * (MOD / i) % MOD;
        facts[i] = facts[i - 1] * i % MOD;
        finvs[i] = finvs[i - 1] * invs[i] % MOD;
    }
    listlen = n + 1;  // 次呼び出すときはn+1以降から再開すれば良い
}
// コンビネーション
modlong modComb(long n, long k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (listlen <= n) computeAll(n);  // 毎回足りない分だけ補う
    return modlong(facts[n]) * finvs[k] * finvs[n - k];
}
// 階乗
modlong modFact(long n) {
    if (listlen <= n) computeAll(n);  // 毎回足りない分だけ補う
    return modlong(facts[n]);
}

//////      使用例

int main() {
    // 初期化方法 4パターン
    // a:long型の値を引数に初期化
    // b:定義時にlongを代入
    // c:定義時にmodlongを代入
    // d:値を初期化しない(この場合自動的に0が代入される)
    modlong a(2), b = 3, c = a, d;

    // 出力したいときは普通にcoutが使えます
    cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';  // -> 2 3 2 0

    // 代入
    // 直接longを代入することもできます。
    // また上でc =
    // aとしましたが、aを変更してもcには反映されません(つまりいつも通り)
    a = 4, d = a;
    cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';  // -> 4 3 2 4

    // 代入時や初期化時にちゃんとmodがかかります
    a = (long)1e9 + 8;
    cout << a << ' ' << modlong(-1) << '\n';  // -> 1 1000000006

    // 四則演算もおてのもの
    a = (long)1e9, b = (long)5e8 + 7, c = 2, d = 1;
    cout << a + b << '\n';  // -> 500000000
    cout << d - c << '\n';  // -> 1000000006
    cout << b * c << '\n';  // -> 7
    cout << d / c << '\n';  // -> 500000004 (逆元)

    // ちなみに演算子の右側はlongでもok
    cout << c + 3 << '\n';  // -> 6
    // 3 + cはエラーになる(頑張ればできるようにできるけどコードがかざばる)
    // 2 / cとかしたい場合は modlong(2)/c あるいは c.inv()*2 と書くと良い

    // 逆元 べき乗 階乗
    a = 2;
    cout << a.inv() << '\n';     // -> 500000004
    cout << a.pow(-2) << '\n';   // -> 250000002 (逆元の2乗)
    cout << a.pow(10) << '\n';   // -> 1024
    cout << a.pow(100) << '\n';  // -> 976371285
    cout << a.fact() << '\n';    // -> 2

    // += *= -= /=も作ったよ
    a = 2;
    a += (long)1e9 + 5;
    cout << a << '\n';  // -> 0

    // 比較もできる
    a = 1, b = 2, c = -1;  // このときcは1000000006になる
    if (a < b) cout << "hoge1" << '\n';
    if (a + c == 0) cout << "hoge2" << '\n';
    // -> hoge1
    //    hoge2

    // longへのキャスト
    long l = a.tol();

    // cin coutもいけるで
    modlong input;
    cin >> input;
    cout << input.C(10) << '\n';
}