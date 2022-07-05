//
// Created by Nana Daughterless on 6/29/22.
//

#include "core.h"

t_ld_stack* add_to_ld_stack(t_ld_stack *stack, long double value) {
    /// Add a new segment to the stack
    /// Returns a pointer to the beginning of the stack

    t_ld_stack *new_segment = create_ld_stack(value);
    new_segment->lower = stack;

    return new_segment;
}
