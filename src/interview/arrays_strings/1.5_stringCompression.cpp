/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"

int writeNumToBuffer(std::vector<char>& buffer, int index, int number) {
	std::string str = std::to_string(number);
	for(char c : str) {
		buffer[index++] = c;
	}
	return index;
}

std::string compressString(const std::string& str) {
	if(str.size() < 3) { //any string of size smaller than 3 cannot be made shorter than that
		return str;
	}

	int size = 2; //minimum size for a single char compressed string
	int count = 1; // minimum character count
	int base = 10; //used to track #occurences > base
	for(int i = 1; i < str.size(); ++i) {
		if(str[i - 1] != str[i]) {
			size += 2; // we need atleast two more characters to represent it
			base = 10;
			count = 1;
		} else {
			++count;
			if(count >= base) { // we need an additional character to represent it
				++size;
				base *= 10;
			}
		}
	}

	if(size >= str.size()) { //can't compress
		return str;
	}

	std::vector<char> buffer(size); //buffer to store the compressed stirng
	int i = 0, j = 0; //we'll need them later
	count = 1;
	for(; i < str.size() - 1; ++i) {
		if(str[i] == str[i + 1]) {
			++count;
		} else {
			buffer[j++] = str[i];
			j = writeNumToBuffer(buffer, j, count);
			count = 1;
		}
	}
	buffer[j++] = str[i]; //write the last character;
	writeNumToBuffer(buffer, j, count);

	return std::string(buffer.begin(), buffer.end());
}

struct StringCompressionTest : public testing::Test {


};

//#define ASSERT_EQ(x, y) std::cout << x << "\t" << y << std::endl;
TEST_F(StringCompressionTest, SomeTest) {

	ASSERT_EQ(compressString(""), "");
	ASSERT_EQ(compressString("a"), "a");
	ASSERT_EQ(compressString("aa"), "aa");
	ASSERT_EQ(compressString("aaa"), "a3");
	ASSERT_EQ(compressString("aabbccdd"), "aabbccdd");
	ASSERT_EQ(compressString("aabbcccdd"), "a2b2c3d2");
	ASSERT_EQ(compressString("baaaaaaaaaaaaaaac"), "b1a15c1");
}

