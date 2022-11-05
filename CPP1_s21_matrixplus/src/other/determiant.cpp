//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

double S21Matrix::Determinant() const{
  if (!IsSquare()) throw std::logic_error("The matrix is not square");

  double result = 0;
  if (!GetRows())
    throw std::logic_error("The matrix is empty");
  else if (GetRows() == 1)
    result = matrix_[0][0];
  else if (GetRows() == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  else
    for (int y = 0; y < GetRows(); y++)
      result += Crop(y, 0).Determinant() * matrix_[y][0] * ((y % 2) ? -1:1);

  return result;
}
