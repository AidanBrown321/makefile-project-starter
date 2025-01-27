#include "lab.h"
#include <stdlib.h>


// Function to create a new list
list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }

// Making sentinel node
node_t *sentinel = (node_t *)malloc(sizeof(node_t));
    if (sentinel == NULL) {
        free(list);
        return NULL;
    }
    sentinel->data = NULL;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;

    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;
    list->head = sentinel;
    return list; 
}

// Function to destroy the list
void list_destroy(list_t **list) {
    if (list == NULL || *list == NULL) {
        return;
    }
    node_t *current = (*list)->head->next;
    while (current != (*list)->head) {
        node_t *next = current->next;
        if ((*list)->destroy_data) { 
            (*list)->destroy_data(current->data);
        }
        free(current);
        current = next;
    }
    free((*list)->head);
    free(*list);
    *list = NULL;
}

// Function to add data to the front of the list
list_t *list_add(list_t *list, void *data) {
    if (list == NULL) {
        return NULL;
    }

    

    // Create a new node
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return NULL;
    }

    // Set the data and point to the current head
    new_node->data = data;

    if (list->size == 0) {
        // Setting the new node
        new_node->next = list->head; //Point to sentinel
        new_node->prev = list->head; //Point to sentinel

        // Setting the sentinel
        list->head->prev = new_node;
    } else {
        // Setting the new node
        new_node->next = list->head->next; //Point to first node
        new_node->prev = list->head; //Point to sentinel

        // Setting the first node
        list->head->next->prev = new_node;

    }

    // Setting the Sentinel
    list->head->next = new_node;

    list->size++;

    return list;
}

// Function to remove data at the specified index
void *list_remove_index(list_t *list, size_t index) {
    if (list == NULL || index >= list->size || list->size == 0) {
        return NULL;
    }

    node_t *current = list->head->next;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    if(current == list->head) {
        return NULL;
    }

    if (current == list->head->next) {
        list->head->next->next->prev = list->head;
        list->head->next = list->head->next->next;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    void *data = current->data;
    free(current);
    list->size--;

    return data;
}

// Function to search for any occurrence of data in the list
int list_indexof(list_t *list, void *data) {
    if (list == NULL) {
        return -1;
    }

    node_t *current = list->head->next;
    size_t index = 0;
    while (index < list->size) {
        if (list->compare_to(current->data, data) == 0) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1;
}
