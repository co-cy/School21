//
// Created by Nana Daughterless on 6/27/22.
//

#ifndef S21_CALC_S21_CALC_H
#define S21_CALC_S21_CALC_H

#include "structs/operators/operators.h"
#include "structs/ld_stack/ld_stack.h"
#include "structs/lexeme/lexem.h"
#include "structs/stack/stack.h"


t_stack *string_to_polish(char *string);

int word_to_polish(char *word, t_stack **polish, t_stack **operators);

int calc(char *string, long double *result);

#endif //S21_CALC_S21_CALC_H
