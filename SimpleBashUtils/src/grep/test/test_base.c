#include "s21_grep_test.h"

START_TEST(base_test1) {
    system("grep void ./data-samples/void > tmp1");
    system("./build/s21_grep void ./data-samples/void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(base_test2) {
    system("grep Lorem ./data-samples/text > tmp1");
    system("./build/s21_grep Lorem ./data-samples/text > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_base(void) {
    Suite *s = suite_create("suite_base");
    TCase *tc = tcase_create("base_tc");

    tcase_add_test(tc, base_test1);
    tcase_add_test(tc, base_test2);

    suite_add_tcase(s, tc);
    return s;
}