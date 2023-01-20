//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

type_lexeme get_type_lexeme_from_string(char *string) {
  /// The function returns the token type, determined from the string
  type_lexeme result;

  if ((string[0] == '+' || string[0] == '-') && strlen(string) > 1) string++;

  if (isdigit(string[0]) || string[0] == 'e' || string[0] == 'x') {
    result = type_lexeme_number;
  }
  elif (!strcmp(string, "mod") || char_is_operator(string[0])) {
    result = type_lexeme_operator;
  }
  elif (string_is_command(string)) { result = type_lexeme_command; }
  else {
    result = type_lexeme_bad;
  }

  return result;
}
