//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();

  if (fabs(det) < EPS) throw std::logic_error("The determinant of the matrix is 0");

  if (GetRows() == 1) {
    S21Matrix newMatrix(GetRows(), GetCols());
    newMatrix(0, 0) = 1;
    return newMatrix;
  } else {
    S21Matrix newMatrix = CalcComplements().Transpose();
    newMatrix.MulNumber(1.0 / det);
    return newMatrix;
  }
}
