//
// Created by _co_cy_ on 24.05.22.
//

#include "s21_matrix.h"


int s21_eq_size_matrix(matrix_t *A, matrix_t *B) {
    return !(A->rows == B->rows && A->columns == B->columns);
}

int s21_is_square(matrix_t *A) {
    return A->rows == A->columns;
}

int s21_merge_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
    int status = s21_eq_size_matrix(A, B);

    if (status == OK) {
        status = s21_create_matrix(A->rows, A->columns, result);
        if (status == OK)
            for (int row = 0; row < A->rows; row++)
                for (int column = 0; column < A->columns; column++)
                    result->matrix[row][column] = A->matrix[row][column] + sign * B->matrix[row][column];
    }
    return status;
}


void s21_print_matrix(matrix_t *A) {
    for (int row = 0; row < A->rows; row++) {
        for (int column = 0; column < A->columns; column++) {
            printf("|%12f\t|", A->matrix[row][column]);
        }
        putchar('\n');
    }
    putchar('\n');
}



int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int status = OK;

    if (rows >= 0 && columns >= 0) {
        result->rows = rows;
        result->columns = columns;

        result->matrix = malloc(rows * sizeof(double*));
        if (!result->matrix)
            exit(666);

        for (int i = 0; i < rows; i++) {
            result->matrix[i] = calloc(columns, sizeof(double));
            if (!result->matrix[i])
                exit(666);
        }
    } else {
        status = INCORRECT_MATRIX;
    }
    return status;
}


void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int row = 0; row < A->rows; row++)
            free(A->matrix[row]);
        free(A->matrix);
    }
}


int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int status = s21_eq_size_matrix(A, B);

    if (status == OK)
        for (int row = 0; status == OK && row < A->rows; row++)
            for (int column = 0; status == OK && column < A->columns; column++)
                status = ldouble_eq(A->matrix[row][column], B->matrix[row][column]);
    return status;
}


int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_merge_matrix(A, B, result, 1);
}


int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    return s21_merge_matrix(A, B, result, -1);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int status = s21_create_matrix(A->rows, A->columns, result);

    if (status == OK)
        for (int row = 0; row < A->rows; row++)
            for (int column = 0; column < A->columns; column++)
                result->matrix[row][column] = A->matrix[row][column] * number;
    return status;
}


int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int status = s21_create_matrix(A->rows, B->columns, result);

    if (status == OK) {
        for (int row = 0; row < A->rows; row++) {
            for (int column = 0; column < B->columns; column++) {
                result->matrix[row][column] = 0;
                for (int col_a = 0, row_b = 0; col_a < A->columns && row_b < B->rows; col_a++, row_b++) {
                    result->matrix[row][column] += A->matrix[row][col_a] * B->matrix[row_b][column];
                }
            }
        }
    }

    return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int status = s21_create_matrix(A->columns, A->rows, result);

    if (status == OK) {
        for (int col = 0; col < A->columns; col++) {
            for (int row = 0; row < A->rows; row++) {
                result->matrix[col][row] = A->matrix[row][col];
            }
        }
    }
    return status;
}


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

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    if (!s21_is_square(A)) 
        return CALC_ERROR;
    
    int status = s21_create_matrix(A->rows, A->columns, result);

    if (status == OK) {
        double tmp_res;
        matrix_t tmp_matrix;
        for (int row = 0; status == OK && row < A->rows; row++) {
            for (int col = 0; status == OK && col < A->columns; col++) {
                
                s21_iv_crop_matrix(A, row, col, &tmp_matrix);

                status = s21_determinant(&tmp_matrix, &tmp_res);

                if (status == OK) {
                    result->matrix[row][col] = tmp_res * ((row + col) % 2 ? -1 : 1);
                }
                s21_remove_matrix(&tmp_matrix);
            }
        }
    }

    return status;
}

int s21_determinant(matrix_t *A, double *result) {
    if (!s21_is_square(A)) 
        return CALC_ERROR;

    int status = OK;

    if (A->rows == 1) {
        *result = A->matrix[0][0];
    } elif (A->rows == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        *result = 0;

        matrix_t tmp_matrix2;
        
        double tmp;
        for (int row = 0; status == OK && row < A->rows; row++) {
            status = s21_iv_crop_matrix(A, row, 0, &tmp_matrix2);
            if (status == OK) {
                status = s21_determinant(&tmp_matrix2, &tmp);
                if (status == OK) {
                    *result += tmp * A->matrix[row][0] * ((row % 2) ? -1 : 1);
                }
            }
        }
    }

    return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    double det = 0;

    int status = s21_create_matrix(A->rows, A->columns, result);
    if (status == OK) {
        status = s21_determinant(A, &det);
        if (status == OK) {
            if (!ldouble_eq(det, 0)) {
                matrix_t tmp_com;
                status = s21_calc_complements(A, &tmp_com);
                if (status == OK) {
                    matrix_t tmp_tranpose;
                    status = s21_transpose(&tmp_com, &tmp_tranpose);
                    s21_mult_number(&tmp_tranpose, 1.0 / det, result);
                }
            } else {
                status = CALC_ERROR;
            }
        }
    }

    return status;
}
