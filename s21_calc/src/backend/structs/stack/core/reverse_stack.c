//
// Created by Nana Daughterless on 6/29/22.
//

#include "core.h"

t_stack *reverse_stack(t_stack *stack) {
    /// Flips the pile, the bottom element becomes the top one, and the top one becomes the bottom one

    t_stack *tmp;
    t_stack *new_stack = NULL;
    while (stack) {
        new_stack = add_to_stack(new_stack, stack->lexeme);

        tmp = stack->lower;
        free(stack);
        stack = tmp;
    }

    return new_stack;
}
