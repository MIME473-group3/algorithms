/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "StringBuilder.h"
#include <map>

std::string englishRepresentation(long integer) {

	typedef std::map<int, std::string> MapType;
	static const MapType repr = {
			{1,"One"},
			{2,"Two"},
			{3,"Three"},
			{4,"Four"},
			{5,"Five"},
			{6,"Six"},
			{7,"Seven"},
			{8,"Eight"},
			{9,"Nine"},
			{10,"Ten"},
			{11,"Eleven"},
			{12,"Twelve"},
			{13,"Thriteen"},
			{14,"Fourteen"},
			{15,"Fifteen"},
			{16,"Sixteen"},
			{17,"Seventeen"},
			{18,"Eighteen"},
			{19,"Nineteen"},
			{20,"Twenty"},
			{30,"Thirty"},
			{40,"Fourty"},
			{50,"Fifty"},
			{60,"Sixty"},
			{70,"Seventy"},
			{80,"Eighty"},
			{90,"Ninety"},
			{100,"Hundred"},
			{1000,"Thousand"},
			{1000000,"Million"},
			{1000000000,"Billion"}
	};

	if(repr.find(integer) != repr.end()) {
		return repr.at(integer);
	}

	StringBuilder builder;
	auto it = static_cast<MapType::const_reverse_iterator>(++repr.upper_bound(integer));
	bool first = true;
	while(it != repr.rend()) {
		long times = integer / it->first;
		integer = integer % it->first;
		if(times >= 1) {
			if(first) {
				first = false;
			} else {
				builder.append(" ");
			}
			if(times > 1) {
				builder.append(englishRepresentation(times));
				builder.append(" ");
			}
			builder.append(it->second);
		}
		++it;
	}
	return builder.str();
}

struct EnglishRepresentationTest : public testing::Test {


};


TEST_F(EnglishRepresentationTest, InMapTest) {

	ASSERT_EQ(englishRepresentation(1), "One");
	ASSERT_EQ(englishRepresentation(10), "Ten");
	ASSERT_EQ(englishRepresentation(1000000), "Million");
}

TEST_F(EnglishRepresentationTest, NotInMapTest) {

	ASSERT_EQ(englishRepresentation(21), "Twenty One");
	ASSERT_EQ(englishRepresentation(135), "Hundred Thirty Five");
	ASSERT_EQ(englishRepresentation(257), "Two Hundred Fifty Seven");
	ASSERT_EQ(englishRepresentation(4785), "Four Thousand Seven Hundred Eighty Five");
	ASSERT_EQ(englishRepresentation(9100), "Nine Thousand Hundred");

	std::cout << englishRepresentation(973852611) << std::endl;
	std::cout << englishRepresentation(91022806116) << std::endl;

}

