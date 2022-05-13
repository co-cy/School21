//
// Created by Nana Daughterless on 5/9/22.
//
#include "s21_math.h"

long double s21_acos(double x) {
    if (x + 1 < EPS || x - 1 > EPS) {
        // TODO: Figure out what to return during an error
        return 0/0;
    } else {
        return PI / 2 - s21_asin(x);
    }
}