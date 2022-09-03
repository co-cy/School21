//
// Created by Nana Daughterless on 6/29/22.
//

#include "core.h"

t_lexeme *pop_lex_stack(t_stack **stack) {
    /// Returns a pointer to the token that was on the stack

    t_lexeme *lexeme = NULL;
    if (*stack) {
        lexeme = (*stack)->lexeme;
        t_stack *tmp = (*stack)->lower;
        free(*stack);
        *stack = tmp;
    }

    return lexeme;
}
