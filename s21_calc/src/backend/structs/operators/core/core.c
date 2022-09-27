//
// Created by Nana Daughterless on 9/7/22.
//

#include "core.h"

static t_operator list_operators[] = {
    {'(', "(", 1},
    {')', ")", 1},
    {'+', "+", 2},
    {'-', "-", 2},
    {'*', "*", 3},
    {'/', "/", 3},
    {'%', "mod", 3},
    {'0', "cos", 3},
    {'0', "sin", 3},
    {'0', "tan", 3},
    {'0', "acos", 3},
    {'0', "asin", 3},
    {'0', "atan", 3},
    {'0', "sqrt", 3},
    {'0', "ln", 3},
    {'0', "log", 3},
    {'^', "^", 4},
    // A string that signals us about the end of the list
    {0, 0, 0},
};

t_operator* get_list_operators() { return list_operators; }
