//
// Created by Nana Daughterless on 6/24/22.
//

#include "core.h"

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int row = 0; row < A->rows; row++)
            free(A->matrix[row]);
        free(A->matrix);
    }
}
