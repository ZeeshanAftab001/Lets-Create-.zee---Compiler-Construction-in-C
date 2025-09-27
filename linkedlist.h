#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

// Function to create a new node
static inline Node* create_node(const char *word) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->word = strdup(word);  // duplicate string
    newNode->next = NULL;
    return newNode;
}

static inline void append(Node **head, const char *word) {
    Node *newNode = create_node(word);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }
}

// Free the list
static inline void free_list(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

#endif // LINKLIST_H
