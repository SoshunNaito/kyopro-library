/*
/////////////         qsortのラッピング

int qsort_int_compare_ascend(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}
int qsort_int_compare_descend(const void *a, const void *b) {
	return *(int*)b - *(int*)a;
}
void ascendOrder(int size, int *array) {//昇順
	qsort(array, size, sizeof(int), qsort_int_compare_ascend);
}
void descendOrder(int size, int *array) {//降順
	qsort(array, size, sizeof(int), qsort_int_compare_descend);
}
int qsort_long_compare_ascend(const void *a, const void *b) {//long型
	long c = *(long*)a - *(long*)b;
	if (c > 0) { return 1; }
	else if (c < 0) { return -1; }
	return 0;
}
int qsort_long_compare_descend(const void *a, const void *b) {//long型
	long c = *(long*)b - *(long*)a;
	if (c > 0) { return 1; }
	else if (c < 0) { return -1; }
	return 0;
}
void ascendOrder(int size, long *array) {//昇順
	qsort(array, size, sizeof(long), qsort_long_compare_ascend);
}
void descendOrder(int size, long *array) {//降順
	qsort(array, size, sizeof(long), qsort_long_compare_descend);
}

class pairClass { // ペアのソート
public:
	pairClass() { key = 0, value = 0; }
	long key, value;
};
int qsort_int_compare_ascend(const void *a, const void *b) {//keyを見比べる
	long x = ((pairClass*)a)->key - ((pairClass*)b)->key;
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}
int qsort_int_compare_descend(const void *a, const void *b) {//keyを見比べる
	long x = ((pairClass*)b)->key - ((pairClass*)a)->key;
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}
void ascendOrder(int size, pairClass *array) {//昇順
	qsort(array, size, sizeof(pairClass), qsort_int_compare_ascend);
}
void descendOrder(int size, pairClass *array) {//降順
	qsort(array, size, sizeof(pairClass), qsort_int_compare_descend);
}

class compareClass {
public:
	compareClass() {
		ID = 0;
		content = 0;
	}
	int ID;
	int content;
};
int qsort_compareClass_ascend(const void *a, const void *b) {
	return ((compareClass*)a)->content - ((compareClass*)b)->content;
}
void getAscendRanking(int size, int *array, int *buf) {// 昇順のランキングを得る
	compareClass *c = new compareClass[size];
	for (int i = 0; i < size; i++) {
		c[i].content = array[i];
		c[i].ID = i;
	}
	qsort(c, size, sizeof(compareClass), qsort_compareClass_ascend);
	for (int i = 0; i < size; i++) {
		buf[c[i].ID] = i;
	}
	delete[] c;
}



*/