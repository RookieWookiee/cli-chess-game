#include <stdlib.h>
#include <stdint.h>

#include "include/llist.h"
#include "include/position.h"

void push(llist_t **head_ref, void *new_data, size_t data_size)
{
    llist_t *new_node = malloc(sizeof(llist_t));

    new_node->data = malloc(data_size);
    new_node->next = (*head_ref);

    for(size_t i = 0; i < data_size; i++) {
        *(uint8_t *)(new_node->data + i) = *(uint8_t *)(new_data + i);
    }

    (*head_ref) = new_node;
}

void print_list(llist_t *node, void (*fptr)(const void *))
{
    while(node != NULL) {
        (*fptr)(node->data);
        node = node->next;
    }
}

bool contains(llist_t *node, void *obj, bool (*equals)(const void*, const void*))
{
    while(node != NULL) {
        if(equals(obj, node->data))
            return true;
        node = node->next;
    }

    return false;
}

void destroy(llist_t **head_ref)
{
    while(*head_ref) {
        llist_t *next = (*head_ref)->next;
        free((*head_ref)->data);
        free((*head_ref));
        (*head_ref) = next;
    }
    (*head_ref) = NULL;
}

bool is_empty(llist_t *head_ref)
{
    return head_ref == NULL;
}
