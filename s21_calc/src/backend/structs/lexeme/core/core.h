//
// Created by Nana Daughterless on 6/28/22.
//

#ifndef S21_CALC_LEXEME_CORE_H
#define S21_CALC_LEXEME_CORE_H


// Include system library
#include <stdlib.h>
#include <ctype.h>


// Include custom library
#include "../../operators/comparison/comparison.h"
#include "../../../features.h"


typedef enum {
    type_lexeme_bad = -1,
    type_lexeme_number = 0,
    type_lexeme_command = 1,
    type_lexeme_operator = 2,
} type_lexeme;


typedef struct {
    type_lexeme type;
    char *string;
} t_lexeme;


t_lexeme *create_lexeme(char *string, type_lexeme type);

void free_lexeme(t_lexeme **lexeme);

type_lexeme get_type_lexeme_from_string(char *string);

#endif //S21_CALC_LEXEME_CORE_H
