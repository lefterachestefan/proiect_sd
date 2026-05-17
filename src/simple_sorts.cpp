#include "sorting.hpp"

namespace sorting {

void bubble_sort(std::vector<int>& a) {
	const int n = a.size();
	for (int i = 0; i < n - 1; ++i) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; ++j) {
			if (a[j] > a[j + 1]) {
				std::swap(a[j], a[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

void insertion_sort(std::vector<int>& a) {
	const int n = a.size();
	for (int i = 1; i < n; ++i) {
		const int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key) {
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = key;
	}
}

void gnome_sort(std::vector<int>& a) {
	const int n = a.size();
	int index = 0;
	while (index < n) {
		if (index == 0) {
			index++;
		}
		if (a[index] >= a[index - 1]) {
			index++;
		} else {
			std::swap(a[index], a[index - 1]);
			index--;
		}
	}
}

}  // namespace sorting
