/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

void generatePermutations(std::vector<std::string>& result, const std::string& prefix, const std::string& str, int index) {
	if(index == str.size()) {
		result.push_back(prefix);
		return;
	}

	for(int i = 0; i <= prefix.size(); ++i) {
		auto newPrefix = prefix.substr(0, i) + str[index] + prefix.substr(i);
		generatePermutations(result, newPrefix, str, index + 1);
	}
}


std::vector<std::string> generatePermutations(const std::string& str) {
	std::vector<std::string> result;
	result.reserve(Utils::factorial(str.size()));
	generatePermutations(result, "", str, 0);
	return result;
}

struct GeneratePermutationsTest : public testing::Test {};

TEST_F(GeneratePermutationsTest, SomeTest) {

	Utils::printVec(generatePermutations("A"));
	ASSERT_TRUE(Utils::allEntriesUnique(generatePermutations("A")));
	Utils::printVec(generatePermutations("AB"));
	ASSERT_TRUE(Utils::allEntriesUnique(generatePermutations("AB")));
	Utils::printVec(generatePermutations("ABC"));
	ASSERT_TRUE(Utils::allEntriesUnique(generatePermutations("ABC")));
	Utils::printVec(generatePermutations("ABCD"));
	ASSERT_TRUE(Utils::allEntriesUnique(generatePermutations("ABCD")));
	Utils::printVec(generatePermutations("ABCDE"));
	ASSERT_TRUE(Utils::allEntriesUnique(generatePermutations("ABCDE")));
}

