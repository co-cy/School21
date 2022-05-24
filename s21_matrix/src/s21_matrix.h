//
// Created by _co_cy_ on 24.05.22.
//

#ifndef S21_MATRIX_S21_MATRIX_H
#define S21_MATRIX_S21_MATRIX_H

#include "common/features.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum { OK = 0,
    INCORRECT_MATRIX = 1,
    CALC_ERROR = 2,
    MALLOC_FAILED = 3 };

enum { FAILURE = 0,
    SUCCESS = 1 };

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;


// CUSTOM
int s21_eq_size_matrix(matrix_t *A, matrix_t *B);
int s21_merge_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign);
void s21_print_matrix(matrix_t *A);

int s21_create_matrix(const int rows, const int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *const A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

#endif //S21_MATRIX_S21_MATRIX_H
