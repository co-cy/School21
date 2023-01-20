//
// Created by Nana Daughterless on 6/24/22.
//

#include "main.h"

START_TEST(eq_test_1) {
    matrix_t A, B;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = 1.2500005;
    B.matrix[0][0] = 2.2500005;

    ck_assert_int_eq(s21_eq_matrix(&A, &B), 0);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
} END_TEST

START_TEST(eq_test_2) {
    matrix_t A, B;
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &B);

    A.matrix[0][0] = 0.25;
    A.matrix[0][1] = 1.25;
    A.matrix[0][2] = 2.25;
    A.matrix[1][0] = 3.25;
    A.matrix[1][1] = 4.25;
    A.matrix[1][2] = 5.25;
    A.matrix[2][0] = 6.25;
    A.matrix[2][1] = 7.25;
    A.matrix[2][2] = 8.25;

    B.matrix[0][0] = 0.25;
    B.matrix[0][1] = 1.25;
    B.matrix[0][2] = 2.25;
    B.matrix[1][0] = 3.25;
    B.matrix[1][1] = 4.25;
    B.matrix[1][2] = 5.25;
    B.matrix[2][0] = 6.25;
    B.matrix[2][1] = 7.25;
    B.matrix[2][2] = 8.25;


    ck_assert_int_eq(s21_eq_matrix(&A, &B), 1);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
} END_TEST

Suite *create_suite_eq_matrix() {
    Suite *s = suite_create("eq_matrix");
    TCase *tc = tcase_create("eq_matrix_tc");

    tcase_add_test(tc, eq_test_1);
    tcase_add_test(tc, eq_test_2);

    suite_add_tcase(s, tc);
    return s;
}