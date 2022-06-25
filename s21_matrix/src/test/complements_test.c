//
// Created by Nana Daughterless on 6/24/22.
//

#include "main.h"

START_TEST(transpose_test_1) {
    matrix_t A, B, R;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &R);

    A.matrix[0][0] = 5;
    A.matrix[0][1] = -1;
    A.matrix[0][2] = 1;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 1;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 3;

    s21_calc_complements(&A, &R);

    B.matrix[0][0] = 9;
    B.matrix[0][1] = -2;
    B.matrix[0][2] = -3;
    B.matrix[1][0] = 3;
    B.matrix[1][1] = 14;
    B.matrix[1][2] = -1;
    B.matrix[2][0] = -7;
    B.matrix[2][1] = -18;
    B.matrix[2][2] = 17;

    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
} END_TEST

Suite *create_suite_complements_matrix() {
    Suite *s = suite_create("complements_matrix");
    TCase *tc = tcase_create("complements_matrix_tc");

    tcase_add_test(tc, transpose_test_1);

    suite_add_tcase(s, tc);
    return s;
}