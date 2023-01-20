//
// Created by Nana Daughterless on 6/29/22.
//

#ifndef S21_CALC_LD_STACK_CORE_H
#define S21_CALC_LD_STACK_CORE_H


// Include system library
#include <stdlib.h>


// Include custom library


typedef struct s_ld_stack {
    long double value;
    struct s_ld_stack *lower;
} t_ld_stack;


t_ld_stack *create_ld_stack(long double value);

void free_ld_stack(t_ld_stack **stack);

t_ld_stack *add_to_ld_stack(t_ld_stack *stack, long double value);

long double pop_ld_stack(t_ld_stack **stack);


#endif //S21_CALC_LD_STACK_CORE_H
