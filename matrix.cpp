/////////	 行列を扱うライブラリ

template <typename T>
class MatrixClass
{
public:
	MatrixClass()
	{
		a = NULL;
		row = 0, column = 0, size = 0;
	}
	MatrixClass(const MatrixClass &other)
	{
		row = other.row;
		column = other.column;
		size = row * column;

		a = new T[size];
		for (int i = 0; i < size; i++)
		{
			a[i] = other.a[i];
		}
	}
	MatrixClass(int _row, int _column, T init = 0)
	{
		assert(_row > 0 && _column > 0);
		row = _row;
		column = _column;
		size = row * column;

		a = new T[size];
		for (int i = 0; i < size; i++)
		{
			a[i] = init;
		}
	}
	inline T &at(int i, int j)
	{ // 要素にアクセスする
		assert(i >= 0 && i < row && j >= 0 && j < column);
		return a[i * column + j];
	}
	inline MatrixClass Transpose()
	{ // 転置
		MatrixClass M(column, row);
		int s = 0;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				M.at(j, i) = a[s];
				s++;
			}
		}
		return M;
	}

	inline MatrixClass &operator=(const MatrixClass &other)
	{
		if (size < other.size)
		{
			delete[] a;
			a = NULL;
		}
		row = other.row;
		column = other.column;
		size = other.size;

		if (a == NULL)
		{
			a = new T[size];
		}
		for (int i = 0; i < size; i++)
		{
			a[i] = other.a[i];
		}

		return *this;
	}
	inline bool operator==(const MatrixClass &other)
	{
		assert(row == other.row && column == other.column);
		for (int i = 0; i < size; i++)
		{
			if (a[i] != other.a[i])
			{
				return false;
			}
		}
		return true;
	}
	inline bool operator!=(const MatrixClass &other)
	{
		return !(*this == other);
	}
	inline MatrixClass &operator+=(const MatrixClass &other)
	{
		assert(row == other.row);
		assert(column == other.column);
		for (int i = 0; i < size; i++)
		{
			a[i] += other.a[i];
		}
		return *this;
	}
	inline MatrixClass &operator-=(const MatrixClass &other)
	{
		assert(row == other.row);
		assert(column == other.column);
		for (int i = 0; i < size; i++)
		{
			a[i] -= other.a[i];
		}
		return *this;
	}
	inline MatrixClass &operator*=(T param)
	{
		int s = min(size, row * column);
		for (int i = 0; i < s; i++)
		{
			a[i] *= param;
		}
		return *this;
	}
	inline MatrixClass &operator/=(T param)
	{
		assert(param != 0);
		int s = min(size, row * column);
		for (int i = 0; i < s; i++)
		{
			a[i] /= param;
		}
		return *this;
	}

	inline MatrixClass operator+(const MatrixClass &other)
	{
		MatrixClass M = *this;
		M += other;
		return M;
	}
	inline MatrixClass operator-(const MatrixClass &other)
	{
		MatrixClass M = *this;
		M -= other;
		return M;
	}
	inline MatrixClass operator*(T param)
	{
		MatrixClass M = *this;
		M *= param;
		return M;
	}
	inline MatrixClass operator/(T param)
	{
		MatrixClass M = *this;
		M /= param;
		return M;
	}
	inline MatrixClass operator*(const MatrixClass &other)
	{
		assert(column == other.row);
		MatrixClass M(row, other.column, 0);
		for (int i = 0; i < row; i++)
		{
			for (int k = 0; k < column; k++)
			{
				T x = this->at(i, k);
				int s = i * other.column;
				int t = k * other.column;
				for (int j = 0; j < other.column; j++)
				{
					M.a[s] += x * other.a[t];
					s++, t++;
				}
			}
		}
		return M;
	}

	T determinant(bool sweep = false)
	{ // sweep = true のときは掃き出し法、false のときは互除法で計算する
		assert(row == column);
		MatrixClass<T> M = *this;

		int n = row;
		if (sweep == true)
		{ // 掃き出し法
			bool f = false;
			for (int i = 0; i < n; i++)
			{
				if (M.at(i, i) == 0)
				{
					int j = i + 1;
					for (; j < n; j++)
					{
						if (M.at(j, i) != 0)
						{
							M.swap_row(i, j);
							f = !f;
							break;
						}
					}
					if (j == n)
					{
						return 0;
					}
				}
				for (int j = i + 1; j < n; j++)
				{
					M.add_row(i, j, -M.at(j, i) / M.at(i, i));
				}
			}
			T ans = 1;
			if (f == true)
			{
				ans = -1;
			}
			for (int i = 0; i < n; i++)
			{
				ans *= M.at(i, i);
			}
			return ans;
		}
		else
		{ // 互除法
			bool f = false;
			for (int i = 0; i < n - 1; i++)
			{
				if (M.at(i, i) == 0)
				{
					int j = i + 1;
					for (; j < n; j++)
					{
						if (M.at(j, i) != 0)
						{
							M.swap_row(i, j);
							f = !f;
							break;
						}
					}
					if (j == n)
					{
						return 0;
					}
				}
				if (M.at(i, i) < 0)
				{
					f = !f;
					for (int j = 0; j < n; j++)
					{
						M.at(i, j) *= -1;
					}
				}
				for (int j = i + 1; j < n; j++)
				{
					T a = M.at(i, i), b = M.at(j, i);
					vector<T> v = Euclid(a, b);
					if (a * v[0] + b * v[1] != 0)
					{
						for (int k = i; k < n; k++)
						{
							a = M.at(i, k), b = M.at(j, k);
							M.at(i, k) = a * v[0] + b * v[1];
							M.at(j, k) = a * v[2] + b * v[3];
						}
					}
					else
					{
						f = !f;
						for (int k = i; k < n; k++)
						{
							a = M.at(i, k), b = M.at(j, k);
							M.at(i, k) = a * v[2] + b * v[3];
							M.at(j, k) = a * v[0] + b * v[1];
						}
					}
				}
			}
			T ans = 1;
			if (f == true)
			{
				ans = -1;
			}
			for (int i = 0; i < n; i++)
			{
				ans *= M.at(i, i);
			}
			return ans;
		}

		return 0;
	}

	void DebugCout()
	{ // デバッグ用
		cout << endl
			 << endl;
		cout << "縦 " << row << " 行, 横 " << column << " 列" << endl;
		for (int i = 0; i < row; i++)
		{
			int k = i * column;
			for (int j = 0; j < column; j++)
			{
				cout << a[k] << " ";
				k++;
			}
			cout << endl;
		}
		cout << endl
			 << endl;
	}

	int row, column;

	void swap_row(int r1, int r2)
	{ // 行の入れ替え
		r1 = r1 * column;
		r2 = r2 * column;
		T x;
		for (int i = 0; i < column; i++)
		{
			x = a[r1];
			a[r1] = a[r2];
			a[r2] = x;
			r1++, r2++;
		}
	}
	void add_row(int r_src, int r_dest, T rate = 1)
	{ // 行の定数倍を他の行に加える
		r_src *= column;
		r_dest *= column;
		for (int i = 0; i < column; i++)
		{
			a[r_dest] += a[r_src] * rate;
			r_src++, r_dest++;
		}
	}
	void swap_column(int c1, int c2)
	{ // 列の入れ替え
		T x;
		for (int i = 0; i < row; i++)
		{
			x = a[c1];
			a[c1] = a[c2];
			a[c2] = x;
			c1 += column, c2 += column;
		}
	}
	void add_column(int c_src, int c_dest, T rate = 1)
	{ // 列の定数倍を他の行に加える
		for (int i = 0; i < row; i++)
		{
			a[c_dest] += a[c_src] * rate;
			c_src += column, c_dest += column;
		}
	}

private:
	vector<T> Euclid(T a, T b)
	{ // 互除法のサポート関数
		T x1 = 1, x2 = 0, y1 = 0, y2 = 1;
		bool f = true;
		while (1)
		{
			if (f)
			{
				if (a == 0)
				{
					break;
				}
				T k = b / a;
				b -= k * a;
				if (b < 0)
				{
					k--;
					b += a;
				}
				y1 -= k * x1;
				y2 -= k * x2;
			}
			else
			{
				if (b == 0)
				{
					break;
				}
				T k = a / b;
				a -= k * b;
				if (a < 0)
				{
					k--;
					a += b;
				}
				x1 -= k * y1;
				x2 -= k * y2;
			}
			f = !f;
		}
		return {x1, x2, y1, y2};
	}

	int size; // 確保サイズ
	T *a;
};

template <typename T>
MatrixClass<T> Identity(int n)
{ // 単位行列
	MatrixClass<T> M(n, n, 0);
	for (int i = 0; i < n; i++)
	{
		M.at(i, i) = 1;
	}
	return M;
}
template <typename T>
MatrixClass<T> power(MatrixClass<T> &S, int n)
{ // 累乗
	MatrixClass<T> M = S, ans = Identity<T>(S.n);
	while (n > 0)
	{
		if (n & 1)
		{
			ans = ans * M;
		}
		M = M * M;
		n /= 2;
	}
	return ans;
}

////////////////////		使用例
int main()
{
	int N = 10;

	MatrixClass<ll> M = Identity<ll>(N) * 3;

	for (int i = 0; i < N; i++)
	{
		M.at(i, (i + 1) % N) = M.at((i + 1) % N, i) = 1;
	}

	M.DebugCout();
	cout << M.determinant() << endl;
	return 0;
}