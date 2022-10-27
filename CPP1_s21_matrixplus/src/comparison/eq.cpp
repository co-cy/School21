//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) const{
  if (!IsEqSize(other))
    return false;

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++)
      if (fabs(matrix_[y][x] - other(y, x)) > EPS) return false;

  return true;
}
