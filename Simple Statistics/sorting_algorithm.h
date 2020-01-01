#pragma once
#ifndef SORTING_ALGORITHM_H
#define SORTING_ALGORITHM_H
#include <iostream>
#include <vector>
#include "pair.h"

template <typename T>
inline void swap(pair<T>& a, pair<T>& b) {//inline makes it faster 
	pair<T> t;

	t.value = a.value;
	t.freq = a.freq;

	a.value = b.value;
	a.freq = b.freq;

	b.value = t.value;
	b.freq = t.freq;
}

//insertionSort(vec, vec.size()-1);  
template <typename T>
void insertionSort(std::vector<pair<T>>& vec, int left_end, int right_end) {
	for (int i = left_end + 1; i <= right_end; i++) {
		for (int j = i; (j > left_end) && (vec[j - 1].value > vec[j].value); j--) {
			swap(vec[j], vec[j - 1]);
		}
	}
}

int findpivot(int i, int j) {
	return (i + j) / 2;
}

template <typename T>
int partition(std::vector<pair<T>>& A, int left_end, int right_end, pair<T> pivot)
{
	while (left_end <= right_end) // Move bounds inward until they meet
	{ 
		while (A[left_end].value < pivot.value) {
			left_end++; //finding the ones greater than pivot from left_end
		}
		
		while ((left_end <= right_end) && (A[right_end].value >= pivot.value)) {
			right_end--; //finding ones lesser than pivot from right_end
			
		}
		
		if (right_end > left_end) {
			swap(A[left_end], A[right_end]);  // Swap out-of-place values	
		}
	}
	return left_end;           // Return first position in right_end partition

} 

//enhanced_quick(vec, 0, vec.size()-1)
template <typename T>
void enhanced_quick(std::vector<pair<T>>& A, int i, int j, bool have_insertion_sort = true) {//i = left_end, j = right_end
	int pivotindex = findpivot(i, j);
	swap(A[pivotindex], A[j]); // Stick pivot at end
	pivotindex = j;

	// k will be the first position in the right subarray
	int k = partition(A, i, j - 1, A[pivotindex]);
	
	swap(A[k], A[j]);                       // Put pivot in place

	int partitionFloor;
	if (have_insertion_sort == false)
		partitionFloor = 1;
	else
		partitionFloor = 10;
	
	if ((k - i) > partitionFloor)// Sort left partition
		enhanced_quick(A, i, k - 1, have_insertion_sort); 
	else if (have_insertion_sort == true)
		insertionSort(A, i, k - 1);

	if ((j - k) > partitionFloor)// Sort right partition
		enhanced_quick(A, k + 1, j, have_insertion_sort); 
	else if (have_insertion_sort == true)
		insertionSort(A, k + 1, j);
}


#endif