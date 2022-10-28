//
// Created by Nana Daughterless on 10/27/22.
//

#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

class EqSimple : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);

  virtual void SetUp() {
    matrixA(0, 0) = 0.25;
    matrixA(0, 1) = 1.25;
    matrixA(0, 2) = 2.25;
    matrixA(1, 0) = 3.25;
    matrixA(1, 1) = 4.25;
    matrixA(1, 2) = 5.25;
    matrixA(2, 0) = 6.25;
    matrixA(2, 1) = 7.25;
    matrixA(2, 2) = 8.25;

    matrixB(0, 0) = 0.25;
    matrixB(0, 1) = 1.25;
    matrixB(0, 2) = 2.25;
    matrixB(1, 0) = 3.25;
    matrixB(1, 1) = 4.25;
    matrixB(1, 2) = 5.25;
    matrixB(2, 0) = 6.25;
    matrixB(2, 1) = 7.25;
    matrixB(2, 2) = 8.25;
  }

};


TEST_F(EqSimple, operator_eq) {
  ASSERT_TRUE(matrixA == matrixB);
}

TEST_F(EqSimple, A_eq_B) {
  ASSERT_TRUE(matrixA.EqMatrix(matrixB));
}

TEST_F(EqSimple, B_eq_A) {
  ASSERT_TRUE(matrixB.EqMatrix(matrixA));
}


class EqSimple2 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(1, 3);
  S21Matrix matrixB = S21Matrix(3, 1);
};

TEST_F(EqSimple2, operator_eq2) {
  ASSERT_FALSE(matrixA == matrixB);
}

TEST_F(EqSimple2, A_eq_B2) {
  ASSERT_FALSE(matrixA.EqMatrix(matrixB));
}

TEST_F(EqSimple2, B_eq_A2) {
  ASSERT_FALSE(matrixB.EqMatrix(matrixA));
}
