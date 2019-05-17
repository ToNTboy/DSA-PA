#include <cstdio>

void merge(int* vector, int lo, int mi, int hi) {
	int* A = vector + lo;
	int lb = mi - lo;
	int* B = new int[lb];
	for (int i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi;
	int* C = vector + mi;
	for (int i = 0, j = 0, k = 0; j < lb;) {
		if (k < lc && C[k] < B[j]) A[i++] = C[k++];
		if (lc <= k || B[j] <= C[k]) A[i++] = B[j++];
	}
	delete[] B;
}

void mergeSort(int* vector, int lo, int hi) {
	if (hi - lo < 2) return;
	int mi = (lo + hi) / 2;
	mergeSort(vector, lo, mi);
	mergeSort(vector, mi, hi);
	merge(vector, lo, mi, hi);
}

int search(int* vector, int lo, int hi, int const e, bool rIdx) {
	if (lo == hi) return lo - 1;

	int mi = (lo + hi) / 2;
	if (rIdx ? vector[mi] <= e : vector[mi] < e) {
		return search(vector, mi + 1, hi, e, rIdx);
	}
	else {
		return search(vector, lo, mi, e, rIdx);
	}
}

int numsBetween(int* vector, int lo, int hi, int min, int max) {
	if (max < vector[lo] || min > vector[hi - 1]) return 0;
	int rl = search(vector, lo, hi, max, true);
	int ll = search(vector, lo, rl + 1, min, false);
	return rl - ll;
}

int main() {
	int n; int m;
	int min, max;
	std::scanf("%d %d", &n, &m);
	int* vector = new int[n];
	int* result = new int[m];
	for (int i = 0; i < n; i++) {
		std::scanf("%d", &vector[i]);
	}
	mergeSort(vector, 0, n); // O(nlogn)
	for (int i = 0; i < m; i++) { // O(2mlogn)
		std::scanf("%d %d", &min, &max);
		result[i] = numsBetween(vector, 0, n, min, max);
	}
	for (int i = 0; i < m; i++) std::printf("%d\n", result[i]);
	delete vector;
	delete result;
	return 0;
}
