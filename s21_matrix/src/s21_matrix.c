//
// Created by _co_cy_ on 24.05.22.
//

#include "s21_matrix.h"


int s21_eq_size_matrix(matrix_t *A, matrix_t *B) {
    return !(A->rows == B->rows && A->columns == B->columns);
}


int s21_merge_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
    int status = s21_eq_size_matrix(A, B);
    if (status == OK) {
        status = s21_create_matrix(A->rows, A->columns, result);
        if (status == OK)
            for (int row = 0; row < A->rows; row++)
                for (int column = 0; column < A->columns; column++)
                    result->matrix[row][column] = A->matrix[row][column] + sign * B->matrix[row][column];
    }
    return status;
}


void s21_print_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            printf("|%12f\t|", A->matrix[row][column]);
        }
        putchar('\n');
    }
    putchar('\n');
}



int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
    int status = OK;
    if (rows >= 0 && columns >= 0) {
        result->rows = rows;
        result->columns = columns;

        result->matrix = malloc(rows * sizeof(double*));
        for (int i = 0; i < rows; i++)
            result->matrix[i] = calloc(columns, sizeof (double));
    } else {
        status = MALLOC_FAILED;
    }
    return status;
}


void s21_remove_matrix(matrix_t *const A) {
    if (A->matrix) {
        for (int row = 0; row < A->rows; row++)
            free(A->matrix[row]);
        free(A->matrix);
    }
    free(A);
}


int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int status = s21_eq_size_matrix(A, B);
    if (status == OK)
        for (int row = 0; status == OK && row < A->rows; row++)
            for (int column = 0; status == OK && column < A->columns; column++)
                status = ldouble_eq(A->matrix[row][column], B->matrix[row][column]);
    return status;
}


int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_merge_matrix(A, B, result, 1);
}


int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_merge_matrix(A, B, result, -1);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK)
        for (int row = 0; row < A->rows; row++)
            for (int column = 0; column < A->columns; column++)
                result->matrix[row][column] = A->matrix[row][column] * number;
    return status;
}


int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int status = s21_create_matrix(A->rows, B->columns, result);
    if (status == OK) {
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < B->columns; column++) {
                result->matrix[row][column] = 0;
                for (int col_a = 0, row_b = 0; col_a < A->columns && row_b < B->rows; col_a++, row_b++) {
                    result->matrix[row][column] += A->matrix[row][col_a] * B->matrix[row_b][column];
                }
            }
        }
    }

    return status;
}
