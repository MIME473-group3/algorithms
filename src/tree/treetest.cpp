#include <gtest/gtest.h>
#include "TreeMap.h"
#include <string>

namespace {

class BasicTest : public ::testing::Test {
public:
	BasicTest() {};
	~BasicTest() {};
};

class AdvancedTest : public ::testing::Test {
public:
	AdvancedTest() {

		map1[0] = "1";
		map1[2] = "aha";
		map1[4] = "wef";

		map2[2] = "a";
		map2[0] = "g";
		map2[1] = "h";
		map2[-1] = "i";
		map2[3] = "b";
		map2[4] = "c";

		opp2[4] = "a";
		opp2[3] = "b";
		opp2[2] = "c";
	};

	~AdvancedTest() {};


	TreeMap map1, map2, opp2;
};

TEST_F(BasicTest, InsertTest) {

	TreeMap map;
//	std::pair<TreeMap::iterator, bool> result;
	auto result = map.insert(std::make_pair(1, "a"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 1);
	EXPECT_EQ(result.first->second, "a");
	result = map.insert(std::make_pair(4, "b"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 4);
	EXPECT_EQ(result.first->second, "b");
	result = map.insert(std::make_pair(16, "c"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 16);
	EXPECT_EQ(result.first->second, "c");

	result = map.insert(std::make_pair(3, "s"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 3);
	EXPECT_EQ(result.first->second, "s");

	result = map.insert(std::make_pair(5, "h"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 5);
	EXPECT_EQ(result.first->second, "h");

	result = map.insert(std::make_pair(9, "fsdf"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 9);
	EXPECT_EQ(result.first->second, "fsdf");

	result = map.insert(std::make_pair(12, "kk"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 12);
	EXPECT_EQ(result.first->second, "kk");

	result = map.insert(std::make_pair(1, "zz"));
	EXPECT_FALSE(result.second);
	EXPECT_EQ(result.first->first, 1);
	EXPECT_EQ(result.first->second, "a");
}

TEST_F(BasicTest, OperatorInsertTest) {

	TreeMap map;
	map[0] = "a";
	EXPECT_EQ(map[0], "a");
	map[4] = "b";
	EXPECT_EQ(map[4], "b");
	map[16] = "c";
	EXPECT_EQ(map[16], "c");


	EXPECT_EQ(map[0], "a");
	EXPECT_EQ(map[4], "b");
	EXPECT_EQ(map[16], "c");
}

TEST_F(BasicTest, SizeTest) {

	TreeMap map;
	EXPECT_EQ(map.size(), 0);
	map[0] = "a";
	EXPECT_EQ(map.size(), 1);
	map[4] = "b";
	EXPECT_EQ(map.size(), 2);
	map[16] = "c";
	EXPECT_EQ(map.size(), 3);
}

TEST_F(BasicTest, AddingBiggerElements) {

	TreeMap m;

	for(int i = 0; i < 100; ++i) {
		m[i] = std::to_string(i);
		ASSERT_EQ(m.size(), (i + 1));
	}
}

TEST_F(BasicTest, AddingSmallerElements) {

	TreeMap m;

	for(int i = 100; i < 0; --i) {
		m[i] = std::to_string(i);
		ASSERT_EQ(m.size(), i + 1);
	}
}

TEST_F(BasicTest, AddingAlternatingElements) {

	TreeMap m;

	for(int i = 1; i < 101; ++i) {
		int l = i;
		m[l] = std::to_string(l);
		l = l * 371 % 100;
		m[l] = std::to_string(l);
		l = l * 973 % 117;
		m[l] = std::to_string(l);
		l = - (l*l) & 111;
		m[l] = std::to_string(l);
	}
}



TEST_F(AdvancedTest, EndsNotEqual) {

	ASSERT_FALSE(map1.end() == map2.end());
	ASSERT_TRUE(map1.end() == map1.end());
	ASSERT_TRUE(map2.end() == map2.end());
}

TEST_F(AdvancedTest, FindTest) {

	TreeMap::iterator it = map1.find(1);
	TreeMap::iterator end = map1.end();

	EXPECT_TRUE(it ==  end);
	EXPECT_EQ(map1.find(0)->first, 0);
	EXPECT_EQ(map1.find(0)->second, "1");

	EXPECT_EQ(map1.find(2)->first, 2);
	EXPECT_EQ(map1.find(2)->second, "aha");

	EXPECT_EQ(map1.find(4)->first, 4);
	EXPECT_EQ(map1.find(4)->second,  "wef");
}

TEST_F(AdvancedTest, EmptyFindTest) {

	TreeMap m;
	EXPECT_TRUE(m.find(0) == m.end());
	EXPECT_TRUE(m.find(1) == m.end());
	EXPECT_TRUE(m.find(-1) == m.end());
	EXPECT_TRUE(m.find(2) == m.end());

	m[1] = "muha";

	EXPECT_TRUE(m.find(1) != m.end());
	EXPECT_TRUE(m.find(1) == m.begin());
	EXPECT_EQ(m.find(1)->first, 1);
	EXPECT_EQ(m.find(1)->second, "muha");
}


TEST_F(AdvancedTest, EmptyIteratorTest) {

	TreeMap map;
	auto it = map.begin();
	EXPECT_TRUE(it == map.end());
	EXPECT_TRUE(++it == map.end());
	EXPECT_TRUE(++it == map.end());
	EXPECT_TRUE(++it == map.end());
	EXPECT_TRUE(it++ == map.end());
	EXPECT_TRUE(it++ == map.end());
	EXPECT_TRUE(it++ == map.end());
	EXPECT_TRUE(--it == map.end());
	EXPECT_TRUE(--it == map.end());
	EXPECT_TRUE(--it == map.end());
	EXPECT_TRUE(it-- == map.end());
	EXPECT_TRUE(it-- == map.end());
	EXPECT_TRUE(it-- == map.end());
}

TEST_F(AdvancedTest, IteratorTest) {

	auto it = map2.begin();
	ASSERT_EQ(it->second, "i");
	EXPECT_EQ((++it)->second, "g");
	EXPECT_EQ((it)->second, "g");
	EXPECT_EQ((it++)->second, "g");
	EXPECT_EQ((it)->second, "h");

	it = map2.end();
//	ASSERT_EQ(it->second, "");
	EXPECT_EQ((--it)->second, "c");
	ASSERT_EQ((it)->second, "c");


	EXPECT_EQ((--it)->second, "b");
	EXPECT_EQ((it)->second, "b");

	EXPECT_EQ((++it)->second, "c");
	EXPECT_EQ((it)->second, "c");

	EXPECT_EQ((it--)->second, "c");
	EXPECT_EQ((it)->second, "b");

	EXPECT_EQ((it++)->second, "b");
	EXPECT_EQ((it)->second, "c");
}

TEST_F(AdvancedTest, BigIteratorTest){

	auto it = map2.begin();
	EXPECT_EQ(it->first, -1);
	EXPECT_EQ((++it)->first, 0);
	EXPECT_EQ((++it)->first, 1);
	EXPECT_EQ((++it)->first, 2);
	EXPECT_EQ((++it)->first, 3);
	EXPECT_EQ((++it)->first, 4);

	EXPECT_TRUE((++it)==map2.end());
	EXPECT_EQ((--it)->first, 4);
	EXPECT_EQ((--it)->first, 3);
	EXPECT_EQ((--it)->first, 2);
	EXPECT_EQ((--it)->first, 1);
	EXPECT_EQ((--it)->first, 0);
	EXPECT_EQ((--it)->first, -1);
}

TEST_F(AdvancedTest, EraseTest) {

	ASSERT_EQ(map2.size(), 6);
	map2.erase(4);
	ASSERT_EQ(map2.size(), 5);
	ASSERT_TRUE(map2.find(4) == map2.end());
	map2.erase(3);
	ASSERT_EQ(map2.size(), 4);
	ASSERT_TRUE(map2.find(3) == map2.end());
	map2.erase(2);
	ASSERT_EQ(map2.size(), 3);
	ASSERT_TRUE(map2.find(2) ==  map2.end());
}

TEST_F(AdvancedTest, BandEraseTest) {

	ASSERT_EQ(map1.size(), 3);
	EXPECT_TRUE(map1.erase(map1.begin(), map1.end()) == map1.end());
	ASSERT_EQ(map1.size(), 0);

	ASSERT_EQ(map2.size(), 6);
	auto begin = map2.begin();
	auto third = ++++map2.begin();
	ASSERT_EQ(third->first, 1);
	EXPECT_TRUE(map2.erase(begin, third) == third);
	ASSERT_EQ(third->first, 1);

	ASSERT_EQ(map2.size(), 4);


}

TEST_F(AdvancedTest, InfoEqTest) {

	EXPECT_TRUE(map2.info_eq(map2));

//	TreeMap map, map3;
//	for(TreeMap::iterator it = map2.begin(); it != map2.end(); ++it)
//		map.insert(*it);
//
//	for(TreeMap::iterator it = map.begin(); it != map.end(); ++it)
//			map3.insert(*it);
//
//	EXPECT_TRUE(map2.info_eq(map3));
//	EXPECT_TRUE(map3.info_eq(map2));
//
//	EXPECT_FALSE(opp2.info_eq(map1));
//	EXPECT_FALSE(map1.info_eq(opp2));

//	TreeMap m1, m2;
//	EXPECT_TRUE(m1.info_eq(m2));

}

TEST_F(AdvancedTest, StructEqTest) {

	EXPECT_TRUE(map2.struct_eq(map2));

	EXPECT_FALSE(opp2.struct_eq(map2));
	EXPECT_FALSE(map2.struct_eq(opp2));

	EXPECT_FALSE(opp2.struct_eq(map1));
	EXPECT_FALSE(map1.struct_eq(opp2));
}

TEST_F(AdvancedTest, CompareEmptyMaps) {

	TreeMap m1, m2;
	EXPECT_EQ(m1, m2);
	EXPECT_EQ(m2, m1);
	EXPECT_EQ(m2, m2);
	EXPECT_EQ(m1, m1);

	EXPECT_TRUE(m1.info_eq(m2));
	EXPECT_TRUE(m2.info_eq(m1));
	EXPECT_TRUE(m1.info_eq(m1));
	EXPECT_TRUE(m2.info_eq(m2));

	EXPECT_TRUE(m1.struct_eq(m2));
	EXPECT_TRUE(m2.struct_eq(m1));
	EXPECT_TRUE(m1.struct_eq(m1));
	EXPECT_TRUE(m2.struct_eq(m2));
}

TEST_F(AdvancedTest, FillAndCompareMaps) {

	TreeMap m1, m2;
	m1[0] = "aha";
	m2[0] = "aha";
	EXPECT_TRUE(m1.info_eq(m2));
	EXPECT_TRUE(m2.info_eq(m1));

	m1[1] = "aha";
	m2[1] = "aha";
	EXPECT_TRUE(m1.info_eq(m2));
	EXPECT_TRUE(m2.info_eq(m1));

	m1[-1] = "aha";
	m2[-1] = "aha";
	EXPECT_TRUE(m1.info_eq(m2));
	EXPECT_TRUE(m2.info_eq(m1));
}

TEST_F(AdvancedTest, CopyConstructorTest) {

	TreeMap m(map2);
	EXPECT_TRUE(m.info_eq(map2));
	EXPECT_TRUE(map2.info_eq(m));
	EXPECT_TRUE(m.struct_eq(map2));
	EXPECT_TRUE(map2.info_eq(m));
}



}



int main(int argc, char** argv) {

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
