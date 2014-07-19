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
  SortTest() : seed_(0), size_(100), randomVec(0) {

    srand(seed_);
    randomVec.resize(size_);
    generate(begin(randomVec), end(randomVec), [this]() { return rand() % size_; });

  };
  ~SortTest() {};

  const int seed_;
  const int size_;
  std::vector<int> randomVec;

  void print() {
	  for(const auto& el : randomVec) {
		  cout << el << " ";
	  }
	  cout << endl;
  }

  void printSorted() {
	  auto vec(randomVec);
	  sort(begin(vec), end(vec));
	  for(const auto& el : vec) {
	  		  cout << el << " ";
	  	  }
	  	  cout << endl;
  }
};

TEST_F(SortTest, Bubble) {
  BubbleSort(randomVec);
  ASSERT_SORTED(randomVec);
}

TEST_F(SortTest, Selection) {
  SelectionSort(randomVec);
  ASSERT_SORTED(randomVec);
}

TEST_F(SortTest, Insertion) {
  InsertionSort(randomVec);
  ASSERT_SORTED(randomVec);
}

TEST_F(SortTest, Shell) {
  ShellSort(randomVec);
  ASSERT_SORTED(randomVec);
}

//TEST_F(SortTest, Merge) {
//  MergeSort(randomVec);
//  ASSERT_SORTED(randomVec);
//}

TEST_F(SortTest, Quick) {
	print();
  QuickSort(randomVec);
  print();
  printSorted();
  ASSERT_SORTED(randomVec);
}

//TEST_F(SortTest, Heap) {
//  HeapSort(randomVec);
//  ASSERT_SORTED(randomVec);
//}

TEST_F(SortTest, Count) {
function<int(const int&)> fun = [](const int& t) {return static_cast<int>(t);};
  CountSort(randomVec, fun);
  ASSERT_SORTED(randomVec);
}

//Count
//Bucket
//Radix


