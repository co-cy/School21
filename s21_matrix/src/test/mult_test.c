//
// Created by Nana Daughterless on 6/24/22.
//

#include "main.h"

START_TEST(mult_number_test_1) {
    matrix_t A, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = 1.25;

    R2.matrix[0][0] = -5;

    s21_mult_number(&A, -4, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
} END_TEST

START_TEST(mult_number_test_2) {
    matrix_t A, R, R2;
    s21_create_matrix(3, 3, &A);
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

    R2.matrix[0][0] = 1;
    R2.matrix[0][1] = 5;
    R2.matrix[0][2] = 9;
    R2.matrix[1][0] = 13;
    R2.matrix[1][1] = 17;
    R2.matrix[1][2] = 21;
    R2.matrix[2][0] = 25;
    R2.matrix[2][1] = 29;
    R2.matrix[2][2] = 33;

    s21_mult_number(&A, 4, &R);

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
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
} END_TEST

START_TEST(mult_matrix_test_1) {
    matrix_t A, B, R, R2;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    s21_create_matrix(1, 1, &R2);

    A.matrix[0][0] = -1;
    B.matrix[0][0] = 2;

    R2.matrix[0][0] = -2;

    s21_mult_matrix(&A, &B, &R);

    ck_assert_double_eq_tol(R.matrix[0][0], R2.matrix[0][0], 1e-7);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&R2);
} END_TEST

START_TEST(mult_matrix_test_2) {
    matrix_t A, B, R, R2;
    s21_create_matrix(3, 2, &A);
    s21_create_matrix(2, 3, &B);
    s21_create_matrix(3, 3, &R2);

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 1;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[2][0] = 6;
    A.matrix[2][1] = 7;

    B.matrix[0][0] = 9;
    B.matrix[0][1] = 8;
    B.matrix[0][2] = 7;
    B.matrix[1][0] = 6;
    B.matrix[1][1] = 5;
    B.matrix[1][2] = 4;

    R2.matrix[0][0] = 6;
    R2.matrix[0][1] = 5;
    R2.matrix[0][2] = 4;
    R2.matrix[1][0] = 51;
    R2.matrix[1][1] = 44;
    R2.matrix[1][2] = 37;
    R2.matrix[2][0] = 96;
    R2.matrix[2][1] = 83;
    R2.matrix[2][2] = 70;

    s21_mult_matrix(&A, &B, &R);

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


Suite *create_suite_mult_matrix() {
    Suite *s = suite_create("mult_matrix");
    TCase *tc = tcase_create("mult_matrix_tc");

    tcase_add_test(tc, mult_number_test_1);
    tcase_add_test(tc, mult_number_test_2);

    tcase_add_test(tc, mult_matrix_test_1);
    tcase_add_test(tc, mult_matrix_test_2);

    suite_add_tcase(s, tc);
    return s;
}