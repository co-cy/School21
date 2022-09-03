//
// Created by Nana Daughterless on 6/29/22.
//

#include "core.h"

t_stack *add_to_lex_stack(t_stack *stack, t_lexeme *lexeme) {
    /// Add a new segment to the lexeme stack
    /// Returns a pointer to the beginning of the stack

    t_stack *new_segment = create_lex_stack(lexeme);
    new_segment->lower = stack;

    return new_segment;
}
