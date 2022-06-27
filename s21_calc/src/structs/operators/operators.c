//
// Created by Nana Daughterless on 6/27/22.
//

#include "operators.h"

bool isoperator(char symbol) {
    /// Checks whether a character is an operator
    bool is = False;

    for (t_s21_operator *cur_operator = list_operators; !is && cur_operator->short_name; cur_operator++)
        if (symbol == cur_operator->short_name)
            is = True;

    return is;
}

bool string_is_operator(char *string) {
    /// Checks whether the string is an operator
    bool is = False;

    for (t_s21_operator *cur_operator = list_operators; !is && cur_operator->short_name; cur_operator++) {
        if (!strcmp(string, list_operators->long_name))
            is = True;
    }

    return is;}
