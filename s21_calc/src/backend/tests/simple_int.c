#include "main.h"

START_TEST(simple_int_sum){
    char string[256];
    long int value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%ld + %ld", value, value2);
    long double true_result = value + value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_int_sub){
    char string[256];
    long int value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%ld - %ld", value, value2);
    long double true_result = value - value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_int_mul){
    char string[256];
    long int value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%ld * %ld", value, value2);
    long double true_result = value * value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_int_div){
    char string[256];
    long int value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%ld / %ld", value, value2);
    long double true_result = value / (long double)value2;

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_int_mod){
    char string[256];
    long int value = get_random(-RAND_MAX / 2, RAND_MAX / 2), value2 = get_random(-RAND_MAX / 2, RAND_MAX / 2);
    sprintf(string, "%ld mod %ld", value, value2);
    long double true_result = fmodl(value, value2);

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_int_degree){
    char string[256];
    long int value = get_random(0, 1000), value2 = get_random(-10, 10);
    sprintf(string, "%ld ^ %ld", value, value2);
    long double true_result = powl(value, value2);

    long double result = 0;
    ck_assert_int_eq(calc(string, 0, &result), 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

Suite *create_simple_int_testcase() {
    Suite *s = suite_create("simple_int_suite");
    TCase *tc = tcase_create("simple_int_testcase");

    tcase_add_loop_test(tc, simple_int_sum, 0, 1000);
    tcase_add_loop_test(tc, simple_int_sub, 0, 1000);
    tcase_add_loop_test(tc, simple_int_mul, 0, 1000);
    tcase_add_loop_test(tc, simple_int_div, 0, 1000);
    tcase_add_loop_test(tc, simple_int_mod, 0, 1000);
    tcase_add_loop_test(tc, simple_int_degree, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}