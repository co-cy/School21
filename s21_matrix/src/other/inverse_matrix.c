//
// Created by Nana Daughterless on 6/24/22.
//

#include "other.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    double det = 0;

    if (!s21_is_square(A))
        return CALC_ERROR;

    int status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
        status = s21_determinant(A, &det);
        if (status == OK) {
            if (!ldouble_eq(det, 0)) {
                matrix_t tmp_com;

                if (A->rows == 1) {
                    s21_create_matrix(1, 1, &tmp_com);
                    tmp_com.matrix[0][0] = 1;
                } else {
                    status = s21_calc_complements(A, &tmp_com);
                }

                if (status == OK) {
                    matrix_t tmp_tranpose;
                    status = s21_transpose(&tmp_com, &tmp_tranpose);
                    s21_mult_number(&tmp_tranpose, 1.0 / det, result);
                }
            } else {
                status = CALC_ERROR;
            }
        }
    }

    return status;
}
