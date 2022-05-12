//
// Created by Nana Daughterless on 5/12/22.
//

#include <string.h>
#include <stdlib.h>
#include "grep.h"


char* strip(char *string) {
    for (size_t i = strlen(string); i && string[i] == '\n'; i--)
        string[i] = '\0';
    return string;
}

char *new_strcpy(char *str) {
    char *new_str = malloc(strlen(str) + 1);
    return strcpy(new_str, str);
}
