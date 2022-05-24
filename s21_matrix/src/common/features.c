//
// Created by _co_cy_ on 24.05.22.
//

#include "features.h"

int ldouble_eq(long double a, long double b) {
    return fabsl(a - b) < EPS;
}
