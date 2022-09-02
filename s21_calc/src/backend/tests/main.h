//
// Created by Nana Daughterless on 9/1/22.
//

#ifndef S21_CALC_MAIN_H
#define S21_CALC_MAIN_H


// Include system library
#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <time.h>


// Include custom library
#include "../calculator.h"
#include "../features.h"


#define EPS 1e-5

long double get_EPS(long double true_result, long double result);
long double get_random(long double start, long double stop);
void run_testcase(Suite *testcase);

Suite *create_simple_float_testcase();
Suite *create_simple_int_testcase();
Suite *create_trigonometry_testcase();
Suite *create_bad_testcase();
Suite *create_hard_testcase();


#endif //S21_CALC_MAIN_H
