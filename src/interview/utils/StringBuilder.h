/*
 * StringBuilder.h
 *
 *  Created on: Nov 24, 2014
 *      Author: adam
 */

#ifndef INTERVIEW_STRINGBUILDER_H_
#define INTERVIEW_STRINGBUILDER_H_

#include <vector>
#include <string>

class StringBuilder {
	std::vector<char> buffer;

public:
	StringBuilder(int size) {
		buffer.reserve(size);
	}

	StringBuilder() : StringBuilder(1024) {}
	StringBuilder& append(const std::string& str);
	std::string str();
};

#endif /* INTERVIEW_STRINGBUILDER_H_ */
