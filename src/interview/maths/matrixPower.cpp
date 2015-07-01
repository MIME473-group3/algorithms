#include "gtest/gtest.h"
#include "Utils.h"
#include <cmath>
#include <glog/logging.h>

std::vector<long> multiply(const std::vector<long>& a, const std::vector<long>& b, long rows, long cols) {
  std::vector<long> result(rows * cols);
  for(long r = 0; r < rows; ++r) {
    for(long c = 0; c < cols; ++c) {
      long sum = 0;
      for(long k = 0; k < rows; ++k) {
        sum += a[r * cols + k] * b[k * cols + c];
      }
      result[r * cols + c] = sum;
    }
  }
  return result;
}

std::vector<long> power(std::vector<long> base, long rows, long cols, long exp, long mod) {

  std::vector<long> result(rows * cols, 0);
  for(long i = 0; i < std::min(rows, cols); ++i) {
    result[i * cols + i] = 1;
  }
  while(exp) {
    if(exp % 2) {
      result = multiply(result, base, rows, cols);
      for(long i = 0; i < rows * cols; ++i) {
        result[i] = result[i] % mod;
      }
    }
    exp /= 2;
    base = multiply(base, base, rows, cols);
    for(long i = 0; i < rows * cols; ++i) {
      base[i] = base[i] % mod;
    }
  }
  return result;
}

struct MatrixPowerTest : public testing::Test {};


TEST_F(MatrixPowerTest, SimpleTest) {


  long n = 36;
  std::vector<long> vec = {1, 1, 1, 0};

  LOG(ERROR) << "fibo # " << 0 << " = " << 0;
  for (long n = 0; n < 100; ++n) {
    auto result = power(vec, 2, 2, n, (long) 1e6);
    LOG(ERROR) << "fibo # " << n+1 << " = " << result[0] % (long) 1e6;
  }
}