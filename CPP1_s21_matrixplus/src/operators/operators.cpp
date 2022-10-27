//
// Created by stf20 on 26.10.2022.
//

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix &other) const{
  S21Matrix tmp = *this;
  tmp.MergeMatrix(other, 1);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const{
  S21Matrix tmp = *this;
  tmp.MergeMatrix(other, -1);
  return tmp;
}

S21Matrix S21Matrix::operator*(double const num) const{
  S21Matrix tmp = *this;
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const{
  S21Matrix tmp = *this;
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix& S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other)
    Resize(other.GetRows(), other.GetCols(), &other);
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


bool S21Matrix::operator==(S21Matrix const& other) const {
  return EqMatrix(other);
}


double& S21Matrix::operator() (int i, int j) {
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  return matrix_[i][j];
}