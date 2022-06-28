//
// Created by Nana Daughterless on 6/28/22.
//

#ifndef S21_CALC_OPERATORS_CORE_H
#define S21_CALC_OPERATORS_CORE_H

typedef struct {
    char short_name;
    char *long_name;
    int priority;
} t_operator;

static t_operator list_operators[] = {
        {'(', "(", 1},
        {')', ")", 1},
        {'+', "+", 1},
        {'-', "-", 1},
        {'*', "*", 2},
        {'/', "/", 2},
        {'%', "mod", 2},
        {'0', "cos", 2},
        {'0', "sin", 2},
        {'0', "tan", 2},
        {'0', "acos", 2},
        {'0', "asin", 2},
        {'0', "atan", 2},
        {'0', "sqrt", 2},
        {'0', "ln", 2},
        {'0', "log", 2},
        {'^', "^", 3},
        // A string that signals us about the end of the list
        {0, 0, 0},
};

#endif //S21_CALC_OPERATORS_CORE_H
