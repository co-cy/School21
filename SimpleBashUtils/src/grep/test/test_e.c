#include "s21_grep_test.h"

START_TEST(e_test1) {
    system("grep -e void ./data-samples/void > tmp1");
    system("./build/s21_grep -e void ./data-samples/void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(e_test2) {
    system("grep -e Loerm ./data-samples/text > tmp1");
    system("./build/s21_grep -e Loerm ./data-samples/text > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(e_test3) {
    system("grep ./data-samples/char -e char > tmp1");
    system("./build/s21_grep ./data-samples/char -e char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(e_test4) {
    system("grep ./data-samples/char -e void -e char > tmp1");
    system("./build/s21_grep ./data-samples/char -e void -e char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(e_test5) {
    system("grep -e void ./data-samples/char > tmp1");
    system("./build/s21_grep -e void ./data-samples/char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_e(void) {
    Suite *s = suite_create("suite_e");
    TCase *tc = tcase_create("e_tc");

    tcase_add_test(tc, e_test1);
    tcase_add_test(tc, e_test2);
    tcase_add_test(tc, e_test3);
    tcase_add_test(tc, e_test4);
    tcase_add_test(tc, e_test5);

    suite_add_tcase(s, tc);
    return s;
}