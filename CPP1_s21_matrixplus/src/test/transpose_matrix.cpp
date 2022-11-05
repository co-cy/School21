//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(TransposeTest, test1) {
  S21Matrix matrixA(0, 0);
  S21Matrix matrixB(0, 0);

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test2) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 10;
  matrixB(0, 0) = 10;

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test3) {
  S21Matrix matrixA(1, 3);
  S21Matrix matrixB(3, 1);

  matrixA(0, 0) = 1;
  matrixA(0, 1) = 2;
  matrixA(0, 2) = 3;

  matrixB(0, 0) = 1;
  matrixB(1, 0) = 2;
  matrixB(2, 0) = 3;

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}

TEST(TransposeTest, test4) {
  S21Matrix matrixA(3, 3);
  S21Matrix matrixB(3, 3);

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
  matrixB(1, 0) = 1.25;
  matrixB(2, 0) = 2.25;
  matrixB(0, 1) = 3.25;
  matrixB(1, 1) = 4.25;
  matrixB(2, 1) = 5.25;
  matrixB(0, 2) = 6.25;
  matrixB(1, 2) = 7.25;
  matrixB(2, 2) = 8.25;

  ASSERT_TRUE(matrixA.Transpose().EqMatrix(matrixB));
}