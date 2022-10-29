//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

class MulNumber : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);

  virtual void SetUp() {
    matrixA(0, 0) = 0.25;
    matrixA(0, 1) = 0.25;
    matrixA(0, 2) = 0.25;
    matrixA(1, 0) = 0.25;
    matrixA(1, 1) = 0.25;
    matrixA(1, 2) = 0.25;
    matrixA(2, 0) = 0.25;
    matrixA(2, 1) = 0.25;
    matrixA(2, 2) = 0.25;

    matrixB(0, 0) = 1.0;
    matrixB(0, 1) = 1.0;
    matrixB(0, 2) = 1.0;
    matrixB(1, 0) = 1.0;
    matrixB(1, 1) = 1.0;
    matrixB(1, 2) = 1.0;
    matrixB(2, 0) = 1.0;
    matrixB(2, 1) = 1.0;
    matrixB(2, 2) = 1.0;
  }
};

TEST_F(MulNumber, test1) {
  matrixA.MulNumber(4);
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test2) {
  matrixA *= 4;
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test3) {
  matrixA = matrixA * 4;
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(MulNumber, test4) {
  matrixA = 4 * matrixA;
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}
