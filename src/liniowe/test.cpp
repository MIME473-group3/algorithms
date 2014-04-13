#include <gtest/gtest.h>
#include "ListMap.h"

int CCount::count = 1;
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
		map2[3] = "b";
		map2[4] = "c";

		opp2[4] = "a";
		opp2[3] = "b";
		opp2[2] = "c";
	};

	~AdvancedTest() {};


	ListMap map1, map2, opp2;
};

TEST_F(BasicTest, InsertTest) {

	ListMap map;
	std::pair<ListMap::iterator, bool> result;
	result = map.insert(std::make_pair(0, "a"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 0);
	EXPECT_EQ(result.first->second, "a");
	result = map.insert(std::make_pair(4, "b"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 4);
	EXPECT_EQ(result.first->second, "b");
	result = map.insert(std::make_pair(16, "c"));
	EXPECT_TRUE(result.second);
	EXPECT_EQ(result.first->first, 16);
	EXPECT_EQ(result.first->second, "c");

	result = map.insert(std::make_pair(0, "zz"));
	EXPECT_FALSE(result.second);
	EXPECT_EQ(result.first->first, 0);
	EXPECT_EQ(result.first->second, "a");
}

TEST_F(BasicTest, OperatorInsertTest) {

	ListMap map;
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

	ListMap map;
	EXPECT_EQ(map.size(), 0);
	map[0] = "a";
	EXPECT_EQ(map.size(), 1);
	map[4] = "b";
	EXPECT_EQ(map.size(), 2);
	map[16] = "c";
	EXPECT_EQ(map.size(), 3);
}

TEST_F(AdvancedTest, EndsNotEqual) {

	ASSERT_FALSE(map1.end() == map2.end());
	ASSERT_TRUE(map1.end() == map1.end());
	ASSERT_TRUE(map2.end() == map2.end());
}

TEST_F(AdvancedTest, FindTest) {

	ListMap::iterator it = map1.find(1);
	ListMap::iterator end = map1.end();

	EXPECT_TRUE(it ==  end);
	EXPECT_TRUE(map1.find(0)->first == 0);
	EXPECT_TRUE(map1.find(0)->second == "1");

	EXPECT_TRUE(map1.find(2)->first == 2);
	EXPECT_TRUE(map1.find(2)->second == "aha");

	EXPECT_TRUE(map1.find(4)->first == 4);
	EXPECT_TRUE(map1.find(4)->second ==  "wef");
}

TEST_F(AdvancedTest, EmptyIteratorTest) {

	ListMap map;
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

//	EXPECT_EQ(map2.end()->second, "");

	auto it = map2.begin();
	EXPECT_EQ(it->second, "c");
	EXPECT_EQ((++it)->second, "b");
	EXPECT_EQ((it)->second, "b");
	EXPECT_EQ((it++)->second, "b");
	EXPECT_EQ((it)->second, "a");

	it = map2.end();
//	ASSERT_EQ(it->second, "");
	EXPECT_EQ((--it)->second, "a");
	ASSERT_EQ((it)->second, "a");


	EXPECT_EQ((--it)->second, "b");
	EXPECT_EQ((it)->second, "b");
//
	EXPECT_EQ((++it)->second, "a");
	EXPECT_EQ((it)->second, "a");
//
	EXPECT_EQ((it)->second, "a");
	EXPECT_EQ((it--)->second, "a");
	EXPECT_EQ((it)->second, "b");

	EXPECT_EQ((it++)->second, "b");
	EXPECT_EQ((it)->second, "a");
}

TEST_F(AdvancedTest, EraseTest) {

	ASSERT_EQ(map2.size(), 3);
	map2.erase(4);
	ASSERT_EQ(map2.size(), 2);
	ASSERT_TRUE(map2.find(4) == map2.end());
	map2.erase(3);
	ASSERT_EQ(map2.size(), 1);
	ASSERT_TRUE(map2.find(3) == map2.end());
	map2.erase(2);
	ASSERT_EQ(map2.size(), 0);
	ASSERT_TRUE(map2.find(2) ==  map2.end());
}

TEST_F(AdvancedTest, DISABLED_BandEraseTest) {

	//zakresy
}

TEST_F(AdvancedTest, InfoEqTest) {

	EXPECT_TRUE(map2.info_eq(map2));

	ListMap map, map3;
	for(ListMap::iterator it = map2.begin(); it != map2.end(); ++it) {

		map.insert(*it);
	}

	for(ListMap::iterator it = map.begin(); it != map.end(); ++it) {

			map3.insert(*it);
		}


	EXPECT_TRUE(map2.info_eq(map3));
	EXPECT_TRUE(map3.info_eq(map2));


	EXPECT_FALSE(opp2.info_eq(map1));
	EXPECT_FALSE(map1.info_eq(opp2));

}

TEST_F(AdvancedTest, StructEqTest) {

	EXPECT_TRUE(map2.struct_eq(map2));

	EXPECT_FALSE(opp2.struct_eq(map2));
	EXPECT_FALSE(map2.struct_eq(opp2));


	EXPECT_FALSE(opp2.struct_eq(map1));
	EXPECT_FALSE(map1.struct_eq(opp2));
}

TEST_F(AdvancedTest, EqAddingElements) {

	ListMap m1, m2;

	ASSERT_TRUE(m1.info_eq(m2));
	ASSERT_TRUE(m1.struct_eq(m2));

	for(int i = 0; i < 100; ++i) {
		m1[i] = std::to_string(i);
		m2[i] = std::to_string(i);
		ASSERT_TRUE(m1.info_eq(m2));
		ASSERT_TRUE(m1.struct_eq(m2));
		ASSERT_EQ(m1[i / 2], m2[i / 2]);
	}

	m2.erase(91);
	m1.erase(91);
	ASSERT_TRUE(m1.info_eq(m2));
	ASSERT_TRUE(m1.struct_eq(m2));
}



}



int main(int argc, char** argv) {

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
