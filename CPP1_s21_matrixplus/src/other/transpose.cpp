//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() const{
  S21Matrix newMatrix(GetCols(), GetRows());

  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++)
      newMatrix(x, y) = matrix_[y][x];

  return newMatrix;
}
