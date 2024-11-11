#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node{
    int data;
    nodePointer link;
} node;

void insert(nodePointer *first, int data);
void printList(nodePointer first);

int main() {
    FILE* file = fopen("link.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    nodePointer first = (nodePointer)malloc(sizeof(node));
    first->link = NULL;

    int data = 0;
    while(fscanf(file, "%d", &data) != EOF) {
        insert(&first, data);
    }

    printList(first);
}

void insert(nodePointer *first, int data) {
    nodePointer trail = (nodePointer)malloc(sizeof(node));
    trail->data = data;
    trail->link = NULL;

    if (*first == NULL) {
        *first = trail;
    }
    else {
        while(trail->link != NULL) {
            trail = trail->link;
        }
        trail->link = *first;
        *first = trail;
    }
}
void printList(nodePointer first) {
    nodePointer trail = first;

    while(trail->link != NULL) {
        printf("%d ", trail->data);
        trail = trail->link;
    }
}