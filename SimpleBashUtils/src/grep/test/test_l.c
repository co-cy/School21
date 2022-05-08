#include "s21_grep_test.h"

START_TEST(l_test1) {
    system("grep -l void ./data-samples/void ./data-samples/char > tmp1");
    system("./build/s21_grep -l void ./data-samples/void ./data-samples/char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(l_test2) {
    system("grep -l void ./data-samples/char > tmp1");
    system("./build/s21_grep -l void ./data-samples/char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(l_test3) {
    system("grep -l void ./data-samples/void > tmp1");
    system("./build/s21_grep -l void ./data-samples/void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_l(void) {
    Suite *s = suite_create("suite_l");
    TCase *tc = tcase_create("l_tc");

    tcase_add_test(tc, l_test1);
    tcase_add_test(tc, l_test2);
    tcase_add_test(tc, l_test3);

    suite_add_tcase(s, tc);
    return s;
}