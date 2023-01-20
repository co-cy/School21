//
// Created by Nana Daughterless on 6/24/22.
//

#include "other.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    if (!s21_is_square(A))
        return CALC_ERROR;

    int status = s21_create_matrix(A->rows, A->columns, result);

    if (status == OK) {
        double tmp_res;
        matrix_t tmp_matrix;

        for (int row = 0; status == OK && row < A->rows; row++) {
            for (int col = 0; status == OK && col < A->columns; col++) {
                s21_iv_crop_matrix(A, row, col, &tmp_matrix);
                status = s21_determinant(&tmp_matrix, &tmp_res);
                s21_remove_matrix(&tmp_matrix);

                if (status == OK) {
                    result->matrix[row][col] = tmp_res * ((row + col) % 2 ? -1 : 1);
                }
            }
        }
    }

    return status;
}
