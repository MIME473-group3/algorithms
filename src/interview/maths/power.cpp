#include "gtest/gtest.h"
#include "Utils.h"
#include <cmath>
#include <glog/logging.h>


double power(double base, int exp) {

  double result = 1;
  while(exp) {
    if(exp % 2) {
      result *= base;
    }
    exp /= 2;
    base *= base;
  }
  return result;
}

struct PowerTest : public testing::Test {};


TEST_F(PowerTest, SimpleTest) {

  ASSERT_DOUBLE_EQ(power(2, 0), 1);
  ASSERT_DOUBLE_EQ(power(2, 1), 2);
  ASSERT_DOUBLE_EQ(power(2, 10), 1024);
  ASSERT_DOUBLE_EQ(power(2, 31), std::pow(2, 31));
}
