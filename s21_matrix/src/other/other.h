//
// Created by Nana Daughterless on 6/24/22.
//

#ifndef S21_MATRIX_OTHER_H
#define S21_MATRIX_OTHER_H

#include "../comparison/comparison.h"
#include "../arithmetic/arithmetic.h"
#include "../common/features.h"
#include "../core/core.h"

int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_iv_crop_matrix(matrix_t *A, int del_row, int del_col, matrix_t *R);

#endif //S21_MATRIX_OTHER_H
