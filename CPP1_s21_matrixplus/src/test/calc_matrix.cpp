//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(ComplementsTest, test1) {
  S21Matrix matrixA(3, 3);
  S21Matrix matrixB(3, 3);

  matrixA(0, 0) = 5;
  matrixA(0, 1) = -1;
  matrixA(0, 2) = 1;
  matrixA(1, 0) = 2;
  matrixA(1, 1) = 3;
  matrixA(1, 2) = 4;
  matrixA(2, 0) = 1;
  matrixA(2, 1) = 0;
  matrixA(2, 2) = 3;

  matrixB(0, 0) = 9;
  matrixB(0, 1) = -2;
  matrixB(0, 2) = -3;
  matrixB(1, 0) = 3;
  matrixB(1, 1) = 14;
  matrixB(1, 2) = -1;
  matrixB(2, 0) = -7;
  matrixB(2, 1) = -18;
  matrixB(2, 2) = 17;

  ASSERT_TRUE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ComplementsTest, test2) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 5;
  matrixB(0, 0) = 5;

  ASSERT_TRUE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ComplementsTest, test3) {
  S21Matrix matrixA(0, 0);
  S21Matrix matrixB(0, 0);

  ASSERT_TRUE(matrixA.CalcComplements().EqMatrix(matrixB));
}

TEST(ErrorComplementsTest, test1) {
  S21Matrix matrix(2, 1);
  ASSERT_ANY_THROW((void)matrix.CalcComplements());
}
