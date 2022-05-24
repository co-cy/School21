//
// Created by _co_cy_ on 24.05.22.
//

#include "s21_matrix.h"


int s21_eq_size_matrix(matrix_t *A, matrix_t *B) {
    return A->rows == B->rows && A->columns == B->columns;
}


matrix_t s21_merge_matrix(matrix_t *A, matrix_t *B, int sign) {
    matrix_t new_matrix;
    if (s21_eq_size_matrix(A, B)) {
        new_matrix = s21_create_matrix(A->rows, A->columns);
        new_matrix.matrix_type = CORRECT_MATRIX;

        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < A->columns; column++) {
                new_matrix.matrix[row][column] = A->matrix[row][column] + sign * B->matrix[row][column];
            }
        }
    }
    else {
        new_matrix = s21_create_matrix(0, 0);
        new_matrix.matrix_type = INCORRECT_MATRIX;
    }
    return new_matrix;
}


matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t *new_matrix = malloc(sizeof (matrix_t));

    new_matrix->rows = rows;
    new_matrix->columns = columns;
    new_matrix->matrix_type = ZERO_MATRIX;

    new_matrix->matrix = malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        new_matrix->matrix[i] = calloc(columns, sizeof (double));
    }
    return *new_matrix;
}


void s21_remove_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        free(A->matrix[row]);
    }
    free(A->matrix);
    free(A);
}


int s21_eq_matrix(matrix_t *A, matrix_t *B) {
//    FAILURE 0
//    SUCCESS 1
    int status = s21_eq_size_matrix(A, B);
    if (status)
        for (int row = 0; status && row < A->rows; row++) {
            for (int column = 0; status && column < A->columns; column++) {
                status = ldouble_eq(A->matrix[row][column], B->matrix[row][column]);
            }
        }
    return status;
}


matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
    return s21_merge_matrix(A, B, 1);
}


matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    return s21_merge_matrix(A, B, -1);
}
