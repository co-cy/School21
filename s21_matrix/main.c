//
// Created by Nana Daughterless on 5/24/22.
//

#include "src/s21_matrix.h"

int main() {

    matrix_t *A = malloc(sizeof (matrix_t));
    matrix_t *B = malloc(sizeof (matrix_t));
    matrix_t *R = malloc(sizeof (matrix_t));

    s21_create_matrix(10, 10, A);
    s21_print_matrix(A);
    s21_create_matrix(10, 10, B);
    s21_print_matrix(B);
    s21_create_matrix(10, 10, R);
    s21_print_matrix(R);

    A->matrix[5][5] = 1;
    s21_print_matrix(A);
    B->matrix[5][5] = 2;
    s21_print_matrix(B);
    R->matrix[5][5] = 3;
    s21_print_matrix(R);

    printf("%d\n", s21_mult_number(A, 10, R));
    s21_print_matrix(R);

    s21_remove_matrix(A);
    s21_remove_matrix(B);
    s21_remove_matrix(R);
    return 0;
}