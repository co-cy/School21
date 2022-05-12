//
// Created by Nana Daughterless on 5/12/22.
//

#ifndef SIMPLEBASHUTILS_GREP_PARSER_H
#define SIMPLEBASHUTILS_GREP_PARSER_H

#include "../linked_list/linked_list.h"
#include "grep.h"

status_code_e parsing_argv(int argc, char **argv, linked_list_t *files, linked_list_t *patterns, int *flags, status_code_e status);

char* strip(char *string);
char *new_strcpy(char *str);

#endif  // SIMPLEBASHUTILS_GREP_PARSER_H
