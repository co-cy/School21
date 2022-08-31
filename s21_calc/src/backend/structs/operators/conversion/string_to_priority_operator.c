//
// Created by Nana Daughterless on 6/28/22.
//

#include "conversion.h"

int string_to_priority_operator(char *string) {
    /// Converts a string to a command priority
    int priority = 0;

    for (int i = 0; !priority && list_operators[i].short_name; i++) {
        if (!strcmp(string, list_operators[i].long_name))
            priority = list_operators[i].priority;
    }

    return priority;
}