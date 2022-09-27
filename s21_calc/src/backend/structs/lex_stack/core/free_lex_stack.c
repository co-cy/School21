//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

void free_lex_stack(t_stack **stack) {
  /// The function cleans up the entire stack except for its segments

  while (*stack) {
    t_stack *tmp = (*stack)->lower;

    free_lexeme(&(*stack)->lexeme);
    free(*stack);

    *stack = tmp;
  }
}
