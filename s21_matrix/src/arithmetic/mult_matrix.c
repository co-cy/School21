//
// Created by Nana Daughterless on 6/24/22.
//

#include "arithmetic.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int status = s21_create_matrix(A->rows, A->columns, result);

    if (status == OK) {
        for (int row = 0; row < A->rows; row++)
            for (int column = 0; column < A->columns; column++)
                result->matrix[row][column] = A->matrix[row][column] * number;
    }

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
