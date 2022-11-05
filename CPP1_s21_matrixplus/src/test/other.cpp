//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(ErrorAny, test1) {
  S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(0, 1));
}

TEST(ErrorAny, test2) {
  S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(-1, -1));
}

TEST(ErrorAny, test3) {
  S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(1, 1));
}

TEST(ErrorAny, test4) {
  const S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(0, 1));
}

TEST(ErrorAny, test5) {
  const S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(-1, -1));
}

TEST(ErrorAny, test6) {
  const S21Matrix matrix(1, 1);

  ASSERT_ANY_THROW(matrix(1, 1));
}

TEST(Any, test1) {
  S21Matrix matrixA(2, 2);
  matrixA(0, 0) = 1;
  matrixA(0, 1) = 2;
  matrixA(1, 0) = 3;
  matrixA(1, 1) = 4;
  S21Matrix matrixB(0, 0);

  S21Matrix matrixC = matrixA;

  matrixB = matrixA;

  ASSERT_TRUE(matrixC.EqMatrix(matrixB));
  matrixB(0, 0) = 11;
  ASSERT_TRUE(matrixA.EqMatrix(matrixC));
}
