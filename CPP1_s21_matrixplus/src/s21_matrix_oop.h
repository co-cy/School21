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

  [[nodiscard]] bool EqMatrix(const S21Matrix& other) const;
  void MergeMatrix(const S21Matrix &other, int sign);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix& other);
  [[nodiscard]] S21Matrix Crop(int i, int j) const;
  [[nodiscard]] S21Matrix Transpose() const;
  [[nodiscard]] S21Matrix CalcComplements() const;
  [[nodiscard]] double Determinant() const;
  [[nodiscard]] S21Matrix InverseMatrix() const;

  [[nodiscard]] bool IsSquare() const;
  [[nodiscard]] bool IsEqSize(const S21Matrix &other) const;
  [[nodiscard]] int GetRows() const;
  [[nodiscard]] int GetCols() const;
  void Resize(int rows, int cols, S21Matrix const *copy_matrix = nullptr);
  void SetRows(int rows);
  void SetCols(int cols);

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(double num) const;
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(S21Matrix const& other) const;
  S21Matrix& operator=(const S21Matrix &other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(double num);
  S21Matrix operator*=(const S21Matrix &other);

  double& operator()(int i, int j);
  double operator()(int i, int j) const;
};


#endif // CPP1_S21_MATRIXPLUS_S21_MATRIX_H
