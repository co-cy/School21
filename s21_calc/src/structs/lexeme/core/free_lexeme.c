//
// Created by Nana Daughterless on 6/28/22.
//

#include "core.h"

void free_lexeme(t_lexeme **lexeme) {
    /// Clears the lexeme completely, including the lexeme itself

    free((*lexeme)->string);
    free(*lexeme);
}
