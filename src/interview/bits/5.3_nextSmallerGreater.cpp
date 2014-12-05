/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

int findPattern(uint where, int pattern, int length) {
	uint mask = (1 << length) - 1;
	for(int i = 0; i < sizeof(where) * 8 - length; ++i) {
		if(((where >> i) & mask) == pattern) {
			return i;
		}
	}
	return -1;
}

int isSet(uint num, int i) {
	return (num >> i) & 1;
}

void set(uint& num, int i) {
	num |= (1 << i);
}

uint rearrangeOnes(uint num, int end, bool reversed = false) {

	int ones = 0;
	int start = 0;
	while(start < end) {
		ones += isSet(num, start++);
	}
	if(ones == 0) {
		return num;
	}

	int oneMask = (1 << ones) - 1;
	if(reversed) {
		oneMask <<= end - ones;
	}

	uint rearranged = num & ((~0) << end); //zeros from start to end exclusive
	return rearranged | oneMask;
}

uint bigger(uint num) {

	int pos = findPattern(num, 1, 2);
	if(pos != -1) {
		num = rearrangeOnes(num + (1 << pos), pos, 0);
	}
	return num;

}

uint smaller(uint num) {

	int pos = findPattern(num, 2, 2);
	if(pos != -1) {
		num = rearrangeOnes(num - (1 << pos), pos, true);
	}
	return num;
}

struct SwapOddEvenTest : public testing::Test {


};


TEST_F(SwapOddEvenTest, SomeTest) {

	int x = 10;
	int negated = 0;
	while(x > 0) {
		--negated; --x;
	}
	LOG(ERROR) << negated;

	ASSERT_EQ(bigger(1), 2);
	ASSERT_EQ(bigger(2), 4);
	ASSERT_EQ(bigger(4), 8);
	ASSERT_EQ(bigger(5), 6);
	ASSERT_EQ(bigger(20), 24);
	ASSERT_EQ(bigger(13948), 13948 + 131 - 64 - 32 - 16);

	ASSERT_EQ(smaller(2), 1);
	ASSERT_EQ(smaller(4), 2);
	ASSERT_EQ(smaller(6), 5);
	ASSERT_EQ(smaller(24), 20);
	ASSERT_EQ(smaller(35), 28);
	ASSERT_EQ(smaller(13948), 13946);
}

