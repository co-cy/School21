//
// Created by Nana Daughterless on 6/3/22.
//

#include "decimal_core.h"

int get_sign(s21_decimal a) {
    /// Return 0 if a is positive else return not zero
    return a.bits[DECIMAL_INFO] & (1 << SIGN_BIT);
}

