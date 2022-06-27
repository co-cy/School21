//
// Created by Nana Daughterless on 6/27/22.
//

#include "stack.h"

t_s21_stack* create_stack(void* value, type_stack type) {
    ///    Creates a stack and returns a pointer to it,
    ///    "type" - what type is currently stored in the stack
    ///    "value" - pointer to data

    t_s21_stack *new_stack = malloc(sizeof(t_s21_stack));

    new_stack->type = type;
    new_stack->value = value;
    new_stack->lower = NULL;

    return new_stack;
}

t_s21_stack* add2stack(t_s21_stack *stack, void* value, type_stack type) {
    /// Add a new segment to the stack
    /// "value" - the value that will be written to the new stack
    /// "type" - type of the newly added segment
    t_s21_stack *new_segment = create_stack(value, type);

    new_segment->lower = stack;

    return new_segment;
}

void free_stack(t_s21_stack** stack) {
    /// The function cleans up the entire stack except for its segments
    while (*stack) {
        t_s21_stack *tmp = (*stack)->lower;

        free(*stack);
        *stack = tmp;
    }
}
