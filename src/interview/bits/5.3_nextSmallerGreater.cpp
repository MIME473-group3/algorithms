/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

uint findPattern(uint where, int pattern, int length) {

	for(int i = 0; i < sizeof(where) * 8; ++i) {

		unsigned mask = ((~0) << length + i) ^ ((~0) << i);
		int match = (where & mask) ^ (pattern << i);
		if(match == 0) {
			return i;
		}
	}
}

int isSet(uint num, int i) {
	return (num & (1 << i)) > 0;
}

void set(uint& num, int i) {
	num |= (1 << i);
}

uint rearrange(uint num, int end, int start, bool reversed = false) {
	if(end <= start) {
		return num;
	}
	int ones = 0;
	uint rearranged = num & ((~0) << end); //zeros from start to end exclusive
	while(start < end) {
		ones += isSet(num, start++);
	}
//	for(int i = 0; i < ones; ++i) {
//		set(rearranged, i);
//	}
	// 1 << ones => 1 at position ones
	// (1 << ones) - 1 => 1s at positions (ones-1) to 0 inclusive
	int oneMask = (1 << ones) - 1;
	if(reversed) {
		oneMask <<= end - ones;
	}
	return rearranged | oneMask;
}

uint bigger(uint num) {

	uint i = findPattern(num, 1, 2);
	return rearrange(num + (1 << i), i, 0);

}

uint smaller(uint num) {

	uint i = findPattern(num, 2, 2);
	return rearrange(num - (1 << i), i, 0, true);
}

struct Test : public testing::Test {


};


TEST_F(Test, SomeTest) {

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

