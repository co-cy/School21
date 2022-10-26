//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

double *S21Matrix::operator[](int y) {
  return matrix_[y];
}

double* const S21Matrix::operator[](int y) const {
  return matrix_[y];
}
