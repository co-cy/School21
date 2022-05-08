#include "s21_grep_test.h"

START_TEST(s_test1) {
    system("grep -s void AHAHAHAHA > tmp1");
    system("./build/s21_grep -s void AHAHAHA > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(s_test2) {
    system("grep -s ./data-samples/void -f AHAHAHAHA ./data-samples/file > tmp1");
    system("./build/s21_grep -s ./data-samples/void -f AHAHAHA ./data-samples/file > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_s(void) {
    Suite *s = suite_create("suite_s");
    TCase *tc = tcase_create("s_tc");

    tcase_add_test(tc, s_test1);
    tcase_add_test(tc, s_test2);

    suite_add_tcase(s, tc);
    return s;
}