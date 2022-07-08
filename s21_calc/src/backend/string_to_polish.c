//
// Created by Nana Daughterless on 6/29/22.
//

#include <string.h>
#include "structs/stack/stack.h"
#include "structs/lexeme/lexem.h"
#include "structs/operators/operators.h"
#include "features.h"

int word_to_polish(char *word, t_stack **polish, t_stack **operators) {
    int status = 0;
    t_lexeme *lexeme = create_lexeme(word, type_lexeme_bad);

    if (lexeme->type == type_lexeme_number) {
        *polish = add_to_stack(*polish, lexeme);
    } elif (!strcmp(word, "(") || lexeme->type == type_lexeme_command) {
        *operators = add_to_stack(*operators, lexeme);
    } elif (lexeme->type == type_lexeme_operator) {
        if (!strcmp(lexeme->string, ")")) {
            while (*operators) {
                if (strcmp((*operators)->lexeme->string, "(") != 0) {
                    *polish = add_to_stack(*polish, pop_stack(operators));
                } else {
                    break;
                }
            }

            if (*operators) {
                dump_stack(operators);
                free_lexeme(&lexeme);

                while (*operators) {
                    if ((*operators)->lexeme->type == type_lexeme_command) {
                        *polish = add_to_stack(*polish, pop_stack(operators));
                    } else {
                        break;
                    }
                }
            } else {
                status = 1;
            }

        } else {
            int cur_priority = char_to_priority_operator(*word);
            while (*operators) {
                int tmp_priority = char_to_priority_operator(*((*operators)->lexeme->string));
                if (cur_priority <= tmp_priority) {
                    *polish = add_to_stack(*polish, pop_stack(operators));
                } else {
                    break;
                }
            }

            *operators = add_to_stack(*operators, lexeme);
        }
    } else {
        status = 1;
    }

    return status;
}


t_stack *string_to_polish(char *string) {
    t_stack *polish = NULL;
    t_stack *operators = NULL;

    int status = 0;
    char *tmp_world = strtok(string, " ");
    while (!status && tmp_world) {
        char *word = calloc(strlen(tmp_world) + 1, sizeof(char));
        strcpy(word, tmp_world);

        printf("WORD - %s\n", word);
        status = word_to_polish(word, &polish, &operators);

        tmp_world = strtok(NULL, " ");
    }

    if (status) {
        if (polish)
            free_stack(&polish);
        if (operators)
            free_stack(&operators);

        polish = NULL;
    } else {
        while (operators) {
            polish = add_to_stack(polish, pop_stack(&operators));
        }
    }

    return polish;
}
