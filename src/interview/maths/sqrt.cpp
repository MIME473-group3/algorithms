/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <cmath>

/**
 * x = sqr(a)
 * x^2 = a
 * x^2 - a = 0
 */

double square_root(double num, double eps = 10e-4) {
	if(num == 0. || num == 1.) {
		return num;
	}
	double x = 1;
	double oldX = 0;
	while(std::abs(oldX - x) >= eps) {
		oldX = x;
		x = x - (x*x - num) / (2 * x);
	}
	return x;
}

struct SquareRootTest : public testing::Test {};


TEST_F(SquareRootTest, SomeTest) {

	ASSERT_DOUBLE_EQ(square_root(25., 10e-12), 5.);
	ASSERT_DOUBLE_EQ(square_root(1., 10e-12), 1.);
	ASSERT_DOUBLE_EQ(square_root(0.), 0.);
}

