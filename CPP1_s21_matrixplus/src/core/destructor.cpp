//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

void S21Matrix::DeleteMatrix() {
  for (rows_--; rows_ >= 0; rows_--)
    delete matrix_[rows_];
  delete matrix_;

  // rows is already 0
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  DeleteMatrix();
}