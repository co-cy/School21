//
// Created by Nana Daughterless on 6/28/22.
//

#include "debug.h"

void print_lex_stack(t_stack *stack) {
    /// Displays the contents of the stack of lexemes

    short was = 0;
    t_stack *tmp;
    while (stack) {
        if (was)
            printf("\t\t\t\t---BELOW---\n");
        was = 1;

        tmp = stack->lower;
        printf("\t\t[%s]\n", stack->lexeme->string);
        stack = tmp;
    }
}
