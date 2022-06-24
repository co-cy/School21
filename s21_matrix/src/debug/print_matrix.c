//
// Created by Nana Daughterless on 6/24/22.
//

#include "debug.h"

void s21_print_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            printf("|%12f\t|", A->matrix[row][column]);
        }
        putchar('\n');
    }
    putchar('\n');
}
