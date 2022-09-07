//
// Created by Nana Daughterless on 9/7/22.
//

#include "main.h"

START_TEST(credit_1) {
    ck_assert_double_eq_tol(credit_calc_annuity(1000, 12, 12), 88.8488, 1e-4);
}
END_TEST

START_TEST(credit_2) {
    ck_assert_double_eq_tol(credit_calc_differentiate(1000, 12, 1, 12), 93.3333, 1e-4);
}
END_TEST

Suite *create_credit() {
    Suite *s = suite_create("credit_suite");
    TCase *tc = tcase_create("credit_testcase");

    tcase_add_test(tc, credit_1);
    tcase_add_test(tc, credit_2);

    suite_add_tcase(s, tc);
    return s;
}
