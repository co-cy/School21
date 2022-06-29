//
// Created by Nana Daughterless on 6/27/22.
//

#include "s21_calc.h"
#include <stdio.h>
#include <stdlib.h>

t_stack * string_to_polish(char *string);
int word_to_polish(char *word, t_stack **polish, t_stack **operators);

int main() {

    size_t len_malloc_mem_string = 1024;
    char *string = calloc(len_malloc_mem_string, sizeof (char));
    string[getline(&string, &len_malloc_mem_string, stdin) - 1] = '\0';

//    string[ - 1] = '\0';

    long double res;
    int status = calc(string, &res);

    printf("_STATUS - %d_\n", status);
    printf("_%s_\n", string);
    printf("_RESULT - %Lf_\n", res);

    free(string);
    return 0;
}

