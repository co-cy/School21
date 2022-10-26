//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Crop(int i, int j) {
  S21Matrix newMatrix(GetRows() - 1, GetCols() - 1);

  int new_y = 0, new_x = 0;
  for (int y = 0; y < GetRows(); y++) {
    if (y == i) continue;
    for (int x = 0; x < GetCols(); x++) {
      if (x == j) continue;
      newMatrix[new_y][new_x] = matrix_[y][x];
      new_x++;
    }
    new_y++;
  }

  return newMatrix;
}
