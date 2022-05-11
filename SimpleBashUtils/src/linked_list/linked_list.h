//
// Created by Nana Daughterless on 5/7/22.
//

#ifndef SIMPLEBASHUTILS_LINKED_LIST_H
#define SIMPLEBASHUTILS_LINKED_LIST_H

typedef struct linked_list {
    void *data;
    struct linked_list *next_item;
    int was;
} linked_list_t;

linked_list_t *linked_list(void *data);
void add_to_linked_list(linked_list_t *list, void *data);
void free_linked_list(linked_list_t *list);
linked_list_t *get_from_linked_list(linked_list_t *list, int index);
short is_empty_linked_list(linked_list_t *list);
void *shift_linked_list(linked_list_t *list);
#endif //SIMPLEBASHUTILS_LINKED_LIST_H
