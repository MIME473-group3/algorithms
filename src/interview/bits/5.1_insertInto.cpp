/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <algorithm>

int insertInto(int dest, int source, int j, int i) {

	if(j < i) {
		std::swap(i, j);
	}

	int mask = ~(((~0) << (j + 1)) ^ ((~0) << i));
	return (dest & mask) | (source << i);
}

struct InsertIntoTest : public testing::Test {


};


TEST_F(InsertIntoTest, SomeTest) {

	int a = insertInto(64, 3, 5, 3);
	std::cout << a << std::endl;
	ASSERT_EQ(a, 88);

	a = insertInto(255, 0, 5, 1);
	std::cout << a << std::endl;
	ASSERT_EQ(a, 193);

	ASSERT_EQ(insertInto(255, 0, 7, 7), 127);
	ASSERT_EQ(insertInto(129, 7, 2, 0), 135);
	ASSERT_EQ(insertInto(32, 3, 7, 6), 224);


}

