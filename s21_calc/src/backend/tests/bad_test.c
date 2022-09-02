#include "main.h"

START_TEST(sign_end_1){
    char string[256];
    sprintf(string, "%LF ", get_random(-RAND_MAX / 2, RAND_MAX / 2));

    int type_sign = get_random(0, 7);

    if (type_sign == 0) {
        strcat(string, "-");
    } elif (type_sign == 1) {
        strcat(string, "+");
    } elif (type_sign == 2) {
        strcat(string, "*");
    } elif (type_sign == 3) {
        strcat(string, "/");
    } elif (type_sign == 4) {
        strcat(string, "^");
    } elif (type_sign == 5) {
        strcat(string, "mod");
    } else {
        strcat(string, "trash");
    }

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(sign_end_2){
    char string[256];
    sprintf(string, "%LF ", get_random(-RAND_MAX / 2, RAND_MAX / 2));

    int type_sign = get_random(0, 7);

    if (type_sign == 0) {
        strcat(string, "- ");
    } elif (type_sign == 1) {
        strcat(string, "+ ");
    } elif (type_sign == 2) {
        strcat(string, "* ");
    } elif (type_sign == 3) {
        strcat(string, "/ ");
    } elif (type_sign == 4) {
        strcat(string, "^ ");
    } elif (type_sign == 5) {
        strcat(string, "mod ");
    } else {
        strcat(string, "trash ");
    }

    char tmp_string[256];
    sprintf(tmp_string, "%Lf", get_random(-RAND_MAX / 2, RAND_MAX / 2));
    strcat(string, tmp_string);

    type_sign = get_random(0, 7);
    if (type_sign == 0) {
        strcat(string, " -");
    } elif (type_sign == 1) {
        strcat(string, " +");
    } elif (type_sign == 2) {
        strcat(string, " *");
    } elif (type_sign == 3) {
        strcat(string, " /");
    } elif (type_sign == 4) {
        strcat(string, " ^");
    } elif (type_sign == 5) {
        strcat(string, " mod");
    } else {
        strcat(string, "trash");
    }

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(bad_brackets_1){
    char string[256];
    sprintf(string, "( %LF", get_random(-RAND_MAX / 2, RAND_MAX / 2));

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(bad_brackets_2){
    char string[256];
    sprintf(string, "%LF )", get_random(-RAND_MAX / 2, RAND_MAX / 2));

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(bad_brackets_3){
    char string[256];
    sprintf(string, "( %LF + %Lf  ) )",
            get_random(-RAND_MAX / 2, RAND_MAX / 2),
            get_random(-RAND_MAX / 2, RAND_MAX / 2));

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(bad_brackets_4){
    char string[256];
    sprintf(string, "( ( %LF + %Lf )",
            get_random(-RAND_MAX / 2, RAND_MAX / 2),
            get_random(-RAND_MAX / 2, RAND_MAX / 2));

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(bad_more_numbers_1){
    char string[256];
    sprintf(string, "%LF %Lf",
            get_random(-RAND_MAX / 2, RAND_MAX / 2),
            get_random(-RAND_MAX / 2, RAND_MAX / 2));

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST

START_TEST(bad_more_numbers_2){
    char string[256];
    sprintf(string, "%LF %Lf +",
            get_random(-RAND_MAX / 2, RAND_MAX / 2),
            get_random(-RAND_MAX / 2, RAND_MAX / 2));

    long double res;
    ck_assert_int_eq(calc(string, 0, &res), 1);
} END_TEST


Suite *create_bad_testcase() {
    Suite *s = suite_create("simple_float_suite");
    TCase *tc = tcase_create("simple_float_testcase");

    tcase_add_loop_test(tc, sign_end_1, 0, 100);
    tcase_add_loop_test(tc, sign_end_2, 0, 100);

    tcase_add_loop_test(tc, bad_brackets_1, 0, 10);
    tcase_add_loop_test(tc, bad_brackets_2, 0, 10);
    tcase_add_loop_test(tc, bad_brackets_3, 0, 10);
    tcase_add_loop_test(tc, bad_brackets_4, 0, 10);

    tcase_add_loop_test(tc, bad_more_numbers_1, 0, 10);
    tcase_add_loop_test(tc, bad_more_numbers_2, 0, 10);

    suite_add_tcase(s, tc);
    return s;
}