//
// Created by Nana Daughterless on 10/29/22.
//

#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

class SumMatrix1 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 0;
    matrixA(0, 1) = 0;
    matrixA(0, 2) = 0;
    matrixA(1, 0) = 0;
    matrixA(1, 1) = 0;
    matrixA(1, 2) = 0;
    matrixA(2, 0) = 0;
    matrixA(2, 1) = 0;
    matrixA(2, 2) = 0;

    matrixB(0, 0) = 1;
    matrixB(0, 1) = 1;
    matrixB(0, 2) = 1;
    matrixB(1, 0) = 1;
    matrixB(1, 1) = 1;
    matrixB(1, 2) = 1;
    matrixB(2, 0) = 1;
    matrixB(2, 1) = 1;
    matrixB(2, 2) = 1;

    matrixC(0, 0) = 1;
    matrixC(0, 1) = 1;
    matrixC(0, 2) = 1;
    matrixC(1, 0) = 1;
    matrixC(1, 1) = 1;
    matrixC(1, 2) = 1;
    matrixC(2, 0) = 1;
    matrixC(2, 1) = 1;
    matrixC(2, 2) = 1;
  }
};

TEST_F(SumMatrix1, test1) {
  matrixA += matrixB;
  ASSERT_TRUE(matrixA.EqMatrix(matrixC));
}

TEST_F(SumMatrix1, test2) {
  ASSERT_TRUE((matrixA + matrixB).EqMatrix(matrixC));
}

TEST(SumErrorTest, test1) {
  S21Matrix matrixA = S21Matrix(2, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  ASSERT_ANY_THROW(matrixA + matrixB);
}

