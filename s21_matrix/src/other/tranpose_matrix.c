//
// Created by Nana Daughterless on 6/24/22.
//

#include "other.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
    int status = s21_create_matrix(A->columns, A->rows, result);

    if (status == OK) {
        for (int col = 0; col < A->columns; col++) {
            for (int row = 0; row < A->rows; row++) {
                result->matrix[col][row] = A->matrix[row][col];
            }
        }
    }
    return status;
}
