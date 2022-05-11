//
// Created by Nana Daughterless on 5/7/22.
//

#include "linked_list.h"
#include <stdlib.h>

linked_list_t *linked_list(void *data) {
    linked_list_t *new_list = calloc(1, sizeof(linked_list_t));
    if (new_list) {
        new_list->data = data;
        new_list->next_item = NULL;
        new_list->was = 1;
    }
    return new_list;
}

void add_to_linked_list(linked_list_t *list, void *data) {
    while (list->next_item) {
        list = list->next_item;
    }
    list->next_item = linked_list(data);
}

void free_linked_list(linked_list_t *list) {
    linked_list_t *tmp;
    while (list) {
        if (list->data) {
            free(list->data);
        }
        tmp = list->next_item;
        free(list);
        list = tmp;
    }
}

linked_list_t *get_from_linked_list(linked_list_t *list, int index) {
    while (index > 0 && list) {
        list = list->next_item;
        index--;
    }
    return list;
}

short is_empty_linked_list(linked_list_t *list) {
    return !list->next_item && !list->data;
}

void *shift_linked_list(linked_list_t *list) {
    linked_list_t *tmp = list->next_item;
    void *tmp_data = NULL;

    if (tmp) {
        tmp_data = tmp->data;
        list->next_item = tmp->next_item;
        free(tmp);
    }

    return tmp_data;
}