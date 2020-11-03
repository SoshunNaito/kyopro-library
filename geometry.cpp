/*

// 英語が苦手な人用
#define JU_SIN		Centroid
#define NAISETSU_EN	Inscribed_Circle
#define GAISETSU_EN	Circumscribed_Circle
#define SUI_SIN		Orthocenter
#define TOTSU_HO	convex_hull

const double EPS = 0.000000000001;
unsigned int SEED() {
	random_device rd;
	return rd();
}
mt19937_64 MT(SEED());

class Vec2 {// 点
public:
	double x, y;

	Vec2() {
		x = 0, y = 0;
	}
	Vec2(double X, double Y) {
		x = X, y = Y;
	}
	Vec2(pair<double, double> p) {
		x = p.first, y = p.second;
	}
	Vec2(const Vec2& other) {
		x = other.x, y = other.y;
	}

	inline Vec2& operator = (const Vec2& other) {
		x = other.x, y = other.y;
		return *this;
	}
	inline bool operator ==(const Vec2& other) {
		return ((abs(x - other.x) < EPS) && (abs(y - other.y) < EPS));
	}
	inline bool operator !=(const Vec2& other) {
		return !(*this == other);
	}
	inline Vec2& operator += (const Vec2& other) {
		x += other.x, y += other.y;
		return *this;
	}
	inline Vec2& operator -= (const Vec2& other) {
		x -= other.x, y -= other.y;
		return *this;
	}
	inline Vec2& operator *= (double param) {
		x *= param, y *= param;
		return *this;
	}
	inline Vec2& operator /= (double param) {
		if (abs(param) < EPS) {
			x = 0, y = 0;
		}
		else {
			x /= param, y /= param;
		}
		return *this;
	}
	inline Vec2 operator + (const Vec2& other) {
		Vec2 v = *this; v += other;
		return v;
	}
	inline Vec2 operator - (const Vec2& other) {
		Vec2 v = *this; v -= other;
		return v;
	}
	inline Vec2 operator * (double param) {
		Vec2 v = *this; v *= param;
		return v;
	}
	inline Vec2 operator / (double param) {
		Vec2 v = *this; v /= param;
		return v;
	}
	inline double length2() const {
		return x * x + y * y;
	}
	inline double length() const {
		return sqrt(length2());
	}
	inline double dot(Vec2 other) const {
		return x * other.x + y * other.y;
	}
	inline double cross(Vec2 other) const {
		return x * other.y - y * other.x;
	}
	inline void normalize() {
		double rate = length();
		if (rate < EPS) {
			x = 1, y = 0;
		}
		else {
			rate = 1.0 / rate;
			x *= rate;
			y *= rate;
		}
	}
	inline void rotate(double angle_deg) {
		double c = cos(angle_deg * 0.01745329251994329547);
		double s = sin(angle_deg * 0.01745329251994329547);
		double X = x * c - y * s;
		double Y = x * s + y * c;
		x = X, y = Y;
	}
	inline double rad() const {
		if (abs(x) < EPS && abs(y) < EPS) {
			return 0;
		}
		return atan2(x, y);
	}
	double deg() const {
		return rad() * 57.29577951308232286;
	}
};
class Line {// 直線
public:
	Line() {
		norm = Vec2(1, 0);
		dot = 0;
	}
	Line(Vec2 A, Vec2 B) {
		B -= A;
		B.normalize();
		norm.x = -B.y;
		norm.y = B.x;
		dot = norm.dot(A);
	}
	Line(Vec2 n, double d) {
		norm = n;
		dot = d;
		double k = 1.0 / n.length();
		norm *= k;
		dot *= k;
	}
	Line(const Line& other) {
		norm = other.norm, dot = other.dot;
	}
	inline Line& operator = (const Line& other) {
		norm = other.norm, dot = other.dot;
		return *this;
	}

	// 法線ベクトルと、内積の値を持っておく
	Vec2 norm;
	double dot;
};
inline Line Vertical_Bisector(Vec2 A, Vec2 B) {// 垂直二等分線
	A = (A + B) / 2;
	return Line(B - A, (B - A).dot(A));
}
inline Vec2 Projection(Vec2 P, Line L) {// 射影
	return P + L.norm * (L.dot - L.norm.dot(P));
}

class Triangle {// 三角形
public:
	Triangle() {
		A = Vec2(0, 0); B = Vec2(0, 0); C = Vec2(0, 0);
	}
	Triangle(Vec2 P1, Vec2 P2, Vec2 P3) {
		A = P1; B = P2; C = P3; flush();
	}
	Triangle(const Triangle& other) {
		A = other.A; B = other.B; C = other.C; flush();
	}
	inline Triangle& operator =(const Triangle& other) {
		A = other.A; B = other.B; C = other.C; flush();
		return *this;
	}
	inline void flush() {
		if ((B - A).cross(C - A) < -EPS) {
			Vec2 P = B; B = C; C = P;
		}
	}
	inline int inside(Vec2 P) {
		double d1 = (B - A).dot(P - A);
		double d2 = (C - B).dot(P - B);
		double d3 = (A - C).dot(P - C);

		if (d1 > EPS || d2 > EPS || d3 > EPS) { return 0; }
		if (abs(d1) < EPS || abs(d2) < EPS || abs(d3) < EPS) { return 2; }
		return 1;
	}
	inline double area() {
		return (B - A).cross(C - A) / 2;
	}

	Vec2 A, B, C;
};
inline Vec2 Centroid(Vec2 A, Vec2 B, Vec2 C) {// 重心
	return (A + B + C) / 3;
}
inline Vec2 Centroid(Triangle T) {// 重心
	return Centroid(T.A, T.B, T.C);
}

class Circle {// 円
public:
	Circle() {
		C = Vec2(0, 0); r2 = 0;
	}
	Circle(Vec2 center, double r) {
		C = center; r2 = r * r;
	}
	Circle(const Circle& other) {
		C = other.C; r2 = other.r2;
	}
	inline Circle& operator = (const Circle& other) {
		C = other.C; r2 = other.r2;
		return *this;
	}
	inline int inside(Vec2 P) {
		double d = (P - C).length2() - r2;
		if (d > EPS) { return 0; }
		if (d > -EPS) { return 2; }
		return 1;
	}
	Vec2 C;
	double r2;
};
inline Circle Circumscribed_Circle(Vec2 A, Vec2 B, Vec2 C) {// 外接円
	Circle D;

	if (B == C) { D.C = (A + B) / 2; D.r2 = (A - D.C).length2(); return D; }
	if (C == A) { D.C = (B + C) / 2; D.r2 = (B - D.C).length2(); return D; }
	if (A == B) { D.C = (C + A) / 2; D.r2 = (C - D.C).length2(); return D; }

	double a = (B - C).length2();
	double b = (C - A).length2();
	double c = (A - B).length2();

	double s = a + b + c;

	double p = (s - a * 2) * a;
	double q = (s - b * 2) * b;
	double r = (s - c * 2) * c;

	s = p + q + r;
	p /= s; q /= s; r /= s;

	D.C = A * p + B * q + C * r;
	D.r2 = (A - D.C).length2();
	return D;
}
inline Circle Circumscribed_Circle(Triangle T) {// 外接円
	return Circumscribed_Circle(T.A, T.B, T.C);
}
inline Circle Inscribed_Circle(Triangle T) {// 内接円
	double a = (T.B - T.C).length();
	double b = (T.C - T.A).length();
	double c = (T.A - T.B).length();
	double r = 1.0 / (a + b + c);

	return Circle((T.A * a + T.B * b + T.C * c) * r, T.area() * 2 * r);
}
inline Circle Inscribed_Circle(Vec2 A, Vec2 B, Vec2 C) {// 内接円
	return Inscribed_Circle(Triangle(A, B, C));
}
inline Vec2 Orthocenter(Triangle T) {// 垂心
	return Centroid(T) * 3 - Circumscribed_Circle(T).C * 2;
}
inline Vec2 Orthocenter(Vec2 A, Vec2 B, Vec2 C) {// 垂心
	return Orthocenter(Triangle(A, B, C));
}

inline pair<Vec2*, int> convex_hull(vector<Vec2>& P) {// 凸包
	int N = (int)P.size();
	vector<Vec2> v;
	{
		vector<pair<pair<double, double>, int>> temp;
		for (int i = 0; i < N; i++) {
			temp.push_back({ {P[i].x, P[i].y}, i });
		}
		sort(temp.begin(), temp.end());
		for (int i = 0; i < N; i++) {
			v.push_back(P[temp[i].second]);
		}
	}

	vector<Vec2> a, b;
	a.push_back(v[0]);
	a.push_back(v[1]);
	b.push_back(v[N - 1]);
	b.push_back(v[N - 2]);

	for (int i = 2; i < N; i++) {
		int j = N - 1 - i;
		int M1 = (int)a.size(), M2 = (int)b.size();
		while ((v[i] - a[M1 - 2]).cross(a[M1 - 1] - a[M1 - 2]) > -EPS) {
			a.pop_back(); M1--;
			if (M1 == 1) { break; }
		}
		while ((v[j] - b[M2 - 2]).cross(b[M2 - 1] - b[M2 - 2]) > -EPS) {
			b.pop_back(); M2--;
			if (M2 == 1) { break; }
		}
		a.push_back(v[i]);
		b.push_back(v[j]);
	}
	for (int i = 0; i < (int)b.size(); i++) {
		if (b[i] != a.back() && b[i] != a[0]) {
			a.push_back(b[i]);
		}
	}
	int s = (int)a.size();

	pair<Vec2*, int> p;
	p.first = new Vec2[s];
	p.second = s;
	for (int i = 0; i < s; i++) {
		p.first[i] = a[i];
	}
	return p;
}
Circle SmallestEnclosingDisk(Vec2* P0, int N) {// 最小包含円
	vector<Vec2> P;
	for (int i = 0; i < N; i++) {
		P.push_back(P0[i]);
	}
	shuffle(P.begin(), P.end(), MT);
	vector<pair<int, pair<int, vector<int>>>> stack;
	{
		vector<int> v;
		stack.push_back({ 0, { N, v } });
	}

	int counter = 0;

	Circle D;
	while (stack.size() > 0) {
		counter++;

		int command = stack.back().first;
		int M = stack.back().second.first;
		vector<int> v = stack.back().second.second;

		if (M == 0 || v.size() == 3) {
			switch (v.size()) {
			case 0:
				D = Circle(Vec2(0, 0), 0);
				break;
			case 1:
				D.C = P[v[0]], D.r2 = 0;
				break;
			case 2:
			{
				D.C = (P[v[0]] + P[v[1]]) / 2;
				D.r2 = (P[v[0]] - D.C).length2();
			}
			break;
			default:
				D = Circumscribed_Circle(P[v[0]], P[v[1]], P[v[2]]);
				break;
			}
			stack.pop_back();
		}
		else {
			switch (command) {
			case 0:
				stack.back().first++;
				stack.push_back({ 0, { M - 1, v} });
				break;
			case 1:
				if ((D.C - P[M - 1]).length2() > D.r2) {
					vector<int> v1 = v;
					v1.push_back(M - 1);
					stack.pop_back();
					stack.push_back({ 0, { M - 1, v1} });
				}
				else {
					stack.pop_back();
				}
				break;
			}
		}
	}
	return D;
}
Circle SmallestEnclosingDisk(vector<Vec2>& points) {// 最小包含円
	return SmallestEnclosingDisk(points.data(), (int)points.size());
}

*/