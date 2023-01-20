//
// Created by Nana Daughterless on 6/24/22.
//

#include "arithmetic.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_merge_matrix(A, B, result, -1);
}
