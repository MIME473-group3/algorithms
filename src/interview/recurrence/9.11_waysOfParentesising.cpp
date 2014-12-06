/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <map>
#include <unordered_map>
#include <glog/logging.h>


namespace std {
	template<> struct hash<std::pair<std::string, char>> {

		std::hash<std::string> hashHelper;
		size_t operator()(const std::pair<std::string, char>& x) const {
			return hashHelper(x.first + x.second);
		}
	};
}

int xorWays(const std::string& a, const std::string& b, char result);
int orWays(const std::string& a, const std::string& b, char result);
int andWays(const std::string& a, const std::string& b, char result);

int waysOfParentesising(const std::string& expr, char result) {
	static std::map<char, int(*)(const std::string&, const std::string&, char)> wayMap = {{'|', orWays}, {'&', andWays}, {'^', xorWays}};
	static std::unordered_map<std::pair<std::string, char>, int> wayCache;

	if(expr.empty() || (result != '0' && result != '1')) {
		return 0;
	}
	if(expr.size() == 1) {
		if(expr[0] == result) {
			return 1;
		}
		return 0;
	}

	auto it = wayCache.find(std::make_pair(expr, result));
	if(it != wayCache.end()) {
		return it->second;
	}

	int ways = 0;
	for(int i = 1; i < expr.size() - 1; ++i) {
		auto it = wayMap.find(expr[i]);
		if(it != wayMap.end()) {
			ways += it->second(expr.substr(0, i), expr.substr(i + 1), result);
		}
	}

	wayCache.emplace(std::make_pair(expr, result), ways);

	return ways;
}

int xorWays(const std::string& a, const std::string& b, char result) {
	if(result == '1') {
		return waysOfParentesising(a, '1') * waysOfParentesising(b, '0') + waysOfParentesising(a, '0') * waysOfParentesising(b, '1');
	}
	return waysOfParentesising(a, '0') * waysOfParentesising(b, '0') + waysOfParentesising(a, '1') * waysOfParentesising(b, '1');
}

int orWays(const std::string& a, const std::string& b, char result) {
	if(result == '1') {
		return waysOfParentesising(a, '1') * waysOfParentesising(b, '1') + waysOfParentesising(a, '1') * waysOfParentesising(b, '0') + waysOfParentesising(a, '0') * waysOfParentesising(b, '1'); ;
	}
	return waysOfParentesising(a, '0') * waysOfParentesising(b, '0');
}

int andWays(const std::string& a, const std::string& b, char result) {
	if(result == '1') {
		return waysOfParentesising(a, '1') * waysOfParentesising(b, '1');
	}
	return waysOfParentesising(a, '0') * waysOfParentesising(b, '0') + waysOfParentesising(a, '1') * waysOfParentesising(b, '0') + waysOfParentesising(a, '0') * waysOfParentesising(b, '1');
}

struct WaysOfParentesisingTest : public testing::Test {};


TEST_F(WaysOfParentesisingTest, SomeTest) {

	ASSERT_EQ(waysOfParentesising("1^0|0|1", '0'), 2);
	ASSERT_EQ(waysOfParentesising("1^0|0|1|1^0|0|1", '0'), 136);
}

