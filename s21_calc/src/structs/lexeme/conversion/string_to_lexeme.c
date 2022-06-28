//
// Created by Nana Daughterless on 6/29/22.
//

#include "conversion.h"


int string_to_lexeme(char *string, t_lexeme** lexeme) {
    /// Converts a string to a lexeme

    if (string[0] == '+' || string[0] == '-')
        string++;

    int len = strlen(string);
    char *long_name_lexeme = calloc(len + 1, sizeof(char));
    strncpy(long_name_lexeme, string, len);

    *lexeme = create_lexeme(long_name_lexeme, type_lexeme_bad);

    return len;
}
