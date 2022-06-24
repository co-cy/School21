//
// Created by Nana Daughterless on 6/24/22.
//

#ifndef S21_MATRIX_MAIN_H
#define S21_MATRIX_MAIN_H

#include <check.h>
#include <stdio.h>
#include <time.h>

#include "../s21_matrix.h"


void run_testcase(Suite *testcase);

Suite *create_suite_sum_matrix();
Suite *create_suite_sub_matrix();
Suite *create_suite_mult_matrix();
Suite *create_suite_eq_matrix();
Suite *create_suite_complements_matrix();
Suite *create_suite_determinant_matrix();
Suite *create_suite_inverse_matrix();
Suite *create_suite_transpose_matrix();

#endif //S21_MATRIX_MAIN_H
