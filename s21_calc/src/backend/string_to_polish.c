//
// Created by Nana Daughterless on 6/29/22.
//

#include <string.h>
#include "structs/lex_stack/lex_stack.h"
#include "structs/lexeme/lexem.h"
#include "calculator.h"


t_stack *string_to_polish(char *string) {
    t_stack *polish = NULL;
    t_stack *operators = NULL;

    int error_code = 0;
    char *tmp_world = strtok(string, " ");
    while (!error_code && tmp_world) {
        char *word = calloc(strlen(tmp_world) + 1, sizeof(char));
        strcpy(word, tmp_world);

        // TODO: delete debug print
        printf("WORD - %s\n", word);
        error_code = word_to_polish(word, &polish, &operators);

        tmp_world = strtok(NULL, " ");
    }

    if (error_code) {
        if (polish)
            free_lex_stack(&polish);
        if (operators)
            free_lex_stack(&operators);

        polish = NULL;
    } else {
        while (operators) {
            polish = add_to_lex_stack(polish, pop_lex_stack(&operators));
        }
    }

    return polish;
}
