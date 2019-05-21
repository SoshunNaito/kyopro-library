/*

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>

using namespace std;

#define arraySize(A) (sizeof(A)/sizeof(A[0]))





/////////////         大小比較

int arrayMax(int size, int *array, int *dest) {
	if (size <= 0 || array == NULL) { return -1; }
	int p = 0;
	for (int i = 0; i < size; i++) {
		if (array[p] < array[i]) { p = i; }
	}
	if (dest != NULL) { *dest = array[p]; }
	return p;
}
int arrayMin(int size, int *array, int *dest) {
	if (size <= 0 || array == NULL) { return -1; }
	int p = 0;
	for (int i = 0; i < size; i++) {
		if (array[p] > array[i]) { p = i; }
	}
	if (dest != NULL) { *dest = array[p]; }
	return p;
}





/////////////         にぶたん
// データ配列に指定された値を挿入したときの番号を返す。
// 例えば x[3] = 5, x[4] = 8 のとき nibutan(5) = ... = nibutan(7) = 4, nibutan(8) = ... = 5

int nibutan(int *x, int n, int key) {
	if (n == 0 || x == NULL) {
		return -1;
	}
	if (key < x[0]) {
		return 0;
	}
	if (x[n - 1] <= key) {
		return n;
	}
	int a = 0, b = n - 1;
	while (b - a > 1) {
		int c = (a + b) / 2;
		if (x[c] <= key) {
			a = c;
		}
		else {
			b = c;
		}
	}
	return b;
}





/////////////         UnionFind
//    バラバラの要素を結合してグループにまとめる際に使える構造。
//    グループ番号、要素数の取得が可能だが、グループに属する要素の列挙はO(N)かかる。

class UnionFindClass {
public:
	UnionFindClass() {
		N = 0;
		parent = NULL;
		size = NULL;
	}
	~UnionFindClass() {
		if (parent != NULL) {
			delete[] parent;
		}
		if (size != NULL) {
			delete[] size;
		}
	}

	void activate(int n) {// 要素の数N
		N = n;
		parent = new int[N];
		size = new int[N];
		for (int i = 0; i < N; i++) {
			parent[i] = -1;
			size[i] = 1;
		}
	}

	int getParent(int x) {// グループの親の番号を得る
		if (parent[x] == -1) {
			return x;
		}
		else {
			int y = getParent(parent[x]);
			parent[x] = y;
			return y;
		}
	}
	int getSize(int x) {// 自分が属するグループのサイズを得る
		x = getParent(x);
		return size[x];
	}
	bool connect(int x, int y) {// 二つの要素を結ぶ。２グループ間を繋いだ場合trueを返す
		x = getParent(x);
		y = getParent(y);
		if (x == y) { return false; }
		int xsize = getSize(x), ysize=getSize(y);
		if (xsize < ysize) {
			parent[x] = y;
			size[y] += size[x];
			size[x] = 0;
		}
		else {
			parent[y] = x;
			size[x] += size[y];
			size[y] = 0;
		}
		return true;
	}

	//データ
	int N;// 個数
	int *parent;// 親の番号。自分自身が親なら-1。
	int *size;// 親のみ有効。自分のグループのサイズ。
};


*/