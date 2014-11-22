/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include <algorithm>

// with additional buffer
bool isPermutation(const std::string& str1, const std::string& str2) {
	if(str1.size() != str2.size()) { //strings of different sizes cannot be a permutation of each other
		return false;
	}

	static const int ASCII_SIZE = 256;
	int charCounter[ASCII_SIZE]; //assume ASCII
	for(int i = 0; i < ASCII_SIZE; ++i) {
		charCounter[i] = 0;
	}

	for(char c : str1) {
		charCounter[c] += 1;
	}
	for(char c : str2) {
		charCounter[c] -= 1;
	}
	for(int i = 0; i < ASCII_SIZE; ++i) {
		if(charCounter[i] != 0) {	//different numbers of ith character
			return false;
		}
	}
	return true;
}

//without additional buffer
bool isPermutation2(std::string& str1, std::string str2) {
	if(str1.size() != str2.size()) {
		return false;
	}
	std::sort(str1.begin(), str1.end());
	std::sort(str2.begin(), str2.end());
	return str1 == str2;
}


struct IsPermutationTest : public testing::Test {

	IsPermutationTest() : positiveExamples{
			{"", ""},
			{" ", " "},
			{"a", "a"},
			{"abcd", "dbca"},
			{"ab cd", "dcb a"}},

		negativeExamples{
			{"", " "},
			{"a", "b"}}

		{};

	std::vector<std::pair<std::string, std::string>> positiveExamples;
	std::vector<std::pair<std::string, std::string>> negativeExamples;
};


TEST_F(IsPermutationTest, Buffered) {

	for(auto& example : positiveExamples) {
		ASSERT_TRUE(isPermutation(example.first, example.second));
	}

	for(auto& example : negativeExamples) {
		ASSERT_FALSE(isPermutation(example.first, example.second));
	}
}

TEST_F(IsPermutationTest, NonBuffered) {

	for(auto& example : positiveExamples) {
		ASSERT_TRUE(isPermutation2(example.first, example.second));
	}

	for(auto& example : negativeExamples) {
		ASSERT_FALSE(isPermutation2(example.first, example.second));
	}
}

