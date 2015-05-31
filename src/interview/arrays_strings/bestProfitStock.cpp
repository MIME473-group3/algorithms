/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"

std::pair<int, int> findBestProfit(const std::vector<float>& prices) {

	if(prices.size() <= 1) {
		return std::make_pair(0, 0);
	}

	int minIndex = 0;
	int maxIndex = 0;
	float diff = 0;
	int currentBeg = 0;

	for(int i = 1; i < prices.size(); ++i) {

		if(prices[i] > prices[maxIndex]) {
			maxIndex = i;
			diff = prices[minIndex] - prices[maxIndex];
		} else if(prices[i] < prices[currentBeg]) {
			currentBeg = i;
		}

		if(prices[i] - prices[currentBeg] > diff) {
			minIndex = currentBeg;
			maxIndex = i;
			diff = prices[maxIndex] - prices[minIndex];
		}
	}
	return std::make_pair(minIndex, maxIndex);
}

struct BestProfitStockTest : public testing::Test {


};


TEST_F(BestProfitStockTest, SomeTest) {

	std::vector<float> prices1 = {7, 10, 11, 6, 8, 5, 7, 10, 12, 10, 15, 12, 7, 18, 20, 22, 30, 6};
	std::vector<float> prices2 = {7, 12, 5, 11, 6, 4};

	ASSERT_EQ(findBestProfit(prices1), std::make_pair(5, 16));
	ASSERT_EQ(findBestProfit(prices2), std::make_pair(2, 3));



}

