//
// Created by Nana Daughterless on 10/29/22.
//

#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

class MulMatrix1x1 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(1, 1);
  S21Matrix matrixB = S21Matrix(1, 1);
  S21Matrix matrixC = S21Matrix(1, 1);

  void SetUp() override {
    matrixA(0, 0) = 1;
    matrixB(0, 0) = 10;
    matrixC(0, 0) = 10;
  }
};

TEST_F(MulMatrix1x1, test1) {
  ASSERT_TRUE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix1x1, test2) {
  ASSERT_TRUE((matrixA *= matrixB).EqMatrix(matrixC));
}

class ErrorMulMatrix : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(1, 2);
  S21Matrix matrixB = S21Matrix(1, 1);
};

TEST_F(ErrorMulMatrix, test1) { ASSERT_ANY_THROW(matrixA * matrixB); }

TEST_F(ErrorMulMatrix, test2) { ASSERT_ANY_THROW(matrixA *= matrixB); }

class MulMatrix2x3 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 2);
  S21Matrix matrixB = S21Matrix(2, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 0;
    matrixA(0, 1) = 1;
    matrixA(1, 0) = 3;
    matrixA(1, 1) = 4;
    matrixA(2, 0) = 6;
    matrixA(2, 1) = 7;

    matrixB(0, 0) = 9;
    matrixB(0, 1) = 8;
    matrixB(0, 2) = 7;
    matrixB(1, 0) = 6;
    matrixB(1, 1) = 5;
    matrixB(1, 2) = 4;

    matrixC(0, 0) = 6;
    matrixC(0, 1) = 5;
    matrixC(0, 2) = 4;
    matrixC(1, 0) = 51;
    matrixC(1, 1) = 44;
    matrixC(1, 2) = 37;
    matrixC(2, 0) = 96;
    matrixC(2, 1) = 83;
    matrixC(2, 2) = 70;
  }
};

TEST_F(MulMatrix2x3, test1) {
  ASSERT_TRUE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix2x3, test2) {
  ASSERT_TRUE((matrixA *= matrixB).EqMatrix(matrixC));
}

class MulMatrix3x3 : public ::testing::Test {
 protected:
  S21Matrix matrixA = S21Matrix(3, 3);
  S21Matrix matrixB = S21Matrix(3, 3);
  S21Matrix matrixC = S21Matrix(3, 3);

  void SetUp() override {
    matrixA(0, 0) = 1;
    matrixA(0, 1) = 2;
    matrixA(0, 2) = 3;
    matrixA(1, 0) = 4;
    matrixA(1, 1) = 5;
    matrixA(1, 2) = 6;
    matrixA(2, 0) = 7;
    matrixA(2, 1) = 8;
    matrixA(2, 2) = 9;

    matrixB(0, 0) = 9;
    matrixB(0, 1) = 8;
    matrixB(0, 2) = 7;
    matrixB(1, 0) = 6;
    matrixB(1, 1) = 5;
    matrixB(1, 2) = 4;
    matrixB(2, 0) = 3;
    matrixB(2, 1) = 2;
    matrixB(2, 2) = 1;

    matrixC(0, 0) = 30;
    matrixC(0, 1) = 24;
    matrixC(0, 2) = 18;
    matrixC(1, 0) = 84;
    matrixC(1, 1) = 69;
    matrixC(1, 2) = 54;
    matrixC(2, 0) = 138;
    matrixC(2, 1) = 114;
    matrixC(2, 2) = 90;
  }
};

TEST_F(MulMatrix3x3, test1) {
  ASSERT_TRUE((matrixA * matrixB).EqMatrix(matrixC));
}

TEST_F(MulMatrix3x3, test2) {
  ASSERT_TRUE((matrixA *= matrixB).EqMatrix(matrixC));
}