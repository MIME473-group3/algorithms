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

using namespace std;

template<class T, template<class> class compare = std::less>
void Sort(std::vector<T>& vec) {
  auto comp = compare<T>();
};

template<class T, template<class> class compare = std::less>
void BubbleSort(std::vector<T>& vec) {
  auto comp = compare<T>(); {

    for(int i = 0; i < vec.size(); ++i) {
      for(int j = 0; j < vec.size(); ++j) {

        if(comp(vec[i], vec[j])) {
          swap(vec[i], vec[j]);
        }
      }
    }
  }
};

template<class T, template<class> class compare = std::less>
void SelectionSort(std::vector<T>& vec) {
  auto comp = compare<T>();

  for(int i = 0; i < vec.size(); ++i) {

    int min = i;
    for(int j = i + 1; j < vec.size(); ++j) {
      if(comp(vec[j], vec[min])) {
        min = j;
      }
    }
    swap(vec[i], vec[min]);
  }
};

template<class T, template<class> class compare = std::less>
void InsertionSort(std::vector<T>& vec, int inc = 1) {
  auto comp = compare<T>();

  for(int i = inc; i < vec.size(); i += inc) {
    int j = i - inc;
    while(j >= inc && comp(vec[i], vec[j])) {
      j -= inc;
    }
    if(comp(vec[j], vec[i])) j += inc;
    T tmp = vec[i];
    for(int k = i; k > j; k -= inc) {
      vec[k] = vec[k-1];
    }
    vec[j] = tmp;
  }
};

template<class T, template<class> class compare = std::less>
void ShellSort(std::vector<T>& vec, const vector<int>& increments = {5, 3, 1}) {
  auto comp = compare<T>();

  auto inc = begin(increments);
  while(*inc > vec.size()) {
    ++inc;
  }
  while(inc != end(increments)) {
    InsertionSort(vec, *inc++);
  }
};

template<class T, template<class> class compare = std::less>
void MergeSort(std::vector<T>& vec) {
  auto comp = compare<T>();
};

template<class T, template<class> class compare = std::less>
void QuickSort(std::vector<T>& vec) {
  auto comp = compare<T>();
};

template<class T, template<class> class compare = std::less>
void HeapSort(std::vector<T>& vec) {
  auto comp = compare<T>();
};

template<class T, template<class> class compare = std::less>
void CountSort(std::vector<T>& vec, function<int(const T&)> mapping) {
  auto comp = compare<T>();

  int max = max_element(begin(vec), end(vec), compare);
  int min = min_element(begin(vec), end(vec), compare);
  std::vector<int> countVec(max - min, 0);
  auto it = begin(vec);
  auto endIt = end(vec);
  while(it != endIt) {
    countVec[mapping(*it++) - min] += 1;
  }

  for(int i = 1; i < countVec.size(); ++i) {

  }


};

template<class T, template<class> class compare = std::less>
void BucketSort(std::vector<T>& vec) {
  auto comp = compare<T>();
};

template<class T, template<class> class compare = std::less>
void RadixSort(std::vector<T>& vec) {
  auto comp = compare<T>();
};


#endif /* SORT_H_ */
