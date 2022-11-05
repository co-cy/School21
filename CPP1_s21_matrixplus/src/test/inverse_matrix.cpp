//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

TEST(InverseTest, test1) {
  S21Matrix matrixA(1, 1);
  S21Matrix matrixB(1, 1);

  matrixA(0, 0) = 1.25;
  matrixB(0, 0) = 0.8;

  ASSERT_TRUE(matrixA.InverseMatrix().EqMatrix(matrixB));
}

TEST(InverseTest, test2) {
  S21Matrix matrixA(3, 3);
  S21Matrix matrixB(3, 3);

  matrixA(0, 0) = 2;
  matrixA(0, 1) = 5;
  matrixA(0, 2) = 7;
  matrixA(1, 0) = 6;
  matrixA(1, 1) = 3;
  matrixA(1, 2) = 4;
  matrixA(2, 0) = 5;
  matrixA(2, 1) = -2;
  matrixA(2, 2) = -3;

  matrixB(0, 0) = 1;
  matrixB(0, 1) = -1;
  matrixB(0, 2) = 1;
  matrixB(1, 0) = -38;
  matrixB(1, 1) = 41;
  matrixB(1, 2) = -34;
  matrixB(2, 0) = 27;
  matrixB(2, 1) = -29;
  matrixB(2, 2) = 24;

  ASSERT_TRUE(matrixA.InverseMatrix().EqMatrix(matrixB));
}

TEST(ErrorInverseTest, test1) {
  S21Matrix matrixA(1, 3);

  ASSERT_ANY_THROW((void)matrixA.InverseMatrix());
}

TEST(ErrorInverseTest, test2) {
  S21Matrix matrixA(0, 0);
  S21Matrix matrixB(0, 0);

  ASSERT_ANY_THROW((void)matrixA.InverseMatrix());
}