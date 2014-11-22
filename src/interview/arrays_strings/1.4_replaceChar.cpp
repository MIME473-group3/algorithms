/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"

std::string replaceChar(const std::string& str, char c, const std::string& rep) {

	int count = 0;
	for(int i = 0; i < str.size(); ++i) {	//	count the number of c occurences
		if(str[i] == c) {
			++count;
		}
	}

	int size = str.size() + count * (rep.size() - 1); //size of the new string; each copied rep will occupy the space previously occupied by c + rep.size() - 1 chars
	std::vector<char> resultString(size);	//buffer for the new string
	for(int i = str.size() - 1, j = size - 1; i >= 0; --i, --j) { //	iterate backwards over str
		if(str[i] == c) { //we have to replace
			j -= (rep.size() - 1); // shift pointer to the place where rep will start in the resultString
			for(int k = 0; k < rep.size(); ++k) {
				resultString[j + k] = rep[k];
			}
		} else {	//	just copy a single char from str
			resultString[j] = str[i];
		}
	}

	return std::string(resultString.begin(), resultString.end());
}

struct ReplaceStringTest : public testing::Test {

	ReplaceStringTest() :
		rep("%20"),
		toReplace(' '),
		testStrings{
			{"", ""},
			{" ", rep},
			{"ab", "ab"},
			{"a b", "a" + rep + "b"},
			{"a bc d", "a" + rep + "bc" + rep + "d"},
			{"abc   ", "abc" + rep + rep + rep}

	}
	{};

	const std::string rep;
	char toReplace;
	std::vector<std::pair<std::string, std::string>> testStrings;
};


TEST_F(ReplaceStringTest, PositiveExample) {

	for(auto& example : testStrings) {
		ASSERT_EQ(replaceChar(example.first, toReplace, rep), example.second);
	}
}

