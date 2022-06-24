//
// Created by Nana Daughterless on 6/24/22.
//

#include "arithmetic.h"

int s21_merge_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
    int status = s21_eq_size_matrix(A, B);

    if (status == OK) {
        status = s21_create_matrix(A->rows, A->columns, result);
        if (status == OK) {
            for (int row = 0; row < A->rows; row++)
                for (int column = 0; column < A->columns; column++)
                    result->matrix[row][column] = A->matrix[row][column] + sign * B->matrix[row][column];
        }
    }
    return status;
}
