//
// Created by Nana Daughterless on 6/29/22.
//

#include "core.h"

void dump_lex_stack(t_stack **stack) {
    /// Removes only the top block from the stack

    t_stack *tmp = (*stack)->lower;

    free_lexeme(&(*stack)->lexeme);
    free(*stack);

    *stack = tmp;
}
