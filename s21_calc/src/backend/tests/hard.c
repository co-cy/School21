#include "main.h"

START_TEST(hard_1){
    char string[256] = "( 2 + 2 * 2 )";
    long double true_result = 6;

    long double result;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(hard_2){
    char string[256] = "( 2 + 2 * ( 1 + 1 ) )";
    long double true_result = 6;

    long double result;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(hard_3){
    char string[256] = "( x + x * ( x + x ) )";
    long double true_result = 210;

    long double result;
    ck_assert_int_eq(calc(string, 10, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(hard_4){
    char string[256] = "( x = x )";

    long double result;
    ck_assert_int_eq(calc(string, 10, &result), 1);
} END_TEST

START_TEST(hard_5){
    char string[256] = "( x boba x )";

    long double result;
    ck_assert_int_eq(calc(string, 10, &result), 1);
} END_TEST

Suite *create_hard_testcase() {
    Suite *s = suite_create("simple_hard_suite");
    TCase *tc = tcase_create("simple_hard_testcase");

    tcase_add_test(tc, hard_1);
    tcase_add_test(tc, hard_2);
    tcase_add_test(tc, hard_3);
    tcase_add_test(tc, hard_4);
    tcase_add_test(tc, hard_5);

    suite_add_tcase(s, tc);
    return s;
}