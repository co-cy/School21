//
// Created by Nana Daughterless on 10/29/22.
//

#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

TEST(DetTest, test1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  ASSERT_TRUE(fabs(matrix.Determinant() - 5) < EPS);
}

TEST(DetTest, test2) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 0.25;
  matrix(0, 1) = 1.25;
  matrix(0, 2) = 2.25;
  matrix(1, 0) = 3.25;
  matrix(1, 1) = 10;
  matrix(1, 2) = 5.25;
  matrix(2, 0) = 6.25;
  matrix(2, 1) = 7.25;
  matrix(2, 2) = 8.25;

  ASSERT_TRUE(fabs(matrix.Determinant() + 69) < EPS);
}

TEST(ErrorDetTest, test1) {
  S21Matrix matrix(0, 0);

  ASSERT_ANY_THROW((void) matrix.Determinant());
}

TEST(ErrorDetTest, test2) {
  S21Matrix matrix(3, 2);

  ASSERT_ANY_THROW((void) matrix.Determinant());
}