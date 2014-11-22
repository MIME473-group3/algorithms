/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"

bool isSubstring(const std::string& base, const std::string& pattern) {

	std::string::size_type size = base.size();
	if(pattern.size() > size || pattern.size() == 0) {
		return false;
	}

	if(base.find(pattern) == std::string::npos) {
		return false;
	}
	return true;
}

bool isRotation(const std::string& base, const std::string& pattern) {
	if(base.size() != pattern.size() || pattern.empty()) {
		return false;
	}
	return isSubstring(base + base, pattern);
}

struct IsRotationTest : public testing::Test {


};


TEST_F(IsRotationTest, IsSubstringTest) {

	std::vector<std::pair<std::string, std::string>> posTestExamples = {
			{" ", " "},
			{"a", "a"},
			{"abba", "abba"},
			{"aba", "ab"},
			{"aba", "ba"}
	};

	std::vector<std::pair<std::string, std::string>> negTestExamples = {
			{"", ""},
			{" ", ""},
			{"", " "},
			{"aba", "abb"}
	};

	for(auto& example : posTestExamples) {
		ASSERT_TRUE(isSubstring(example.first, example.second));
	}

	for(auto& example : negTestExamples) {
		ASSERT_FALSE(isSubstring(example.first, example.second));
	}

}

TEST_F(IsRotationTest, IsRotationTest) {

	std::vector<std::pair<std::string, std::string>> posTestExamples = {
			{" ", " "},
			{"a", "a"},
			{"abba", "abba"},
			{"abba", "bbaa"},
			{"abcda", "cdaab"}
	};

	std::vector<std::pair<std::string, std::string>> negTestExamples = {
			{"", ""},
			{" ", ""},
			{"", " "},
			{"aba", "abb"}
	};

	for(auto& example : posTestExamples) {
		ASSERT_TRUE(isRotation(example.first, example.second));
	}

	for(auto& example : negTestExamples) {
		ASSERT_FALSE(isRotation(example.first, example.second));
	}
}

