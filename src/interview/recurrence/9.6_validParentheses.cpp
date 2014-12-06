/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

void validParentheses(std::vector<std::string>& result, std::vector<char>& buffer, int leftRem, int rightRem, int index) {
	if(index == buffer.size()) {
		result.emplace_back(buffer.begin(), buffer.end());
	}

	if(leftRem) {
		buffer[index] = '(';
		validParentheses(result, buffer, leftRem - 1, rightRem, index + 1);
	}

	if(rightRem && rightRem > leftRem) {
		buffer[index] = ')';
		validParentheses(result, buffer, leftRem, rightRem - 1, index + 1);
	}
}

std::vector<std::string> validParentheses(int N) {
	std::vector<std::string> result;
	std::vector<char> buffer(2 * N);
	validParentheses(result, buffer, N, N, 0);
	return result;
}


struct ValidParenthesesTest : public testing::Test {};


TEST_F(ValidParenthesesTest, SomeTest) {
	auto a = validParentheses(15);
	Utils::printContainer(a);
	LOG(ERROR) << a.size();
}

