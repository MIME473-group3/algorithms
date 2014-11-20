/*
 * test.cpp
 *
 *  Created on: 15 Jul 2014
 *      Author: adam
 */

#include <gtest/gtest.h>
#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "sort.h"

using namespace std;

#define ASSERT_SORTED(x) EXPECT_TRUE(is_sorted(begin(x), end(x)))

class SortTest : public ::testing::Test {
public:
  SortTest() : seed_(0), size_(100), randomVec(size_),
  	orderedVec(size_), reversedVec(size_) {

    srand(seed_);
    generate(begin(randomVec), end(randomVec), [this]() { return rand() % size_; });
    for(int i = 0; i < size_; ++i) {
    	orderedVec[i] = i;
    	reversedVec[i] = size_ - i - 1;
    }
  };
  ~SortTest() {};

  const int seed_;
  const int size_;
  vector<int> randomVec;
  vector<int> orderedVec;
  vector<int> reversedVec;

  template<class T>
  void print(const vector<T>& vec) {
	  for(const auto& el : vec) {
		  cout << el << " ";
	  }
	  cout << endl;
  }

  template<class T>
  void printSorted(const vector<T>& vec) {
	  auto v(vec);
	  sort(begin(v), end(v));
	  for(const auto& el : v) {
	  		  cout << el << " ";
	  	  }
	  	  cout << endl;
  }
};

TEST_F(SortTest, Bubble) {
  BubbleSort(randomVec);
  ASSERT_SORTED(randomVec);
  BubbleSort(orderedVec);
  ASSERT_SORTED(orderedVec);
  BubbleSort(reversedVec);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, Selection) {
  SelectionSort(randomVec);
  ASSERT_SORTED(randomVec);
  SelectionSort(orderedVec);
  ASSERT_SORTED(orderedVec);
  SelectionSort(reversedVec);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, Insertion) {
  InsertionSort(randomVec);
  ASSERT_SORTED(randomVec);
  InsertionSort(orderedVec);
  ASSERT_SORTED(orderedVec);
  InsertionSort(reversedVec);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, Shell) {
  ShellSort(randomVec);
  ASSERT_SORTED(randomVec);
  ShellSort(orderedVec);
  ASSERT_SORTED(orderedVec);
  ShellSort(reversedVec);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, Merge) {
  MergeSort(randomVec);
  ASSERT_SORTED(randomVec);
  MergeSort(orderedVec);
  ASSERT_SORTED(orderedVec);
  MergeSort(reversedVec);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, QuickChoosePivot) {

	for(int i = 0; i < 1000; ++i) {
		int low = rand() % 1000000;
		int high = rand() % 1000000;
		if(low > high) swap(low, high);
		int pivot = quickChoosePivot(low, high);
		ASSERT_GE(pivot, low);
		ASSERT_LE(pivot, high);
	}
}

TEST_F(SortTest, QuickPartition) {

	less<int> comp;
	for(uint p = 0; p < randomVec.size(); ++p) {
		int pivotValue = randomVec[p];
		int pivotIndex = quickPartition(comp, randomVec, 0, randomVec.size() - 1, p);
		ASSERT_EQ(randomVec[pivotIndex], pivotValue) << "p = " << p;
		for(int i = 0; i < pivotIndex; ++i) {
			ASSERT_LE(randomVec[i], pivotValue);
		}
		for(uint i = pivotIndex + 1; i < randomVec.size(); ++i) {
			ASSERT_GE(randomVec[i], pivotValue) << "i = " << i << " p = " << p;
		}
	}
}

TEST_F(SortTest, Quick) {
  QuickSort(reversedVec);
  ASSERT_SORTED(reversedVec);
  QuickSort(orderedVec);
  ASSERT_SORTED(orderedVec);
  QuickSort(reversedVec);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, HeapSiftDown) {

	less<int> comp;
	vector<int> vec = {5, 4, 3, 2, 1};
	siftDown(comp, vec, 0, vec.size());
	ASSERT_EQ(vec[0], 3);
	ASSERT_EQ(vec[1], 4);
	ASSERT_EQ(vec[2], 5);
	ASSERT_EQ(vec[3], 2);
	ASSERT_EQ(vec[4], 1);
}

TEST_F(SortTest, HeapHeapify) {

	less<int> comp;
	vector<int> vec = {5, 4, 3, 2, 1};
	heapify(comp, vec);
	ASSERT_EQ(vec[0], 1);
	ASSERT_EQ(vec[1], 2);
	ASSERT_EQ(vec[2], 3);
	ASSERT_EQ(vec[3], 5);
	ASSERT_EQ(vec[4], 4);
}

TEST_F(SortTest, Heap) {
  HeapSort(randomVec);
  ASSERT_SORTED(randomVec);
}

TEST_F(SortTest, Count) {
function<int(const int&)> fun = [](const int& t) {return static_cast<int>(t);};
  CountSort(randomVec, fun);
  ASSERT_SORTED(randomVec);
  CountSort(orderedVec, fun);
  ASSERT_SORTED(orderedVec);
  CountSort(reversedVec, fun);
  ASSERT_SORTED(reversedVec);
}

TEST_F(SortTest, Bucket) {
	vector<float> randomVec(begin(this->randomVec), end(this->randomVec));
	transform(begin(randomVec), end(randomVec), begin(randomVec), [](float f) {return f * 0.01;});
	BucketSort(randomVec, 10);
	float min = *min_element(begin(randomVec), end(randomVec));
	float max = *max_element(begin(randomVec), end(randomVec));
	float bucketSize = (max - min) / 10;
	auto first = begin(randomVec);
	auto second = ++begin(randomVec);
	auto end = std::end(randomVec);
	while(second < end) {
		ASSERT_GT(*second++, *first++ - bucketSize);
	}
}

static string randomStrGen(int length) {
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

TEST_F(SortTest, Radix) {
	int N = 100;
	vector<string> vec(N);
	generate_n(begin(vec), 100, [](){ return randomStrGen((rand() % 10) + 1);});
	print(vec);
	RadixSort(vec);
	print(vec);
	printSorted(vec);
	ASSERT_SORTED(vec);

}


