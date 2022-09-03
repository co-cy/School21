//
// Created by Nana Daughterless on 6/28/22.
//

#ifndef S21_CALC_OPERATORS_CORE_H
#define S21_CALC_OPERATORS_CORE_H


typedef struct {
    char short_name;
    const char *long_name;
    int priority;
} t_operator;


static t_operator list_operators[] = {
        {'(', "(",    1},
        {')', ")",    1},
        {'+', "+",    2},
        {'-', "-",    2},
        {'*', "*",    3},
        {'/', "/",    3},
        {'%', "mod",  3},
        {'0', "cos",  3},
        {'0', "sin",  3},
        {'0', "tan",  3},
        {'0', "acos", 3},
        {'0', "asin", 3},
        {'0', "atan", 3},
        {'0', "sqrt", 3},
        {'0', "ln",   3},
        {'0', "log",  3},
        {'^', "^",    4},
        // A string that signals us about the end of the list
        {0,   0,      0},
};


#endif //S21_CALC_OPERATORS_CORE_H
