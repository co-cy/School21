//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() const{
  if (!IsSquare()) throw std::logic_error("The matrix is not square");

  S21Matrix newMatrix(GetRows(), GetCols());
  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++)
      newMatrix(y, x) = Crop(y, x).Determinant() * ((y + x) % 2? -1 : 1);

  return newMatrix;
}
