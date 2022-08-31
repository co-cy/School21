//
// Created by Nana Daughterless on 8/31/22.
//

#include <string.h>
#include "structs/lex_stack/lex_stack.h"
#include "structs/lexeme/lexem.h"
#include "structs/operators/operators.h"
#include "features.h"


int word_to_polish(char *word, t_stack **polish, t_stack **operators) {
    int error_code = 0;
    t_lexeme *lexeme = create_lexeme(word, type_lexeme_undefined);

    if (lexeme->type == type_lexeme_number) {
        *polish = add_to_lex_stack(*polish, lexeme);
    } elif (!strcmp(word, "(") || lexeme->type == type_lexeme_command) {
        *operators = add_to_lex_stack(*operators, lexeme);
    } elif (lexeme->type == type_lexeme_operator) {
        if (!strcmp(lexeme->string, ")")) {
            while (*operators && strcmp((*operators)->lexeme->string, "("))
                *polish = add_to_lex_stack(*polish, pop_lex_stack(operators));

            if (*operators) {
                dump_lex_stack(operators);
                free_lexeme(&lexeme);

                while (*operators && (*operators)->lexeme->type == type_lexeme_command)
                    *polish = add_to_lex_stack(*polish, pop_lex_stack(operators));
            } else {
                error_code = 1;
            }
        } else {
            int cur_priority = char_to_priority_operator(*word);
            while (*operators && cur_priority <= char_to_priority_operator(*((*operators)->lexeme->string)))
                *polish = add_to_lex_stack(*polish, pop_lex_stack(operators));

            *operators = add_to_lex_stack(*operators, lexeme);
        }
    } else {
        error_code = 1;
    }

    return error_code;
}