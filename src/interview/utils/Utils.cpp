/*
 * Utils.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: adam
 */

#include "Utils.h"
#include "StringBuilder.h"

std::string Utils::binaryRepr(unsigned num, int length) {

	StringBuilder builder;
	for(int i = length - 1; i >= 0; --i) {
		if(num & 1 << i) {
			builder.append("1");
		} else {
			builder.append("0");
		}
	}
	return builder.str();
}

long Utils::factorial(int num) {
	long f = num;
	for(int i = 1; i < num; ++i) {
		f *= i;
	}
	return f;
}
