//
// Created by stf20 on 26.10.2022.
//

#include "debug.h"

void print(S21Matrix &matrix) {
  std::cout << "Size:\n";
  std::cout << "Rows: " << matrix.GetRows() << " Cols: " << matrix.GetCols() << "\n";

  for (int y = 0; y < matrix.GetRows(); y++) {
    for (int x = 0; x < matrix.GetCols(); x++) {
      std::cout << matrix[y][x] << "\t";
    }
    std::cout << "\n";
  }
}
