//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

t_stack* create_stack(t_lexeme* lexeme) {
    ///    Creates a stack and returns a pointer to it,
    ///    "lexeme" - pointer to the allocated memory containing the lexeme

    t_stack *new_stack = malloc(sizeof(t_stack));

    if (!new_stack)
        exit(666);

    new_stack->lexeme = lexeme;
    new_stack->lower = NULL;

    return new_stack;
}
