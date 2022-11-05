//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

void S21Matrix::Resize(int rows, int cols, S21Matrix const *copy_matrix) {
  double **new_matrix_ = nullptr;
  if (rows) {
    new_matrix_ = new double *[rows];

    for (int y = 0; y < rows; y++) {
      if (cols) {
        new_matrix_[y] = new double[cols];
        for (int x = 0; x < cols; x++) {
          if (copy_matrix && copy_matrix->GetRows() > y &&
              copy_matrix->GetCols() > x)
            new_matrix_[y][x] = (*copy_matrix)(y, x);
          else
            new_matrix_[y][x] = 0;
        }
      } else {
        new_matrix_[y] = nullptr;
      }
    }
  }

  DeleteMatrix();

  rows_ = rows;
  cols_ = cols;
  matrix_ = new_matrix_;
}