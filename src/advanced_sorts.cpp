#include <algorithm>
#include <cmath>
#include <cstdint>

#include "sorting.hpp"

namespace sorting {

// Helper for Introsort
void insertion_sort_intro(std::vector<int>& a, const int left, const int right) {
	for (int i = left + 1; i <= right; i++) {
		const int key = a[i];
		int j = i - 1;
		while (j >= left && a[j] > key) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

void heapify_intro(std::vector<int>& a, const int n, const int i, const int offset) {
	int largest = i;
	const int l = 2 * i + 1;
	const int r = 2 * i + 2;

	if (l < n && a[offset + l] > a[offset + largest]) {
		largest = l;
	}

	if (r < n && a[offset + r] > a[offset + largest]) {
		largest = r;
	}

	if (largest != i) {
		std::swap(a[offset + i], a[offset + largest]);
		heapify_intro(a, n, largest, offset);
	}
}

void heap_sort_intro(std::vector<int>& a, const int left, const int right) {
	const int n = right - left + 1;
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify_intro(a, n, i, left);
	}

	for (int i = n - 1; i > 0; i--) {
		std::swap(a[left], a[left + i]);
		heapify_intro(a, i, 0, left);
	}
}

[[nodiscard]] int partition_intro(std::vector<int>& a, const int low, const int high) {
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

void introsort_util(std::vector<int>& a, const int left, const int right, const int depth_limit) {
	const int n = right - left + 1;
	if (n < 16) {
		insertion_sort_intro(a, left, right);
		return;
	}
	if (depth_limit == 0) {
		heap_sort_intro(a, left, right);
		return;
	}
	const int pivot = partition_intro(a, left, right);
	introsort_util(a, left, pivot - 1, depth_limit - 1);
	introsort_util(a, pivot + 1, right, depth_limit - 1);
}

void intro_sort(std::vector<int>& a) {
	if (a.empty()) {
		return;
	}
	const int depth_limit = 2 * std::log2(a.size());
	introsort_util(a, 0, a.size() - 1, depth_limit);
}

// --- Patience Sort ---
void patience_sort(std::vector<int>& a) {
	if (a.empty()) {
		return;
	}
	std::vector<std::vector<int>> piles;
	for (const int x : a) {
		auto it = std::lower_bound(
			piles.begin(), piles.end(), x,
			[](const std::vector<int>& pile, const int val) { return pile.back() < val; });
		if (it == piles.end()) {
			piles.push_back({x});
		} else {
			it->push_back(x);
		}
	}

	// Merge piles
	const auto compare = [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
		return p1.first > p2.first;
	};
	std::vector<int> result;
	result.reserve(a.size());

	// min-heap pentru merging
	std::vector<std::pair<int, int>> heap;
	std::vector<int> pile_ptr(piles.size());
	for (size_t i = 0; i < piles.size(); ++i) {
		heap.push_back({piles[i].back(), i});
		pile_ptr[i] = piles[i].size() - 1;
	}
	std::make_heap(heap.begin(), heap.end(), compare);

	while (!heap.empty()) {
		std::pop_heap(heap.begin(), heap.end(), compare);
		const auto [val, idx] = heap.back();
		heap.pop_back();

		result.push_back(val);

		if (pile_ptr[idx] > 0) {
			pile_ptr[idx]--;
			heap.push_back({piles[idx][pile_ptr[idx]], idx});
			std::push_heap(heap.begin(), heap.end(), compare);
		}
	}
	a = std::move(result);
}

// --- Radix Sort ---
void radix_sort(std::vector<int>& a) {
	if (a.empty()) {
		return;
	}

	const int n = a.size();
	std::vector<uint32_t> b(n);
	// [-2^31, 2^31-1] -> [0, 2^32-1]
	for (int i = 0; i < n; ++i) {
		b[i] = static_cast<uint32_t>(a[i]) ^ 0x80000000;
	}

	std::vector<uint32_t> temp(n);
	for (int shift = 0; shift < 32; shift += 8) {
		size_t count[256] = {0};
		for (int i = 0; i < n; ++i) {
			count[(b[i] >> shift) & 0xFF]++;
		}
		for (int i = 1; i < 256; ++i) {
			count[i] += count[i - 1];
		}
		for (int i = n - 1; i >= 0; --i) {
			temp[--count[(b[i] >> shift) & 0xFF]] = b[i];
		}
		b = temp;
	}

	for (int i = 0; i < n; ++i) {
		a[i] = static_cast<int>(b[i] ^ 0x80000000);
	}
}

}  // namespace sorting
