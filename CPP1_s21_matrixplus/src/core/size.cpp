//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

bool S21Matrix::IsSquare() const { return GetRows() == GetCols();}

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  Resize(rows, GetCols());
}
void S21Matrix::SetCols(int cols) {
  Resize(GetRows(), cols);
}