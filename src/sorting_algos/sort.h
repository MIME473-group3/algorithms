/*
 * sort.h
 *
 *  Created on: 15 Jul 2014
 *      Author: adam
 */

#ifndef SORT_H_
#define SORT_H_

#include <utility>
#include <functional>
#include <vector>
#include <type_traits>
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
void print(const vector<T>& vec, int i = 0, int j = -1) {
	if(j == -1) j = vec.size();

	for(int k = 0; k < i; ++k) {
		cout.width(2);
		cout << " " << " ";
	}

	for(; i < j; ++i) {
		cout.width(2);
		cout << vec[i] << " ";
	}
	cout << endl;
}

template<class T, class Comp = less<T>>
void BubbleSort(vector<T>& vec, Comp comp = Comp()) {
//	compare<T> comp;
	{

		for (int i = 0; i < vec.size(); ++i) {
			for (int j = 0; j < vec.size(); ++j) {

				if (comp(vec[i], vec[j])) {
					swap(vec[i], vec[j]);
				}
			}
		}
	}
}

template<class T, template<class > class compare = less>
void SelectionSort(vector<T>& vec) {
	compare<T> comp;

	for (int i = 0; i < vec.size(); ++i) {

		int min = i;
		for (int j = i + 1; j < vec.size(); ++j) {
			if (comp(vec[j], vec[min])) {
				min = j;
			}
		}
		swap(vec[i], vec[min]);
	}
}

template<class T, template<class > class compare = less>
void InsertionSort(vector<T>& vec, int inc = 1) {
	compare<T> comp;

	for (int i = inc; i < vec.size(); i += inc) {
		int j = i - inc;
		while (j >= inc && comp(vec[i], vec[j])) {
			j -= inc;
		}
		if (comp(vec[j], vec[i]))
			j += inc;
		T tmp = vec[i];
		for (int k = i; k > j; k -= inc) {
			vec[k] = vec[k - 1];
		}
		vec[j] = tmp;
	}
}

template<class T, template<class > class compare = less>
void ShellSort(vector<T>& vec,
		const vector<int>& increments = { 5, 3, 1 }) {

	auto inc = begin(increments);
	while (*inc > vec.size()) {
		++inc;
	}
	while (inc != end(increments)) {
		InsertionSort(vec, *inc++);
	}
}

template<class T, class Comp>
void mergeCombine(const Comp& comp, vector<T>& vec, vector<T>& aux, int low, int mid, int high) {
	int i = low, j = mid, l = low;
	while(l < high) {

		if(i >= mid) aux[l++] = vec[j++];
		else if(j >= high) aux[l++] = vec[i++];
		else if(comp(vec[i], vec[j])) aux[l++] = vec[i++];
		else aux[l++] = vec[j++];
	}
}

template<class T, class Comp>
void mergeSortImpl(const Comp& comp, vector<T>& vec, vector<T>& aux, int low, int high) {

	if(high - low < 2) {
		return;
	}

	const int mid = (high - low + 1) / 2 + low;
	//	swap vec and aux - saves some time due to implicit coping
	mergeSortImpl(comp, aux, vec, low, mid);
	mergeSortImpl(comp, aux, vec, mid, high);

	mergeCombine(comp, vec, aux, low, mid, high);
}

template<class T, template<class > class compare = less>
void MergeSort(vector<T>& vec, compare<T> comp = compare<T>()) {

	vector<T> aux(vec);
	mergeSortImpl(comp, vec, aux, 0, vec.size());
	vec = aux;
}

template<class T, class Comp>
void MergeSortComp(vector<T>& vec, Comp comp) {

	vector<T> aux(vec);
	mergeSortImpl(comp, vec, aux, 0, vec.size());
	vec = aux;
}


int quickChoosePivot(int low, int high) {

	return (rand() % (high - low + 1)) + low;
}

template<class T, class Comp>
int quickPartition(const Comp& comp, vector<T>& vec, int low, int high, int pivot = -1) {

	if(pivot == -1) {
		pivot = quickChoosePivot(low, high);
	}

	swap(vec[pivot], vec[high]);
	pivot = high;
	int i = low, j = high - 1;
	while(i < j) {
		if(comp(vec[i], vec[pivot])) ++i;
		else if(comp(vec[pivot], vec[j])) --j;
		else swap(vec[i++], vec[j--]);
	}
	while(comp(vec[j], vec[pivot])) {
		if(j < high) ++j;
	}
	swap(vec[j], vec[pivot]);
	return j;
}

template<class T, class Comp>
void QuickSortImpl(const Comp& comp, vector<T>& vec, int low, int high) {
	if(high - low + 1 <= 1) {
		return;
	}

	int pivot = quickPartition(comp, vec, low, high);
	QuickSortImpl(comp, vec, low, pivot - 1);
	QuickSortImpl(comp, vec, pivot + 1, high);
}


template<class T, template<class > class compare = less>
void QuickSort(vector<T>& vec) {
	const compare<T> comp;

	QuickSortImpl(comp, vec, 0, vec.size() - 1);
}

template<class T, class Comp>
void siftDown(const Comp& comp, vector<T>& vec, int start, int end) {

	while(2 * start + 1 < end) {
		int swap = 2 * start + 1;
		if(swap + 1 < end && comp(vec[swap + 1], vec[swap])) {
			++swap;
		}
		if(comp(vec[swap], vec[start])) {
			std::swap(vec[start], vec[swap]);
		} else {
			return;
		}
		start = swap;
	}
}

template<class T, class Comp>
void heapify(const Comp& comp, vector<T>& vec) {

	for(int i = vec.size() / 2 - 1; i >= 0; --i) {
		siftDown(comp, vec, i, vec.size());
	}
}

template<class T, template<class > class compare = less>
void HeapSort(vector<T>& vec) {
	compare<T> comp;
	heapify(comp, vec);

	for(int i = vec.size() - 1; i > 0; --i) {
		swap(vec[0], vec[i]);
		siftDown(comp, vec, 0, i);
	}
	std::reverse(begin(vec), end(vec));
}

template<class T, template<class > class compare = less>
void CountSort(vector<T>& vec, function<int(const T&)> mapping) {
	compare<T> comp;

	int max = *max_element(begin(vec), end(vec), comp);
	int min = *min_element(begin(vec), end(vec), comp);
	vector<int> countVec(max - min + 1, 0);
	auto it = begin(vec);
	auto endIt = end(vec);
	while (it != endIt) {
		countVec[mapping(*it++) - min] += 1;
	}

	for (int i = 1; i < countVec.size(); ++i) {
		countVec[i] += countVec[i - 1];
	}
	for(int i = countVec.size() - 1; i > 0; --i) {
		countVec[i] = countVec[i - 1];
	}
	countVec[0] = 0;

	vector<T> sortedVec(vec.size());
	it = begin(vec);
	while (it != endIt) {
		int index = mapping(*it) - min;
		sortedVec[(countVec[index])++] = *(it++);
	}

	vec = sortedVec;
}

template<class T>
void BucketSort(vector<T>& vec, int bins) {
	static_assert(is_arithmetic<T>::value, "Implemented for arithmetics types only");

	bins += 1;
	int* counter = new int[bins];
	memset(counter, 0, bins * sizeof(int));
	T min = *min_element(begin(vec), end(vec));
	T max = *max_element(begin(vec), end(vec));
	T binSize = (max - min) / (bins - 1);

	for_each(begin(vec), end(vec), [counter, binSize](T t) { ++counter[int(t / binSize)];});
	transform(counter, counter + bins - 1, counter + 1, counter + 1, [](int i1, int i2)
			{ return i1 + i2;} );

	rotate(counter, counter + bins - 1, counter + bins);
	counter[0] = 0;

	vector<T> aux(vec.size());
	for_each(begin(vec), end(vec), [&aux, binSize, counter](T t) {

		aux[counter[int(t / binSize)]++] = t;
	});
	vec = aux;

	delete[] counter;
}

template<template<class > class compare = less>
void RadixSort(vector<string>& vec) {
	compare<char> comp;

	int length = max_element(begin(vec), end(vec),
			[](const string& s1, const string& s2) {
		return s1.length() < s2.length();
	})->length();

	for(int i = length; i > 0; --i) {
		auto comparator = [&comp, i](const string& s1, const string& s2) {


			if(s1.length() >= i && s2.length() >= i) return comp(s1[i - 1], s2[i - 1]);
			return s1.length() < s2.length();
		};

		BubbleSort(vec, comparator);
	}

}

#endif /* SORT_H_ */
