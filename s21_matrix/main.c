//
// Created by Nana Daughterless on 5/24/22.
//

#include "src/s21_matrix.h"

int main() {

    matrix_t A;
    matrix_t R;

    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = -1;
    A.matrix[0][1] = 3;
    A.matrix[0][2] = -1;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 10;
    A.matrix[1][2] = 11;
    A.matrix[2][0] = -1;
    A.matrix[2][1] = 2;
    A.matrix[2][2] = -1;


    s21_print_matrix(&A);

    matrix_t res;
    s21_inverse_matrix(&A, &res);
    s21_print_matrix(&res);

    s21_remove_matrix(&A);
    return 0;
}