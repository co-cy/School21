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

    t_stack *aboba = string_to_polish(string);
    print_stack(aboba);

    free_stack(&aboba);

    printf("_%s_", string);

    free(string);
    return 0;
}

