//
// Created by Nana Daughterless on 6/29/22.
//

#include <string.h>

#include "calculator.h"
#include "structs/lex_stack/lex_stack.h"
#include "structs/lexeme/lexem.h"

t_stack *string_to_polish(char *string) {
  t_stack *polish = NULL;
  t_stack *operators = NULL;

  int error_code = 0;
  char *tmp_world = strtok_r(string, " ", &string);
  while (!error_code && tmp_world) {
    char *word = calloc(strlen(tmp_world) + 1, sizeof(char));
    snprintf(word, strlen(tmp_world) + 1, "%s", tmp_world);

    error_code = word_to_polish(word, &polish, &operators);
    if (error_code) free(word);

    tmp_world = strtok_r(NULL, " ", &string);
  }

  if (error_code) {
    if (polish) free_lex_stack(&polish);
    if (operators) free_lex_stack(&operators);

    polish = NULL;
  } else {
    while (operators) {
      polish = add_to_lex_stack(polish, pop_lex_stack(&operators));
    }
  }

  return polish;
}
