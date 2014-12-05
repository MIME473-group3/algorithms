/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

std::vector<std::string> generatePermutations(char c, const std::string& str) {
	std::vector<std::string> permutations;
	if(str.size() == 1) {
		permutations.push_back(c + str);
		permutations.push_back(str + c);
	} else if(str.size() > 1){
		auto prevPerms = generatePermutations(str[0], str.substr(1));
		for(const auto& p : prevPerms) {
			permutations.push_back(c + p);
			for(int i = 1; i < p.size() ; ++i) {
				permutations.push_back(p.substr(i - 1, i) + c + p.substr(i));
			}
			permutations.push_back(p + c);
		}
	}
	return permutations;
}

std::vector<std::string> generatePermutations(const std::string& str) {
	if(str.empty()) {
		return std::vector<std::string>();
	}
	if(str.size() == 1) {
		return std::vector<std::string>(1, str);
	}
	return generatePermutations(str[0], str.substr(1));
}

struct GeneratePermutationsTest : public testing::Test {

	bool allUnique(const std::vector<std::string>& vec) {
		LOG(ERROR) << vec.size();
		std::set<std::string> s;
		for(const auto& str : vec) {
			if(s.count(str)) {
				return false;
			}
			s.insert(str);
		}
		return true;
	}
};

//TODO something's wrong; doesn't work for 5+ letters
TEST_F(GeneratePermutationsTest, SomeTest) {

	Utils::printVec(generatePermutations("A"));
	ASSERT_TRUE(allUnique(generatePermutations("A")));
	Utils::printVec(generatePermutations("AB"));
	ASSERT_TRUE(allUnique(generatePermutations("AB")));
	Utils::printVec(generatePermutations("ABC"));
	ASSERT_TRUE(allUnique(generatePermutations("ABC")));
	Utils::printVec(generatePermutations("ABCD"));
	ASSERT_TRUE(allUnique(generatePermutations("ABCD")));
	Utils::printVec(generatePermutations("ABCDE"));
	ASSERT_TRUE(allUnique(generatePermutations("ABCDE")));
}

