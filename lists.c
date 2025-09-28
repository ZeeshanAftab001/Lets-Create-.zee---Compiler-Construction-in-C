#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT,
    FLOAT,
    CHAR,
} Dtypes;

typedef struct {
    Dtypes type;
    void *data;
    size_t size;
} Item;

typedef struct Node {
    Item item;
    struct Node *next;
} Node;

/* ====== ITEM FACTORIES ====== */
Item make_int(int x) {
    Item it;
    it.type = INT;
    it.size = sizeof(int);
    it.data = malloc(it.size);
    memcpy(it.data, &x, it.size);
    return it;
}

Item make_float(float f) {
    Item it;
    it.type = FLOAT;
    it.size = sizeof(float);
    it.data = malloc(it.size);
    memcpy(it.data, &f, it.size);
    return it;
}

Item make_char(char c) {
    Item it;
    it.type = CHAR;
    it.size = sizeof(char);
    it.data = malloc(it.size);
    memcpy(it.data, &c, it.size);
    return it;
}

/* ====== LINKED LIST ====== */
Node *create(Item data) {
    Node *curr = (Node *) malloc(sizeof(Node));
    if (!curr) { perror("malloc"); exit(1); }

    curr->next = NULL;
    curr->item = data; // copy struct (shallow, but ok here)
    return curr;
}

void append(Node **first, Item data) {
    Node *curr = create(data);
    if (!*first) {
        *first = curr;
    } else {
        Node *temp = *first;
        while (temp->next) temp = temp->next;
        temp->next = curr;
    }
}

void display(Node *first) {
    Node *curr = first;
    while (curr) {
        switch (curr->item.type) {
            case INT:
                printf("INT: %d\n", *(int*) curr->item.data);
                break;
            case FLOAT:
                printf("FLOAT: %f\n", *(float*) curr->item.data);
                break;
            case CHAR:
                printf("CHAR: %c\n", *(char*) curr->item.data);
                break;
        }
        curr = curr->next;
    }
}

void free_list(Node *first) {
    Node *curr = first;
    while (curr) {
        Node *next = curr->next;
        free(curr->item.data);
        free(curr);
        curr = next;
    }
}

/* ====== DEMO ====== */
int main() {
    Node *list = NULL;

    append(&list, make_int(42));
    append(&list, make_float(3.14f));
    append(&list, make_char('Z'));

    display(list);
    free_list(list);
    return 0;
}
