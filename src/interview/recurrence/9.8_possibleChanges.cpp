/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"

typedef std::vector<int> Change;
typedef std::vector<Change> ChangeVec;

void checkPositiveCoinsOnly(const Change& coins) {
	for(auto coin : coins) {
		if(coin <= 0) {
			throw new std::logic_error("Coins must have positive value!");
		}
	}
}

void possibleChanges(ChangeVec& result, const Change& coins, Change& current, int index, int N) {
	if(index == coins.size() - 1) {
		if(N % coins[index] == 0) {
			current[index] = N / coins[index];
			result.emplace_back(current.begin(), current.end());
		}
		return;
	}

	current[index] = 0;
	while(N >= 0) {
		possibleChanges(result, coins, current, index + 1, N);
		current[index] += 1;
		N -= coins[index];
	}
}

ChangeVec possibleChanges(const Change& coins, int N) {
	checkPositiveCoinsOnly(coins);
	ChangeVec result;
	Change current(coins.size(), 0);
	possibleChanges(result, coins, current, 0, N);
	return result;
}

int possibleChangeWays(const Change& coins, int index, int N) {
	if(index == coins.size() - 1) {
		if(N % coins[index] == 0) {
			return 1;
		}
		return 0;
	}

	int ways = 0;
	while(N >= 0) {
		ways += possibleChangeWays(coins, index + 1, N);
		N -= coins[index];
	}
	return ways;
}

int possibleChangeWays(const Change& coins, int N) {
	checkPositiveCoinsOnly(coins);
	return possibleChangeWays(coins, 0, N);
}

struct PossibleChangesTest : public testing::Test {};


TEST_F(PossibleChangesTest, SomeTest) {

	const Change coins = {25, 10, 5, 1};
	auto result = possibleChanges(coins, 100);

	for(const auto& vec : result) {
		int sum = 0;
		for(int i = 0; i < vec.size(); ++i) {
			sum += coins[i] * vec[i];
		}
		ASSERT_EQ(sum, 100);
		Utils::printVec(vec);
	}
	int ways = possibleChangeWays(coins, 100);
	std::cout << ways << std::endl;
	ASSERT_EQ(result.size(), ways);
}

