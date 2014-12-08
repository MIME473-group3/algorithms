/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"

int afterSpaces(const std::vector<char>& str, int start) {
	while(start < str.size() && std::isspace(str[start])) {
		++start;
	}
	return start;
}

void reverseChars(std::vector<char>& str, int start, int end) {
	while(start < end) {
		std::swap(str[start], str[end]);
		++start;
		--end;
	}
}

std::string reverseWordOrder(const std::string& str) {
	if(str.empty()) {
		return str;
	}

	std::vector<char> buffer(str.begin(), str.end());
	int start = afterSpaces(buffer, 0);
	int i = start;
	int j = i + 1;
	while(j < buffer.size()) {
		while(j < buffer.size() && !std::isspace(buffer[j])) {
			++j;
		}
		reverseChars(buffer, i, j - 1);
		i = afterSpaces(buffer, j);
		j = i + 1;
	}
	reverseChars(buffer, start, buffer.size() - 1);
	return std::string(buffer.begin(), buffer.end());
}

struct ReverseWordOrderTest : public testing::Test {


};


TEST_F(ReverseWordOrderTest, SomeTest) {

	ASSERT_EQ(reverseWordOrder("Idę do domu"), ("domu do Idę"));
	ASSERT_EQ(reverseWordOrder("   Ide do domu"), ("   domu do Ide"));
}

