//
// Created by Nana Daughterless on 6/24/22.
//

#include "other.h"

int s21_determinant(matrix_t *A, double *result) {
    if (!s21_is_square(A))
        return CALC_ERROR;

    int status = OK;

    if (A->rows == 0) {
        status = CALC_ERROR;
    } elif (A->rows == 1) {
        *result = A->matrix[0][0];
    } elif (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        *result = 0;

        matrix_t tmp_matrix2;

        double tmp;
        for (int row = 0; status == OK && row < A->rows; row++) {
            status = s21_iv_crop_matrix(A, row, 0, &tmp_matrix2);
            if (status == OK) {
                status = s21_determinant(&tmp_matrix2, &tmp);
                if (status == OK) {
                    *result += tmp * A->matrix[row][0] * ((row % 2) ? -1 : 1);
                }
            }
            s21_remove_matrix(&tmp_matrix2);
        }
    }

    return status;
}
