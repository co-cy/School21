//
// Created by Nana Daughterless on 5/9/22.
//
#include "s21_math.h"
#include <math.h>
#include <stdio.h>

long double s21_asin(double x) {
    if (x + 1 < EPS || x - 1 > EPS) {
        // TODO: Figure out what to return during an error
        return 0/0;
    } else {
        long double res = 0;
        long double new_res = x;

        int n = 0;
        while (n < 10 || new_res - res > EPS) {

            res = new_res;
            new_res = ((double)s21_factorial(2 * n) * pow(x, 2 * n + 1)) /
                    (pow(4, n) * pow((double)s21_factorial(n), 2) * (2 * n + 1));
            printf("%Lf\n", new_res - res);
            printf("%f\n", (double)s21_factorial(2 * n) * pow(x, 2 * n + 1));
            printf("%f\n\n\n", pow(4, n) * pow((double)s21_factorial(n), 2) * (2 * n + 1));
            n++;
        }
        return res;
    }
}