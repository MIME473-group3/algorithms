//
// Created by Adam Kosiorek on 6/30/15.
//

#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

#include <map>

int complementaryNumbers(int K, std::vector<int> A) {

  std::map<int, int> countMap;
  for(auto a : A) {
    auto it = countMap.find(a);
    if(it == countMap.end()) {
      countMap[a] = 1;
    } else {
      it->second += 1;
    }
  }

  int count = 0;
  int size = 0;
  for(const auto& c : countMap) {
    A[size] = c.first;
    ++size;

    if(c.first * 2 == K) {
      count += c.second * c.second;
    }
  }

  int beg = 0;
  int end = size - 1;
  while(beg < end) {

    int sum = A[beg] + A[end];
    if(sum == K) {
      count += countMap[A[beg]] * countMap[A[end]] * 2;
    } else if(sum > K) {
      --end;
      continue;
    }
    ++beg;
  }

  return count;
}


struct ComplementaryNumbersTest : public testing::Test {};

TEST_F(ComplementaryNumbersTest, SomeTest) {

  std::vector<int> testVec = {2, 4, 9, -3, 1, 12, -1, 2, 0, 7, 10, 5, 7, 8};
  for(int k = 0; k < 10; ++k) {
    LOG(ERROR) << k << " = " << complementaryNumbers(k, testVec);
  }

  std::vector<int> testVec2 = {2, 2, 2, 2};
  ASSERT_EQ(0, complementaryNumbers(0, testVec2));
  ASSERT_EQ(0, complementaryNumbers(2, testVec2));
  ASSERT_EQ(16, complementaryNumbers(4, testVec2));
  testVec2.pop_back();
  ASSERT_EQ(9, complementaryNumbers(4, testVec2));
  testVec2.pop_back();
  ASSERT_EQ(4, complementaryNumbers(4, testVec2));
  testVec2.pop_back();
  ASSERT_EQ(1, complementaryNumbers(4, testVec2));
  testVec2.pop_back();
  ASSERT_EQ(0, complementaryNumbers(4, testVec2));

  ASSERT_EQ(complementaryNumbers(2, testVec2), 0);

  std::vector<int> testVec3 = {1, 8, -3, 0, 1, 3, -2, 4, 5};
  ASSERT_EQ(7, complementaryNumbers(6, testVec3));


  std::vector<int> testVec4 = {1, 1, 4, 4, 4};
  ASSERT_EQ(4, complementaryNumbers(2, testVec4));
  ASSERT_EQ(9, complementaryNumbers(8, testVec4));
  ASSERT_EQ(12, complementaryNumbers(5, testVec4));

  LOG(ERROR) << "I work!";
}