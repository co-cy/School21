//
// Created by Nana Daughterless on 6/24/22.
//

#include "other.h"

int s21_crop_matrix(matrix_t *A, int rows_s, int columns_s, int rows_e, int columns_e, matrix_t *R) {
    int status = s21_create_matrix((rows_e - rows_s), (columns_e - columns_s), R);

    if (!status) {
        for (int row = rows_s; row < rows_e; row++) {
            for (int col = columns_s; col < columns_e; col++) {
                R->matrix[row][col] = A->matrix[row][col];
            }
        }
    }

    return status;
}

int s21_iv_crop_matrix(matrix_t *A, int del_row, int del_col, matrix_t *R) {
    int status = s21_create_matrix(A->rows - 1, A->columns - 1, R);

    if (!status) {
        for (int row = 0, row1 = 0; row < A->rows; row++) {
            if (row == del_row)
                continue;
            for (int col = 0, col1 = 0; col < A->columns; col++) {
                if (col == del_col)
                    continue;

                R->matrix[row1][col1] = A->matrix[row][col];
                col1++;
            }
            row1++;
        }
    }

    return status;
}

