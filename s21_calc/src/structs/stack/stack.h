//
// Created by Nana Daughterless on 6/27/22.
//

#ifndef S21_CALC_STACK_H
#define S21_CALC_STACK_H

// Include system library
#include <stdlib.h>

// Include custom library
#include "constant.h"

typedef struct s_s21_stack{
    void *value;
    type_stack type;

    struct s_s21_stack *lower;
} t_s21_stack;

t_s21_stack* create_stack(void* value, type_stack type);
t_s21_stack* add2stack(t_s21_stack *stack, void* value, type_stack type);
void free_stack(t_s21_stack** stack);

#endif //S21_CALC_STACK_H
