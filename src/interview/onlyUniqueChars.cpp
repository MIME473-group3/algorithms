#include "gtest/gtest.h"
#include <iostream>
#include <algorithm>

bool onlyUniqueChars(const std::string& str) {
	if(str.size() < 2) {	//any string with less than 2 char cannot have non-unique ones
		return true;
	}

	//assume extended ASCII chars
	bool isUnique[256];
	for(int i = 0; i < 256; ++i) {
		isUnique[i] = true;
	}

	for(char c : str) {
		if(!isUnique[c]) {	//char c has already been visited
			return false;
		}
		isUnique[c] = false; //mark as visited
	}
	return true; //checked all characters
}

bool onlyUniqueChars2(std::string& str) {

	if(str.size() < 2) { //any string with less than 2 chars cannot have any non-unique ones
		return true;
	}
	std::sort(str.begin(), str.end()); //after this all non unique chars will be adjacent to eachother
	for(int i = 1; i < str.size(); ++i) {
		if(str[i - 1] == str[i]) { //found non unique chars
			return false;
		}
	}
	return true;
}

class Test : public testing::Test {
public:
	static std::string strs[6];
};

std::string Test::strs[] = {"", "a", "ab", "abc", "aa", "abcda"};


TEST_F(Test, WithAdditionalMemory) {

	ASSERT_TRUE(onlyUniqueChars(strs[0]));
	ASSERT_TRUE(onlyUniqueChars(strs[1]));
	ASSERT_TRUE(onlyUniqueChars(strs[2]));
	ASSERT_TRUE(onlyUniqueChars(strs[3]));
	ASSERT_FALSE(onlyUniqueChars(strs[4]));
	ASSERT_FALSE(onlyUniqueChars(strs[5]));
}

TEST_F(Test, SortingBased) {

	ASSERT_TRUE(onlyUniqueChars2(strs[0]));
	ASSERT_TRUE(onlyUniqueChars2(strs[1]));
	ASSERT_TRUE(onlyUniqueChars2(strs[2]));
	ASSERT_TRUE(onlyUniqueChars2(strs[3]));
	ASSERT_FALSE(onlyUniqueChars2(strs[4]));
	ASSERT_FALSE(onlyUniqueChars2(strs[5]));
}

