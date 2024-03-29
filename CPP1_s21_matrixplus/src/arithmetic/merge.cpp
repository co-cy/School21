//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

void S21Matrix::MergeMatrix(const S21Matrix &other, int sign) {
  if (!IsEqSize(other))
    throw std::logic_error("Different dimension of matrices");

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++) matrix_[y][x] += other(y, x) * sign;
}
