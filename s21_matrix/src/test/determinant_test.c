//
// Created by Nana Daughterless on 6/24/22.
//

#include "main.h"

START_TEST(determinant_test_1) {
    matrix_t A;
    double B, R = 1.25;
    s21_create_matrix(1, 1, &A);

    A.matrix[0][0] = 1.25;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
} END_TEST

START_TEST(determinant_test_2) {
    matrix_t A;
    double B, R = -69;
    s21_create_matrix(3, 3, &A);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 10;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    s21_determinant(&A, &B);

    ck_assert_double_eq_tol(B, R, 1e-7);

    s21_remove_matrix(&A);
} END_TEST

Suite *create_suite_determinant_matrix() {
    Suite *s = suite_create("determinant_matrix");
    TCase *tc = tcase_create("determinant_matrix_tc");

    tcase_add_test(tc, determinant_test_1);
    tcase_add_test(tc, determinant_test_2);

    suite_add_tcase(s, tc);
    return s;
}