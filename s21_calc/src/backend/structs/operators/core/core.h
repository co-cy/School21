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

t_operator* get_list_operators();



#endif //S21_CALC_OPERATORS_CORE_H
