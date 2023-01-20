//
// Created by Nana Daughterless on 6/24/22.
//

#include "core.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int status = OK;

    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;

        result->matrix = malloc(rows * sizeof(double*));
        if (!result->matrix)
            status = INCORRECT_MATRIX;

        for (int i = 0; status == OK && i < rows; i++) {
            result->matrix[i] = calloc(columns, sizeof(double));
            if (!result->matrix[i]) {
                for (int j = 0; j < i; j++)
                    free(result->matrix[j]);
                free(result->matrix);

                status = INCORRECT_MATRIX;
            }
        }
    } else {
        status = INCORRECT_MATRIX;
    }
    return status;
}
