//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix operator+(const S21Matrix &a, const S21Matrix &b) {
  S21Matrix tmp = a;
  tmp.MergeMatrix(b, 1);
  return tmp;

}
S21Matrix operator-(const S21Matrix &a, const S21Matrix &b) {
  S21Matrix tmp = a;
  tmp.MergeMatrix(b, -1);
  return tmp;
}
S21Matrix operator*(const S21Matrix &a, double num) {
  S21Matrix tmp = a;
  tmp.MulNumber(num);
  return tmp;
}
S21Matrix operator*(double num, const S21Matrix &a) {
    return a * num;
}
S21Matrix operator*(const S21Matrix &a, const S21Matrix &b) {
  S21Matrix tmp = a;
  tmp.MulMatrix(b);
  return tmp;
}

S21Matrix& S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other)
    Resize(other.GetRows(), other.GetCols(), &other);
}
S21Matrix& S21Matrix::operator=(S21Matrix&& other)  noexcept {
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

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  MergeMatrix(other, 1);
  return *this;
}
S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  MergeMatrix(other, -1);
  return *this;
}
S21Matrix S21Matrix::operator*=(double const num) {
  MulNumber(num);
  return *this;
}
S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}


bool operator==(const S21Matrix &a, const S21Matrix &b) {
  return a.EqMatrix(b);
}


double& S21Matrix::operator() (int i, int j) {
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  return matrix_[i][j];
}