#include "lab.h"
#include <stdlib.h>

// Define the list node structure
typedef struct list_node {
    void *data;
    struct list_node *next;
} list_node_t;

// Define the list structure
struct list_t {
    list_node_t *head;
};

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
    new_node->next = list->head;

    // Update the head to the new node
    list->head = new_node;

    return list;
}
