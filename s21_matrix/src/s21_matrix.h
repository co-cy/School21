//
// Created by _co_cy_ on 24.05.22.
//

#ifndef S21_MATRIX_S21_MATRIX_H
#define S21_MATRIX_S21_MATRIX_H

#include "common/features.h"
#include <stdlib.h>
#include <math.h>

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

// CUSTOM
int s21_eq_size_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_merge_matrix(matrix_t *A, matrix_t *B, int sign);


matrix_t s21_create_matrix(int rows, int columns);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);

#endif //S21_MATRIX_S21_MATRIX_H
