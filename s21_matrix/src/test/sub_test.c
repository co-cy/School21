//
// Created by Nana Daughterless on 6/24/22.
//

#include "main.h"

START_TEST(sub_test_1) {
    matrix_t A, B, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 2.25;

    R2.matrix[0][0] = -1;

    s21_sub_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
} END_TEST

START_TEST(sub_test_2) {
    matrix_t A, B, R, R2;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);
    s21_create_matrix(3, 3, &R2);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    B.matrix[0][0] = 9.25;
    B.matrix[0][1] = 8.25;
    B.matrix[0][2] = 7.25;
    B.matrix[1][0] = 6.25;
    B.matrix[1][1] = 5.25;
    B.matrix[1][2] = 4.25;
    B.matrix[2][0] = 3.25;
    B.matrix[2][1] = 2.25;
    B.matrix[2][2] = 1.25;

    R2.matrix[0][0] = -9.0;
    R2.matrix[0][1] = -7.0;
    R2.matrix[0][2] = -5.0;
    R2.matrix[1][0] = -3.0;
    R2.matrix[1][1] = -1.0;
    R2.matrix[1][2] = 1.0;
    R2.matrix[2][0] = 3.0;
    R2.matrix[2][1] = 5.0;
    R2.matrix[2][2] = 7.0;

    s21_sub_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][1], R2.matrix[0][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[0][2], R2.matrix[0][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][0], R2.matrix[1][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][1], R2.matrix[1][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[1][2], R2.matrix[1][2], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][0], R2.matrix[2][0], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][1], R2.matrix[2][1], 1e-7);
    ck_assert_double_eq_tol(R.matrix[2][2], R2.matrix[2][2], 1e-7);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
} END_TEST

Suite *create_suite_sub_matrix() {
    Suite *s = suite_create("sub_matrix");
    TCase *tc = tcase_create("sub_matrix_tc");

    tcase_add_test(tc, sub_test_1);
    tcase_add_test(tc, sub_test_2);

    suite_add_tcase(s, tc);
    return s;
}