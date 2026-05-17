#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "sorting.hpp"

void custom_sort(std::vector<int>& a) {
	char* algo = std::getenv("ALGO");
	std::string s_algo = algo ? algo : "std::sort";

	if (s_algo == "bubble") {
		sorting::bubble_sort(a);
	} else if (s_algo == "insertion") {
		sorting::insertion_sort(a);
	} else if (s_algo == "gnome") {
		sorting::gnome_sort(a);
	} else if (s_algo == "heap") {
		sorting::heap_sort(a);
	} else if (s_algo == "merge") {
		sorting::merge_sort(a);
	} else if (s_algo == "quick") {
		sorting::quick_sort(a);
	} else if (s_algo == "intro") {
		sorting::intro_sort(a);
	} else if (s_algo == "patience") {
		sorting::patience_sort(a);
	} else if (s_algo == "radix") {
		sorting::radix_sort(a);
	} else {
		std::sort(a.begin(), a.end());
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	if (!(std::cin >> n)) {
		return 0;
	}
	std::vector<int> a(n);
	for (int& x : a) {
		std::cin >> x;
	}

	auto start = std::chrono::high_resolution_clock::now();
	custom_sort(a);
	auto end = std::chrono::high_resolution_clock::now();

	assert(std::ranges::is_sorted(a));

	std::chrono::duration<double> diff = end - start;
	std::cerr << diff.count() << std::endl;

	return 0;
}
