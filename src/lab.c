#include "lab.h"
#include <stdlib.h>

// Define the list node structure
typedef struct list_node {
    void *data;
    struct list_node *next;
    struct list_node *prev;
} list_node_t;

// Define the list structure
struct list_t {
    void (*destroy_data)(void *);
    int (*compare_to)(const void *, const void *);
    size_t size;
    list_node_t *head;
};

// Function to create a new list
list_t *list_init(void (*destroy_data)(void *), int (*compare_to)(const void *, const void *)) {
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }
    list->destroy_data = destroy_data;
    list->compare_to = compare_to;
    list->size = 0;
    list->head = NULL;
    return list; 
}

// Function to destroy the list
void list_destroy(list_t **list) {
    if (list == NULL || *list == NULL) {
        return;
    }
    list_node_t *current = (*list)->head;
    while (current != NULL) {
        list_node_t *next = current->next;
        if ((*list)->destroy_data) { 
            (*list)->destroy_data(current->data);
        }
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}

// Function to add data to the front of the list
list_t *list_add(list_t *list, void *data) {
    if (list == NULL) {
        return NULL;
    }

    

    // Create a new node
    list_node_t *new_node = (list_node_t *)malloc(sizeof(list_node_t));
    if (new_node == NULL) {
        return NULL;
    }

    // Set the data and point to the current head
    new_node->data = data;

    if (list->size == 0) {
        new_node->next = NULL;
        new_node->prev = NULL;
    } else {
        new_node->next = list->head;
        new_node->prev = list->head->prev;
    }

    // Update the head to the new node
    
    if (list->size == 1) {
        list->head->next = new_node;
        list->head->prev = new_node;
    } else if (list->size > 1) {
        list->head->prev = new_node;
    }

    list->head = new_node;
    list->size++;

    return list;
}

// Function to remove data at the specified index
void *list_remove_index(list_t *list, size_t index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }

    list_node_t *current = list->head;
    list_node_t *previous = NULL;
    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        list->head->next->prev = list->head->prev;
        list->head->prev->next = list->head->next;
        list->head = current->next;
    } else {
        previous->next = current->next;
        current->next->prev = previous;
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

    list_node_t *current = list->head;
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
