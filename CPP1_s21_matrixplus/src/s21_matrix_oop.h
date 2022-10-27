//
// Created by stf20 on 26.10.2022.
//

#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_H
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_H

#include <cmath>
#include <stdexcept>

#define EPS (1e-6)

class S21Matrix {
private:
  // Attributes
  int rows_ = 0, cols_ = 0;         // Rows and columns
  double **matrix_ = nullptr;         // Pointer to the memory where the matrix is allocated
  void DeleteMatrix();

public:
  S21Matrix();              // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();             // Destructor

  bool EqMatrix(const S21Matrix& other);
  void MergeMatrix(const S21Matrix &other, int sign);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Crop(int i, int j);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  bool IsSquare() const;
  int GetRows() const;
  int GetCols() const;
  void Resize(int rows, int cols, S21Matrix const *copy_matrix = nullptr);
  void SetRows(int rows);
  void SetCols(int cols);
};


#endif // CPP1_S21_MATRIXPLUS_S21_MATRIX_H
