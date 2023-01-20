//
// Created by Nana Daughterless on 6/24/22.
//

#ifndef S21_MATRIX_CORE_H
#define S21_MATRIX_CORE_H

#include <stdlib.h>

enum {
    OK = 0,
    INCORRECT_MATRIX = 1,
    CALC_ERROR = 2,
};

enum {
    FAILURE = 0,
    SUCCESS = 1,
};

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);


#endif //S21_MATRIX_CORE_H
