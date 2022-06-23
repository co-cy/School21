//
// Created by Nana Daughterless on 5/24/22.
//

#include "src/s21_matrix.h"

int main() {

    matrix_t *A = malloc(sizeof(matrix_t));
    matrix_t *R = malloc(sizeof(matrix_t));

    s21_create_matrix(2, 1, A);
    s21_print_matrix(A);

    s21_transpose(A, R);
    s21_print_matrix(R);

    s21_transpose(R, R);
    s21_print_matrix(R);

    s21_remove_matrix(A);
    s21_remove_matrix(R);
    return 0;
}