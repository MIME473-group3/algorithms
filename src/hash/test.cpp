//#include <gtest/gtest.h>
//#include "aisdihashmap.h"
//
//template class AISDIHashMap<std::string, std::string>;
//
//template<>
//int AISDIHashMap<std::string, std::string>::InnerList::NodeCounter::count = 0;
//
//namespace {
//
//class HashBasicTest : public ::testing::Test {
//public:
//	HashBasicTest() {};
//	~HashBasicTest() {};
//};
//
//class HashAdvancedTest : public ::testing::Test {
//public:
//	HashAdvancedTest() {
//
//		map1["0"] = "1";
//		map1["2"] = "aha";
//		map1["4"] = "wef";
//
//		map2["2"] = "a";
//		map2["3"] = "b";
//		map2["4"] = "c";
//	};
//
//	~HashAdvancedTest() {};
//
//
//	AISDIHashMap<std::string, std::string> map1, map2, opp2;
//};
//
//TEST_F(HashBasicTest, InsertTest) {
//
//	AISDIHashMap<std::string, std::string> map;
//	std::pair<AISDIHashMap<std::string, std::string>::iterator, bool> result;
//
//	result = map.insert(std::make_pair("0", "a"));
//	EXPECT_TRUE(result.second);
//	EXPECT_EQ(result.first->first, "0");
//	EXPECT_EQ(result.first->second, "a");
//	result = map.insert(std::make_pair("4", "b"));
//	EXPECT_TRUE(result.second);
//	EXPECT_EQ(result.first->first, "4");
//	EXPECT_EQ(result.first->second, "b");
//	result = map.insert(std::make_pair("16", "c"));
//	EXPECT_TRUE(result.second);
//	EXPECT_EQ(result.first->first, "16");
//	EXPECT_EQ(result.first->second, "c");
//
//	result = map.insert(std::make_pair("0", "zz"));
//	EXPECT_FALSE(result.second);
//	EXPECT_EQ(result.first->first, "0");
//	EXPECT_EQ(result.first->second, "a");
//}
//
//TEST_F(HashBasicTest, OperatorInsertTest) {
//
//	AISDIHashMap<std::string, std::string> map;
//	map["0"] = "a";
//	map["0"] = "h";
//	EXPECT_EQ(map["0"], "h");
//	map["4"] = "b";
//	EXPECT_EQ(map["4"], "b");
//	map["16"] = "c";
//	EXPECT_EQ(map["16"], "c");
//
//
//	EXPECT_EQ(map["0"], "h");
//	EXPECT_EQ(map["4"], "b");
//	EXPECT_EQ(map["16"], "c");
//}
//
//TEST_F(HashBasicTest, SizeTest) {
//
//	AISDIHashMap<std::string, std::string> map;
//	EXPECT_EQ(map.size(), 0);
//	map["0"] = "a";
//	EXPECT_EQ(map.size(), 1);
//	map["4"] = "b";
//	EXPECT_EQ(map.size(), 2);
//	map["16"] = "c";
//	EXPECT_EQ(map.size(), 3);
//}
//
//TEST_F(HashBasicTest, EmptyIteratorTest) {
//
//	AISDIHashMap<std::string, std::string> map;
//	auto it = map.begin();
//	auto end =  map.end();
//
//	EXPECT_TRUE(it == end);
//	EXPECT_TRUE(++it == end);
//	EXPECT_TRUE(++it == end);
//	EXPECT_TRUE(++it == end);
//	ASSERT_TRUE(it == end);
//	EXPECT_TRUE(it++ == end);
//	EXPECT_TRUE(it++ == end);
//	EXPECT_TRUE(it++ == end);
//	EXPECT_TRUE(--it == end);
//	EXPECT_TRUE(--it == end);
//	EXPECT_TRUE(--it == end);
//	EXPECT_TRUE(it-- == end);
//	EXPECT_TRUE(it-- == end);
//	EXPECT_TRUE(it-- == end);
//}
//
//TEST_F(HashAdvancedTest, EndsNotEqual) {
//
//	ASSERT_FALSE(map1.end() == map2.end());
//	ASSERT_TRUE(map1.end() == map1.end());
//	ASSERT_TRUE(map2.end() == map2.end());
//}
//
//TEST_F(HashAdvancedTest, FindTest) {
//
//	AISDIHashMap<std::string, std::string>::iterator it = map1.find("1");
//	AISDIHashMap<std::string, std::string>::iterator end = map1.end();
//
//	EXPECT_TRUE(it ==  end);
//	EXPECT_TRUE(map1.find("0")->first == "0");
//	EXPECT_TRUE(map1.find("0")->second == "1");
//
//	EXPECT_TRUE(map1.find("2")->first == "2");
//	EXPECT_TRUE(map1.find("2")->second == "aha");
//
//	EXPECT_TRUE(map1.find("4")->first == "4");
//	EXPECT_TRUE(map1.find("4")->second ==  "wef");
//}
//
//TEST_F(HashAdvancedTest, IteratorTest) {
//
//	auto it = map2.begin();
//
//	EXPECT_EQ(it->second, "a");
//	EXPECT_EQ((++it)->second, "b");
//	EXPECT_EQ((it)->second, "b");
//	EXPECT_EQ((it++)->second, "b");
//	EXPECT_EQ((it)->second, "c");
//
//	it = map2.end();
//	ASSERT_EQ(it->second, "");
//	EXPECT_EQ((--it)->second, "c");
//	EXPECT_EQ((it)->second, "c");
//
//
//	EXPECT_EQ((--it)->second, "b");
//	EXPECT_EQ((it)->second, "b");
//
//	EXPECT_EQ((++it)->second, "c");
//	EXPECT_EQ((it)->second, "c");
//
//	EXPECT_EQ((it--)->second, "c");
//	EXPECT_EQ((it)->second, "b");
//
//	EXPECT_EQ((it++)->second, "b");
//	EXPECT_EQ((it)->second, "c");
//}
//
//TEST_F(HashAdvancedTest, EraseTest) {
//
//	ASSERT_EQ(map2.size(), 3);
//	map2.erase("4");
//	ASSERT_EQ(map2.size(), 2);
//	ASSERT_TRUE(map2.find("4") == map2.end());
//	map2.erase("3");
//	ASSERT_EQ(map2.size(), 1);
//	ASSERT_TRUE(map2.find("3") == map2.end());
//	map2.erase("2");
//	ASSERT_EQ(map2.size(), 0);
//	ASSERT_TRUE(map2.find("2") ==  map2.end());
//}
//TEST_F(HashAdvancedTest, ClearTest) {
//	ASSERT_EQ(map2.size(), 3);
//	map2.clear();
//	ASSERT_EQ(map2.size(), 0);
//}
//
//TEST_F(HashAdvancedTest, BandEraseTest) {
//
//	ASSERT_EQ(map1.size(), 3);
//	EXPECT_TRUE(map1.erase(map1.begin(), map1.end()) == map1.end());
//	ASSERT_EQ(map1.size(), 0);
//
//	ASSERT_EQ(map2.size(), 3);
//	auto begin = map2.begin();
//	auto second = ++++map2.begin();
//	EXPECT_TRUE(map2.erase(begin, second) == second);
//	ASSERT_EQ(map2.size(), 1);
//}
//
//
//
//}
//
//
//
//int main(int argc, char** argv) {
//
//	::testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}
