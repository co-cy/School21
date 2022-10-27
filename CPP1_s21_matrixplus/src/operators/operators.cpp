//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

double& S21Matrix::operator() (int i, int j) {
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  return matrix_[i][j];
}