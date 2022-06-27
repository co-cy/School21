//
// Created by Nana Daughterless on 6/27/22.
//

#ifndef S21_CALC_STACK_H
#define S21_CALC_STACK_H

#include "stdlib.h"

typedef struct s_s21_stack{
    void *value;
    size_t type;

    struct s_s21_stack *lower;
} t_s21_stack;

t_s21_stack* create_stack(void* value, size_t type);
t_s21_stack* add2stack(t_s21_stack *stack, void* value, size_t type);
void free_stack(t_s21_stack** stack);

#endif //S21_CALC_STACK_H
