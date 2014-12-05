/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

uint swapOddEven(uint num) {
	return ((num & 0xAAAAAAAA) >> 1) | ((num & 0x55555555) << 1);
}

struct SwapOddEvenTest : public testing::Test {


};


TEST_F(SwapOddEvenTest, SomeTest) {

	LOG(ERROR) << Utils::binaryRepr(10);
	LOG(ERROR) << Utils::binaryRepr(swapOddEven(10));
	LOG(ERROR) << Utils::binaryRepr(0xAAAAAAAA, 32);
	LOG(ERROR) << Utils::binaryRepr(swapOddEven(0xAAAAAAAA), 32);
	LOG(ERROR) << Utils::binaryRepr(0x55555555, 32);
	LOG(ERROR) << Utils::binaryRepr(swapOddEven(0x55555555), 32);
}

