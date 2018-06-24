#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct node {
    void *data;
    struct node *next;
} llist_t;

bool contains(llist_t *head_ref, void * const obj, bool (*equals)(const void *, const void *));
void print_list(llist_t *head_ref, void (*fptr)(const void *));
bool is_empty(llist_t *head_ref);
void push(llist_t **head_ref, void *new_data, size_t data_size);
void destroy(llist_t **head_ref);

#endif /* LINKED_LIST_H */
