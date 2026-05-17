#include <algorithm>
#include <cstdlib>

#include "sorting.hpp"

namespace sorting {

// --- Heap Sort ---
void heapify(std::vector<int>& a, const int n, const int i) {
	int largest = i;
	const int l = 2 * i + 1;
	const int r = 2 * i + 2;

	if (l < n && a[l] > a[largest]) {
		largest = l;
	}

	if (r < n && a[r] > a[largest]) {
		largest = r;
	}

	if (largest != i) {
		std::swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}

void heap_sort(std::vector<int>& a) {
	const int n = a.size();
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}

	for (int i = n - 1; i > 0; i--) {
		std::swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

// --- Merge Sort ---
void merge(std::vector<int>& a, const int l, const int m, const int r) {
	const int n1 = m - l + 1;
	const int n2 = r - m;

	std::vector<int> L(n1), R(n2);

	for (int i = 0; i < n1; i++) {
		L[i] = a[l + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = a[m + 1 + j];
	}

	int i = 0, j = 0, k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			a[k] = L[i];
			i++;
		} else {
			a[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		a[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		a[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort_recursive(std::vector<int>& a, const int l, const int r) {
	if (l < r) {
		const int m = l + (r - l) / 2;
		merge_sort_recursive(a, l, m);
		merge_sort_recursive(a, m + 1, r);
		merge(a, l, m, r);
	}
}

void merge_sort(std::vector<int>& a) {
	if (a.empty()) {
		return;
	}
	merge_sort_recursive(a, 0, a.size() - 1);
}

// --- Quick Sort ---
[[nodiscard]] int partition(std::vector<int>& a, const int low, const int high) {
	const int pivot_idx = low + std::rand() % (high - low + 1);
	std::swap(a[pivot_idx], a[high]);
	const int pivot = a[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (a[j] < pivot) {
			i++;
			std::swap(a[i], a[j]);
		}
	}
	std::swap(a[i + 1], a[high]);
	return (i + 1);
}

void quick_sort_recursive(std::vector<int>& a, int low, int high) {
	while (low < high) {
		const int pi = partition(a, low, high);
		// Tail recursion optimization
		if (pi - low < high - pi) {
			quick_sort_recursive(a, low, pi - 1);
			low = pi + 1;
		} else {
			quick_sort_recursive(a, pi + 1, high);
			high = pi - 1;
		}
	}
}

void quick_sort(std::vector<int>& a) {
	if (a.empty()) {
		return;
	}
	quick_sort_recursive(a, 0, a.size() - 1);
}

}  // namespace sorting
