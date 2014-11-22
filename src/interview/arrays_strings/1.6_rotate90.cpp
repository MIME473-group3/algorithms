/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"

void changeIndex(int& i, int& j, int N) {
	int tmp = N - 1 - j;
	j = i;
	i = tmp;
}

void rotate90(int** img, int N) {

	for(int i = 0; i < (N + 1) / 2; ++i) {
		for(int j = i; j < N - i - 1; ++j) {

			int buffer = img[i][j];
			int oldI = i, oldJ = j;
			for(int k = 0; k < 3; ++k) {
				changeIndex(i, j, N);
				img[oldI][oldJ] = img[i][j];
				oldI = i;
				oldJ = j;
			}
			changeIndex(i, j, N);
			img[oldI][oldJ] = buffer;
		}
	}
}

struct Rotate90Test : public testing::Test {

	Rotate90Test() : testExamples(matCount), expectedResults(matCount) {};

	void SetUp() {

		for(int i = 0; i < matCount; ++i) {
			int N = i+1;
			testExamples[i] = Utils::create2DArray<int>(N, N);
			expectedResults[i] = Utils::create2DArray<int>(N, N);
			Utils::fill2DArray<int>(testExamples[i], N, N, [N](int i, int j) {return i * N + j;});
			Utils::fill2DArray<int>(expectedResults[i], N, N, [N](int i, int j) {return (N - 1 - j) * N + i;});
		}
	}

	void TearDown() {
		for(int i = 0; i < matCount; ++i) {
			int N = i + 1;
			Utils::delete2DArray(testExamples[i], N);
			Utils::delete2DArray(expectedResults[i], N);
		}
	}

	void printVec(const std::vector<int**>& vec) {
		for(int i = 0; i < vec.size(); ++i) {
			Utils::print2DArray(vec[i], i+1, i+1, "\t");
			std::cout << std::endl;
		}
	}

	const int matCount = 5;
	std::vector<int**> testExamples;
	std::vector<int**> expectedResults;
};


TEST_F(Rotate90Test, SimpleTest) {
	for(int i = 0; i < matCount; ++i) {
		int N = i + 1;
		rotate90(testExamples[i], N);
		ASSERT_TRUE(Utils::array2DEqual(testExamples[i], expectedResults[i], N, N));
	}
}

