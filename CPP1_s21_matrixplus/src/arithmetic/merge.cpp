//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

void S21Matrix::MergeMatrix(const S21Matrix &other, int sign) {
  if (GetRows() != other.GetRows() || GetCols() != other.GetCols())
    throw std::logic_error("Different dimension of matrices");

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++)
      matrix_[y][x] += other(y, x) * sign;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  MergeMatrix(other, 1);
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  MergeMatrix(other, -1);
}
