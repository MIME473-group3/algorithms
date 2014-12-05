/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <unordered_set>
#include <glog/logging.h>
#include <cmath>

std::unordered_set<std::string> validParentheses(int n) {
	std::unordered_set<std::string> result;
	if(n <= 0) {
		return result;
	}
	if(n == 1) {
		result.insert("()");
	}

	for(const auto& entry : validParentheses(n - 1)) {

		result.insert("()" + entry);
		for(int i = 0; i < entry.size(); ++i) {
			if(entry[i] == '(') {
				result.insert(entry.substr(0, i + 1) + "()" + entry.substr(i + 1));
			}
		}
	}
	return result;
}

struct Test : public testing::Test {


};

/**
 * x = sqr(a)
 * x^2 = a
 * x^2 - a = 0
 */

double Sqrt(double num, double eps = 10e-4) {
	double x = 1;
	double oldX = 0;
	while(std::abs(oldX - x) >= eps) {
		oldX = x;
		x = x - (x*x - num) / (2 * x);
	}
	return x;
}


TEST_F(Test, SomeTest) {

	LOG(ERROR) << Sqrt(25.0, 10e-12);
//	auto a = validParentheses(15);
//	Utils::printContainer(a)
//	LOG(ERROR) << a.size();
}

