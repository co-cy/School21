//
// Created by Nana Daughterless on 6/24/22.
//

#ifndef S21_MATRIX_ARITHMETIC_H
#define S21_MATRIX_ARITHMETIC_H

#include "../comparison/comparison.h"
#include "../core/core.h"

int s21_merge_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

#endif //S21_MATRIX_ARITHMETIC_H
