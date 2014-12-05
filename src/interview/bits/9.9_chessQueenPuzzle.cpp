/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <set>

void printReverse(const std::vector<int>& vec) {
	for(int i = vec.size() - 1; i >= 0; --i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

int diagNum(int row, int col) {
	return col - row;
}

int negDiagNum(int row, int col, int N) {
	return N - col - 1 - row;
}


void printQueenPositions(std::vector<int>& pos, std::set<int>& diag, std::set<int>& nDiag, int col, std::vector<std::vector<int>>& results) {

	static int a = 0;
	if(col == pos.size()) {
//		std::cout << a++ << std::endl;
//		printReverse(pos);
		results.push_back(std::vector<int>(pos.size()));
		std::copy(pos.rbegin(), pos.rend(), results[results.size() - 1].begin());
		return;
	}

	for(int i = 0; i < pos.size() - col; ++i) {
		int row = pos[i];
		int diagN = diagNum(row, col);
		int negDiagN = negDiagNum(row, col, pos.size());
		if(diag.count(diagN) || nDiag.count(negDiagN)) {
			continue;
		}
		std::swap(pos[i], pos[pos.size() - col - 1]);
		diag.insert(diagN);
		nDiag.insert(negDiagN);
		printQueenPositions(pos, diag, nDiag, col + 1, results);
		diag.erase(diagN);
		nDiag.erase(negDiagN);
		std::swap(pos[i], pos[pos.size() - col - 1]);
	}
}

void printQueenPositions(int N) {
	std::vector<int> pos(N);
	for(int i = 0; i < pos.size(); ++i) {
		pos[i] = i;
	}

	std::set<int> diag;
	std::set<int> negDiag;
	int col = 0;
	std::vector<std::vector<int>> results;
	printQueenPositions(pos, diag, negDiag, col, results);
	std::set<std::vector<int>> uniques;
	for(const auto& vec : results) {
		Utils::printVec(vec);
		uniques.insert(vec);
	}
	std::cout << std::endl;
	std::cout << results.size() << std::endl;
	std::cout << uniques.size() << std::endl;
}

struct Test : public testing::Test {


};


TEST_F(Test, SomeTest) {

	printQueenPositions(8);
}

