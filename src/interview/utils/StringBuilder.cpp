/*
 * StringBuilder.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: adam
 */

#include "StringBuilder.h"

StringBuilder& StringBuilder::append(const std::string& str) {
	for(auto c : str) {
		buffer.push_back(c);
	}
}

std::string StringBuilder::str() {
	return std::string(buffer.begin(), buffer.end());
}
