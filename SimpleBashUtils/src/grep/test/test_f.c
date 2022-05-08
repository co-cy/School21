#include "s21_grep_test.h"

START_TEST(f_test1) {
    system("grep -f ./data-samples/void ./data-samples/v2 > tmp1");
    system("./build/s21_grep -f ./data-samples/void ./data-samples/v2 > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(f_test2) {
    system("grep -f ./data-samples/void ./data-samples/void > tmp1");
    system("./build/s21_grep -f ./data-samples/void ./data-samples/void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(f_test3) {
    system("grep -f ./data-samples/void -f ./data-samples/char ./data-samples/void ./data-samples/char > tmp1");
    system("./build/s21_grep -f ./data-samples/void -f ./data-samples/char ./data-samples/void ./data-samples/char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(f_test4) {
    system("grep -f ./data-samples/char ./data-samples/void > tmp1");
    system("./build/s21_grep -f ./data-samples/char ./data-samples/void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_f(void) {
    Suite *s = suite_create("suite_f");
    TCase *tc = tcase_create("f_tc");

    tcase_add_test(tc, f_test1);
    tcase_add_test(tc, f_test2);
    tcase_add_test(tc, f_test3);
    tcase_add_test(tc, f_test4);

    suite_add_tcase(s, tc);
    return s;
}