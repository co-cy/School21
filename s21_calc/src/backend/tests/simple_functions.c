#include "main.h"

START_TEST(simple_low_random_cos){
    char string[256];
    long double value = get_random(-1, 1);
    sprintf(string, "cos ( %Lf )", value);
    long double true_result = cosl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_acos){
    char string[256];
    long double value = get_random(-1, 1);
    sprintf(string, "acos ( %Lf )", value);
    long double true_result = acosl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_sin){
    char string[256];
    long double value = get_random(-1, 1);
    sprintf(string, "sin ( %Lf )", value);
    long double true_result = sinl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_asin){
    char string[256];
    long double value = get_random(-1, 1);
    sprintf(string, "asin ( %Lf )", value);
    long double true_result = asinl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_tan){
    char string[256];
    long double value = get_random(-1, 1);
    sprintf(string, "tan ( %Lf )", value);
    long double true_result = tanl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);

    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_atan){
    char string[256];
    long double value = get_random(-1, 1);
    sprintf(string, "atan ( %Lf )", value);
    long double true_result = atanl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);

    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_sqrt){
    char string[256];
    long double value = get_random(0, RAND_MAX / 2);
    sprintf(string, "sqrt ( %Lf )", value);
    long double true_result = sqrtl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_ln){
    char string[256];
    long double value = get_random(0e-7, RAND_MAX / 2);
    sprintf(string, "ln ( %Lf )", value);
    long double true_result = logl(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST

START_TEST(simple_low_random_log){
    char string[256];
    long double value = get_random(0e-7, RAND_MAX / 2);
    sprintf(string, "log ( %Lf )", value);
    long double true_result = log10l(value);

    long double result = 0;
    int error_code = calc(string, 0, &result);
    ck_assert_int_eq(error_code, 0);
    ck_assert_double_eq_tol(result, true_result, get_EPS(true_result, result));
} END_TEST


Suite *create_trigonometry_testcase() {
    Suite *s = suite_create("simple_suite");
    TCase *tc = tcase_create("simple_testcase");

    tcase_add_loop_test(tc, simple_low_random_cos, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_acos, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_sin, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_asin, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_tan, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_atan, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_sqrt, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_ln, 0, 1000);
    tcase_add_loop_test(tc, simple_low_random_log, 0, 1000);

    suite_add_tcase(s, tc);
    return s;
}