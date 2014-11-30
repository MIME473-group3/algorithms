/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

std::string toFixedPointString(double d) {

	std::vector<char> buffer(33, '\0');
	buffer[0] = '0';
	buffer[1] = '.';
	double weight = 0.5;
	for(int i = 2; i < 33; ++i) {
		if(weight <= d) {
			d -= weight;
			buffer[i] = '1';
		} else {
			buffer[i] = '0';
		}
		if(d == 0.0) {
			return "exact: " + std::string(buffer.begin(), buffer.end());
		}
		weight /= 2;
	}
	return "error " + std::string(buffer.begin(), buffer.end());
}

struct Test : public testing::Test {


};


TEST_F(Test, SomeTest) {

	LOG(ERROR) << toFixedPointString(0.754);
}

