/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include <vector>


void reverseString(char* str) {

	char* last = str;
	while(*last) { //increment until it points at NULL
		++last;
	}
	--last; //decrement so that it points at the last char
	while(last > str) {
		char tmp = *last;
		*last = *str;
		*str = tmp;
		++str;
		--last;
	}
}

class Test : public testing::Test {


	void SetUp() {


		std::vector<std::string> strs = {"", "a", "aa", "ab", "abc", "ab_cb"};
		for(int i = 0; i < strs.size(); ++i) {
			char* str = new char[strs[i].size() + 1];
			strcpy(str, strs[i].c_str());
			testStrings.push_back(str);
		}

		reversed.push_back("");
		reversed.push_back("a");
		reversed.push_back("aa");
		reversed.push_back("ba");
		reversed.push_back("cba");
		reversed.push_back("bc_ba");
	}

	void TearDown() {
		for(int i = 0; i < testStrings.size(); ++i) {
			delete[] testStrings[i];
		}
	}

public:
	std::vector<char*> testStrings;
	std::vector<const char*> reversed;
};


TEST_F(Test, someTest) {

	for(char* str : testStrings) {
		reverseString(str);
	}

	for(int i = 0; i < testStrings.size(); ++i) {
		ASSERT_STREQ(testStrings[i], reversed[i]);
	}

}
