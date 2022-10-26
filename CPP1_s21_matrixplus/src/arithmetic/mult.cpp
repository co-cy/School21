//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

void S21Matrix::MulNumber(const double num) {
  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < GetCols(); x++)
      matrix_[y][x] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (GetCols() != other.GetRows())
    throw std::logic_error("The number of columns of the first matrix is not equal to the number of rows of the second matrix");

  S21Matrix tmpMatrix(GetRows(), other.GetCols());
  for (int y = 0; y < GetRows(); y++)
    for (int x = 0; x < other.GetCols(); x++)
      for (int x_a = 0, y_b = 0; x_a < GetCols() && y_b < other.GetRows(); x_a++, y_b++)
        tmpMatrix[y][x] += matrix_[y][x_a] * other[y_b][x];

  Resize(GetRows(), other.GetCols(), &tmpMatrix);
}