/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"

void setZerosSimple(int** mat, int N) {

	std::vector<bool> rows(N, false);
	std::vector<bool> cols(N, false);

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			if(mat[i][j] == 0) {
				rows[i] = true;
				cols[j] = true;
			}
		}
	}

	for(int i = 0; i < N; ++i) {
		if(rows[i] == true) {
			for(int j = 0; j < N; ++j) {
				mat[i][j] = 0;
			}
		}
		if(cols[i] == true) {
				for(int j = 0; j < N; ++j) {
					mat[j][i] = 0;
				}
			}
	}
}

void setZerosSkipping(int**mat, int N) {

	std::vector<int> rows(N+1);
	std::vector<int> cols(N+1);
	for(int i = 0; i <= N; ++i) {	//ith entry tells us to which row/column should we go next
		rows[i] = i;
		cols[i] = i;
	}

	for(int i = rows[0]; i < N; i = rows[i+1]) {
		for(int j = cols[0]; j < N; j = cols[j+1]) {
			if(mat[i][j] == 0) {	// if we encounter a zero we shouldn't consider this row/column anymore
				rows[i] = rows[i + 1];
				cols[j] = cols[j + 1];
			}
		}
	}

//	Utils::printVec(rows);
//	Utils::printVec(cols);


	int lastRow = 0, lastCol = 0;
	for(int i = rows[0]; i < N; i = rows[i+1]) {
		for(int j = cols[0]; j < N; j = cols[j+1]) {
			for(int k = lastRow; k < i; ++k) {
				for(int l = lastCol; l < j; ++l) {
					mat[k][l] = 0;
				}
			}
			lastCol = j;
		}
		lastRow = i;
	}
}

struct ZeroRowsColsTest : public testing::Test {

	ZeroRowsColsTest() : testExamples(exampleCount), expectedResults(exampleCount) {};

	void SetUp() {

		std::vector<std::vector<std::vector<int>>> in{
			{	{1, 1}, {1, 0}		},
			{	{1, 1, 1}, {1, 0, 1}, {1, 1, 1}		},
			{	{1, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 1}		}
		};

		std::vector<std::vector<std::vector<int>>> out{
			{	{1, 0}, {0, 0}		},
			{	{1, 0, 1}, {0, 0, 0}, {1, 0, 1}		},
			{	{1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 1}		}
		};

		for(int i = 0; i < exampleCount; ++i) {
			int N = i + 2;
			testExamples[i] = Utils::create2DArray<int>(N, N);
			expectedResults[i] = Utils::create2DArray<int>(N, N);
			for(int j = 0; j < N; ++j) {
				for(int k = 0; k < N; ++k) {
					testExamples[i][j][k] = in[i][j][k];
					expectedResults[i][j][k] = out[i][j][k];
				}
			}
		}
	}

	void TearDown() {
		for(int i = 0; i < exampleCount; ++i) {
			int N = i + 2;
			Utils::delete2DArray(testExamples[i], N);
			Utils::delete2DArray(expectedResults[i], N);
		}
	}

	const int exampleCount = 3;
	std::vector<int**> testExamples;
	std::vector<int**> expectedResults;
};


TEST_F(ZeroRowsColsTest, SimpleMethodTest) {
	for(int i = 0; i < exampleCount; ++i) {
		int N = i + 2;
		setZerosSimple(testExamples[i], N);
		ASSERT_TRUE(Utils::array2DEqual(testExamples[i], expectedResults[i], N, N));
	}
}

TEST_F(ZeroRowsColsTest, SkippingMethodTest) {
	for(int i = 0; i < exampleCount; ++i) {
		int N = i + 2;
		Utils::print2DArray(testExamples[i], N, N); std::cout << std::endl;
		setZerosSkipping(testExamples[i], N);
		Utils::print2DArray(testExamples[i], N, N); std::cout << std::endl;
		Utils::print2DArray(expectedResults[i], N, N); std::cout << std::endl;
		ASSERT_TRUE(Utils::array2DEqual(testExamples[i], expectedResults[i], N, N));
	}
}
