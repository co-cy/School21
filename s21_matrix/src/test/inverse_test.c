//
// Created by Nana Daughterless on 6/24/22.
//

#include "main.h"

START_TEST(inverse_test_1) {
    matrix_t A, B, R;
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);

    A.matrix[0][0] = 1.25;
    B.matrix[0][0] = 0.8;

    s21_inverse_matrix(&A, &R);
//    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
} END_TEST

//START_TEST(inverse_test_2) {
//    matrix_t A, B, R;
//    s21_create_matrix(3, 3, &A);
//    s21_create_matrix(3, 3, &B);
//
//    A.matrix[0][0] = -1;
//    A.matrix[0][1] = -10;
//    A.matrix[0][2] = 1;
//    A.matrix[1][0] = 1;
//    A.matrix[1][1] = 10;
//    A.matrix[1][2] = 1;
//    A.matrix[2][0] = 1;
//    A.matrix[2][1] = 1;
//    A.matrix[2][2] = 1;
//
//    s21_inverse_matrix(&A, &R);
//
//    B.matrix[0][0] = -0.5;
//    B.matrix[0][1] = -11.0/18.0;
//    B.matrix[0][2] = 10.0/9.0;
//    B.matrix[1][0] = 0;
//    B.matrix[1][1] = 1.0/9.0;
//    B.matrix[1][2] = -1.0/9.0;
//    B.matrix[2][0] = 0.5;
//    B.matrix[2][1] = 0.5;
//    B.matrix[2][2] = 0;
//
//
//    ck_assert_int_eq(s21_eq_matrix(&R, &B), 1);
//
//    s21_remove_matrix(&A);
//    s21_remove_matrix(&B);
//    s21_remove_matrix(&R);
//} END_TEST

Suite *create_suite_inverse_matrix() {
    Suite *s = suite_create("inverse_matrix");
    TCase *tc = tcase_create("inverse_matrix_tc");

    tcase_add_test(tc, inverse_test_1);
//    tcase_add_test(tc, inverse_test_2);

    suite_add_tcase(s, tc);
    return s;
}