/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

int findInRotatedArray(const std::vector<int>& vec, int value, int start, int end) {
//	LOG(ERROR) << start << " " << start + (end - start) / 2 << " " << end;
	if(start >= end) { // failure
		return -1;
	}

	int mid = start + (end - start) / 2;
	if(vec[mid] == value) {
		return mid;
	}

	if(vec[start] == vec[mid]) {	// we have a problem; check both sides
		int right = findInRotatedArray(vec, value, mid + 1, end);
		if(right != -1) {
			return right;
		}
		return findInRotatedArray(vec, value, start, mid);
	}

	if(vec[start] < vec[mid]) { // left part is normally sorted
		if(value >= vec[start] && value < vec[mid]) { // go left
			return findInRotatedArray(vec, value, start, mid);
		} //go right
		return findInRotatedArray(vec, value, mid + 1, end);
	} // right part is normally sorted
	if(value > vec[mid] && value <= vec[end - 1]) { // go right
		return findInRotatedArray(vec, value, mid + 1, end);
	} //go left
	return findInRotatedArray(vec, value, start, mid);
}

int findInRotatedArray(const std::vector<int>& vec, int value) {
//	LOG(ERROR) << "value:" << value;
	return findInRotatedArray(vec, value, 0, vec.size());
}

int findMinIndex(const std::vector<int>& vec, int start, int end, int minIndex) {
//		LOG(ERROR) << start << " " << start + (end - start) / 2 << " " << end;
	if(start >= end) {
		return minIndex;
	}

	int mid = start + (end - start) / 2;
	if(vec[mid] < vec[minIndex]) {
		minIndex = mid;
	}

	if(vec[start] > vec[mid]) {
		return findMinIndex(vec, start, mid, minIndex);
	}
	return findMinIndex(vec, mid + 1, end, minIndex);

}

int findMinIndex(const std::vector<int>& vec) {
	return findMinIndex(vec, 0, vec.size(), vec.size() / 2);
}

struct FindInRotatedArrayTest : public testing::Test {

	FindInRotatedArrayTest() : testVec {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14} {}
	std::vector<int> testVec;
};


TEST_F(FindInRotatedArrayTest, FindValueTest) {
	ASSERT_EQ(findInRotatedArray(testVec, 5), 8);
	ASSERT_EQ(findInRotatedArray(testVec, 15), 0);
	ASSERT_EQ(findInRotatedArray(testVec, 20), 3);
	ASSERT_EQ(findInRotatedArray(testVec, 1), 5);
	ASSERT_EQ(findInRotatedArray(testVec, 14), 11);
	ASSERT_EQ(findInRotatedArray(testVec, 33), -1);
}

TEST_F(FindInRotatedArrayTest, FindMinTest) {
	ASSERT_EQ(findMinIndex(testVec), 5);
}

