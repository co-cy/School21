//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

t_ld_stack * create_ld_stack(long double value) {
    ///    Creates a stack and returns a pointer to it,
    ///    "value" - the number that will be stored in the stack

    t_ld_stack *new_stack = malloc(sizeof(t_ld_stack));

    if (!new_stack)
        exit(666);

    new_stack->value = value;
    new_stack->lower = NULL;

    return new_stack;
}
