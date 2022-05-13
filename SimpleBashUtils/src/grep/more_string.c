//
// Created by Nana Daughterless on 5/12/22.
//

#include <string.h>
#include <stdlib.h>
#include "grep.h"


char* strip(char *string) {
    char *b = strchr(string, '\n');
    if (b)
        *b = '\0';
    return string;
}

char *new_strcpy(char *str) {
    char *new_str = malloc(strlen(str) + 1);
    return strcpy(new_str, str);
}
