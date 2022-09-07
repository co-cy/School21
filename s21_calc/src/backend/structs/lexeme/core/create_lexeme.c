//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

t_lexeme *create_lexeme(char *string, type_lexeme type) {
    /// Creates a new lexeme based on the string and the type of the lexeme
    /// "string" - pointer to the allocated string in memory
    /// "type" - the type of the new lexeme

    // TODO(nanadaug): Take out a normal error code handler
    t_lexeme *new_lexeme = malloc(sizeof(t_lexeme));
    if (!new_lexeme)
        exit(1);

    if (type == type_lexeme_undefined)
        new_lexeme->type = get_type_lexeme_from_string(string);
    else
        new_lexeme->type = type;

    new_lexeme->string = string;

    return new_lexeme;
}
