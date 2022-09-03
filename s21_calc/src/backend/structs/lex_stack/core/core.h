//
// Created by Nana Daughterless on 6/28/22.
//

#ifndef S21_CALC_STACK_CORE_H
#define S21_CALC_STACK_CORE_H


// Include system library
#include <stdlib.h>


// Include custom library
#include "../../lexeme/core/core.h"


typedef struct s_stack {
    t_lexeme *lexeme;
    struct s_stack *lower;
} t_stack;


t_stack *create_lex_stack(t_lexeme *lexeme);

void free_lex_stack(t_stack **stack);

t_stack *add_to_lex_stack(t_stack *stack, t_lexeme *lexeme);

void dump_lex_stack(t_stack **stack);

t_stack *reverse_lex_stack(t_stack *stack);

t_lexeme *pop_lex_stack(t_stack **stack);


#endif //S21_CALC_STACK_CORE_H
