//
// Created by Nana Daughterless on 6/24/22.
//

#include "comparison.h"


int s21_eq_size_matrix(matrix_t *A, matrix_t *B) {
    return !(A->rows == B->rows && A->columns == B->columns);
}

int s21_is_square(matrix_t *A) {
    return A->rows == A->columns;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int status = s21_eq_size_matrix(A, B);

    if (status == OK)
        for (int row = 0; status == OK && row < A->rows; row++)
            for (int column = 0; status == OK && column < A->columns; column++)
                status = ldouble_eq(A->matrix[row][column], B->matrix[row][column]);
    return status;
}

