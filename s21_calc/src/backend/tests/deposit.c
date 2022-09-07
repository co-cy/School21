//
// Created by Nana Daughterless on 9/7/22.
//

#include "main.h"

START_TEST(deposit_1) {
  int error = 0;
  t_deposit res =
      deposit_calc(1000, 12, 12, 0, 1, 0, "1 1000", "1 1000", &error);

  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(res.tax, 0, 1e-7);
  ck_assert_double_eq_tol(res.contribution, 1120, 1e-7);
}
END_TEST

START_TEST(deposit_2) {
  int error = 0;
  t_deposit res =
      deposit_calc(1000, 12, 12, 0, 1, 1, "1 1000", "1 1000", &error);

  ck_assert_int_eq(error, 0);
  ck_assert_double_eq_tol(res.tax, 0, 1e-7);
  ck_assert_double_eq_tol(res.contribution, 1126.83, 1e-2);
}
END_TEST

Suite *create_deposit_testcase() {
  Suite *s = suite_create("deposit_suite");
  TCase *tc = tcase_create("deposit_testcase");

  tcase_add_test(tc, deposit_1);
  tcase_add_test(tc, deposit_2);

  suite_add_tcase(s, tc);
  return s;
}