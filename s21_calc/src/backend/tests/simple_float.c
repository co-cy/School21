#include "main.h"

START_TEST(simple_float_sum){
    char string[256];
    long double value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%Lf + %Lf", value, value2);
    long double true_result = value + value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_float_sub){
    char string[256];
    long double value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%Lf - %Lf", value, value2);
    long double true_result = value - value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_float_mul){
    char string[256];
    long double value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%Lf * %Lf", value, value2);
    long double true_result = value * value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_float_div){
    char string[256];
    long double value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%Lf / %Lf", value, value2);
    long double true_result = value / value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_float_mod){
    char string[256];
    long double value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%Lf mod %Lf", value, value2);
    long double true_result = fmodl(value, value2);

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_float_degree){
    char string[256];
    long double value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%Lf ^ %Lf", value, value2);
    long double true_result = powl(value, value2);

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

Suite *create_simple_float_testcase() {
    Suite *s = suite_create("simple_float_suite");
    TCase *tc = tcase_create("simple_float_testcase");

    tcase_add_loop_test(tc, simple_float_sum, 0, 1000);
    tcase_add_loop_test(tc, simple_float_sub, 0, 1000);
    tcase_add_loop_test(tc, simple_float_mul, 0, 1000);
    tcase_add_loop_test(tc, simple_float_div, 0, 1000);
    tcase_add_loop_test(tc, simple_float_mod, 0, 1000);
    tcase_add_loop_test(tc, simple_float_degree, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}