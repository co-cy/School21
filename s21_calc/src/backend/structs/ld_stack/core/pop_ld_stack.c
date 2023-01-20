//
// Created by Nana Daughterless on 6/29/22.
//

#include "core.h"

long double pop_ld_stack(t_ld_stack **stack) {
  /// Returns the number stored in the stack by removing the top element of the
  /// stack

  long double value = 0;
  if (*stack) {
    value = (*stack)->value;

    t_ld_stack *tmp = (*stack)->lower;
    free(*stack);
    *stack = tmp;
  }

  return value;
}
