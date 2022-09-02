//
// Created by Nana Daughterless on 9/1/22.
//

#include "main.h"

int failed_tests = 0;

int main() {
    Suite *list_cases[] = {
            create_simple_int_testcase(),
            create_simple_float_testcase(),
            create_trigonometry_testcase(),
            NULL};

    for (Suite **testcase = list_cases; *testcase != NULL; testcase++) {
        run_testcase(*testcase);
    }

//    long double res;
//    long double v1 = -1;
//    long double v2 = 1;
//    char a[256];
//    printf("AAA - %LF", strtold("-12", NULL));
//    sprintf(a, "%Lf - %Lf", v1, v2);
//    calc(a, 0, &res);
//    printf("RES - %Lf, TRUE - %Lf", res, v1 - v2);

    if (failed_tests) {
        fprintf(stderr, "FAIL TEST: %d\n", failed_tests);
    }

    return 0;
}

void run_testcase(Suite *testcase) {
    static int counter_testcase = 1;

    if (counter_testcase > 1)
        putchar('\n');

    printf("CURRENT TEST: %d\n", counter_testcase);
    counter_testcase++;

    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed_tests += srunner_ntests_failed(sr);

    srunner_free(sr);
}

long double get_random(long double start, long double stop) {
    static unsigned int rand_seed = 0;
    if (!rand_seed)
        rand_seed = time(NULL);

    long double random = rand_r(&rand_seed) / (long double)RAND_MAX;

    return start + random * (fabsl(stop - start));
}

long double get_EPS(long double true_result, long double result) {
    if (fabsl(result) > fabsl(true_result))
        result = true_result;

    long double eps = (EPS * fabsl(result));
    if (eps < EPS) {
        return EPS;
    } else {
        return eps;
    }
}
