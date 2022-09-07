//
// Created by Nana Daughterless on 6/28/22.
//

#include "conversion.h"

int char_to_priority_operator(char symbol) {
    /// Converts a character to operator priority
    int priority = 0;

    for (int i = 0; !priority && get_list_operators()[i].short_name; i++) {
        if (symbol == get_list_operators()[i].short_name)
            priority = get_list_operators()[i].priority;
    }

    return priority;
}
