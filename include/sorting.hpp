#ifndef SORTING_HPP
#define SORTING_HPP

#include <vector>

namespace sorting {

void bubble_sort(std::vector<int>& a);
void insertion_sort(std::vector<int>& a);
void gnome_sort(std::vector<int>& a);
void heap_sort(std::vector<int>& a);
void quick_sort(std::vector<int>& a);
void merge_sort(std::vector<int>& a);
void intro_sort(std::vector<int>& a);
void patience_sort(std::vector<int>& a);
void radix_sort(std::vector<int>& a);

}  // namespace sorting

#endif	// SORTING_HPP
