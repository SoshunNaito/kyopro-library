/*
using namespace std;
typedef long long ll;

///////////////   �Z�O�����g��
const ll INF = (ll)1234567891011121314;

ll segtree_func(ll a, ll b) {// �ŏ��l�𓾂�Z�O�����g�؂��ł���B
	return min(a, b);
}

class SegmentTree {
public:
	SegmentTree() {
		N = 0;
		node = NULL;
	}
	void activate(int N, ll value) {// ������
		if (node != NULL) { delete[] node; }

		this->N = N;
		size = 1; while (size < N) { size *= 2; }

		node = new ll[2 * size - 1];
		for (int i = 0; i < 2 * size - 1; i++) { node[i] = value; }
	}

	void activate(vector<ll> v) {
		if (node != NULL) { delete[] node; }

		N = v.size();
		size = 1; while (size < N) { size *= 2; }

		node = new ll[2 * size - 1];

		for (ll i = 0; i < N; i++) node[i + size - 1] = v[i];
		for (ll i = size - 2; i >= 0; i--) node[i] = segtree_func(node[i * 2 + 1], node[i * 2 + 2]);
	}

	void update(int pos, ll v) {// pos�̒l��v�ɍX�V����
		int k = pos + size - 1;
		node[k] = v;
		while (k > 0) {
			k = (k - 1) / 2;
			node[k] = segtree_func(node[k * 2 + 1], node[k * 2 + 2]);
		}
	}

	ll get(ll pos) {// pos�̒l���擾����
		if (pos < 0 || pos >= N) {
			cout << "get : pos = "<< pos << "�͔͈�[0, " << N << ")�𒴂��Ă��܂�" << endl;
			return 0;
		}
		ll k = pos + size - 1;
		return node[k];
	}
	ll get(ll L, ll R) {// ���J��� [L, R) �ɂ�����ŏ��l/�ő�l�擾�Ȃǂɓ�����
		if (L > R) {
			ll s = L; L = R; R = s;
			cout << "get : L��R�̑召�֌W���t�ł�" << endl;
		}
		if (L < 0) {
			L = 0;
			cout << "get : L��0�����̒l�ł���" << endl;
		}
		if (R > N) {
			R = N;
			cout << "get : R��N�����傫�Ȓl�ł���" << endl;
		}
		if (L == R) {
			cout << "get : ��Ԃ̕���0�ł���" << endl;
			return 0;
		}
		return query(L, R, 0, 0, size);
	}

	void DebugCout() {// �f�o�b�O�p
		cout << endl << endl;
		cout << "�͈� : " << 0 << " to " << N - 1 << endl;
		int k = 2;
		for (int i = 0; i < size * 2 - 1; i++) {
			if (node[i] == INF) {
				cout << "INF ";
			}
			else {
				cout << node[i] << " ";
			}
			if (i + 2 == k) {
				cout << endl;
				k *= 2;
			}
		}
		cout << endl << endl;
	}
private:
	int size, N;// �m�ۂ��Ă���T�C�Y�A�g���T�C�Y
	ll* node;// �Ǘ��p

	ll query(ll a, ll b, int k, int l, int r) {
		if (a <= l && r <= b) return node[k];

		int c = (l + r) / 2;

		if (c <= a) { return query(a, b, k * 2 + 2, c, r); }
		if (b <= c) { return query(a, b, k * 2 + 1, l, c); }

		return segtree_func(query(a, b, k * 2 + 2, c, r), query(a, b, k * 2 + 1, l, c));
	}
};

int main() {
	int N, M; cin >> N >> M;
	SegmentTree ST; ST.activate(N, INF);

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		a--;
		ST.update(a, b);
	}

	ST.DebugCout();

	cout << ST.get(0, 3) << endl;
	cout << ST.get(4, 6) << endl;
	cout << ST.get(0, 5) << endl;
	cout << ST.get(0, N) << endl;

	cout << ST.get(9, -1) << endl;// �s���ȓ���

	return 0;
}
//////		���ؗp���̓f�[�^
8 6
0 5
2 9
4 3
5 2
7 5
6 1
*/