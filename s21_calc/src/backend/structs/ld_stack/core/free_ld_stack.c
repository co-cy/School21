//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

void free_ld_stack(t_ld_stack **stack) {
    /// The function cleans up the entire stack except for its segments

    while (*stack) {
        t_ld_stack *tmp = (*stack)->lower;

        free(*stack);

        *stack = tmp;
    }
}
