//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
S21Matrix::S21Matrix(int rows, int cols) {
  Resize(rows, cols);
}
S21Matrix::S21Matrix(const S21Matrix &other) {
  Resize(other.GetRows(), other.GetCols(), &other);
}
S21Matrix::S21Matrix(S21Matrix &&other) noexcept{
  if (this != &other) {
    DeleteMatrix();

    rows_ = other.GetRows();
    cols_ = other.GetCols();
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
}

