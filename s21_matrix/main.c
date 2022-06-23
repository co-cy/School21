//
// Created by Nana Daughterless on 5/24/22.
//

#include "src/s21_matrix.h"

int main() {

    matrix_t A;
    matrix_t R;

    s21_create_matrix(4, 4, &A);

A.matrix[0][0] = 1;
A.matrix[0][1] = 2;
A.matrix[0][2] = 3;
A.matrix[0][3] = 2;
A.matrix[1][0] = 0;
A.matrix[1][1] = 5;
A.matrix[1][2] = 2;
A.matrix[1][3] = 8;
A.matrix[2][0] = 5;
A.matrix[2][1] = 2;
A.matrix[2][2] = 1;
A.matrix[2][3] = 2;
A.matrix[3][0] = 2;
A.matrix[3][1] = 9;
A.matrix[3][2] = 2;
A.matrix[3][3] = 2;
    s21_print_matrix(&A);

    double res;
    s21_determinant(&A, &res);
    printf("RES - %lf", res);

    s21_remove_matrix(&A);
    return 0;
}