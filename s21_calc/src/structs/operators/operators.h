//
// Created by Nana Daughterless on 6/27/22.
//

#ifndef S21_CALC_OPERATORS_H
#define S21_CALC_OPERATORS_H

// Include system library
#include <string.h>

// Include custom library
#include "../../features.h"

typedef struct {
    char short_name;
    char *long_name;
    int priority;
} t_s21_operator;

static t_s21_operator list_operators[] = {
        {'+', "+", 0},
        {'-', "-", 0},
        {'*', "*", 1},
        {'/', "/", 1},
        {'%', "mod", 1},
        {'0', "cos", 1},
        {'1', "sin", 1},
        {'2', "tan", 1},
        {'3', "acos", 1},
        {'4', "asin", 1},
        {'5', "atan", 1},
        {'6', "sqrt", 1},
        {'7', "ln", 1},
        {'8', "log", 1},
        {'^', "^", 2},
        {0, 0, 0},
};

bool isoperator(char symbol);
bool string_is_operator(char *string);

#endif //S21_CALC_OPERATORS_H
