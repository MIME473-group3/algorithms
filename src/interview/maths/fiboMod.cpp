//
// Created by Adam Kosiorek on 7/1/15.
//

#include <cmath>
#include <array>
#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

typedef long long LL;
typedef std::array<std::array<LL, 2>, 2> Matrix;

Matrix multiplyMod(const Matrix& a, const Matrix& b, LL mod) {
  Matrix result;
  for(int r = 0; r < 2; ++r) {
    for(int c = 0; c < 2; ++c) {
      LL sum = 0;
      for(int k = 0; k < 2; ++k) {
        sum += a[r][k] * b[k][c];
      }
      result[r][c] = sum % mod;
    }
  }
  return result;
}

Matrix power(Matrix base, LL exp, LL mod) {

  Matrix result;
  for(long i = 0; i < result.size(); ++i) {
    result[i].fill(0);
    result[i][i] = 1;
  }

  while(exp) {
    if(exp % 2) {
      result = multiplyMod(result, base, mod);
    }
    exp /= 2;
    base = multiplyMod(base, base, mod);
  }
  return result;
}

LL fiboMod(LL n) {

  Matrix mat;
  mat[0][0] = mat[0][1] = mat[1][0] = 1;
  mat[1][1] = 0;

  auto result = power(mat, n, (long) 1e6);
  return result[1][0];
}

struct FiboModTest : public testing::Test {};


TEST_F(FiboModTest, SimpleTest) {

  for (long n = 0; n < 100; ++n) {
    LOG(ERROR) << "fibo # " << n << " = " << fiboMod(n);
  }
}