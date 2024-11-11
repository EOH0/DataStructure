#include <stdio.h>
#include <stdlib.h>

int check = 0;

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;  
} listNode;

void insert(listPointer *first, listPointer *trail, int num);
void append(listPointer *first, listPointer *trail, int data);
void print(listPointer *first, listPointer *trail);

int main() {
    FILE* file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error.\n");
        return -1;
    }

    listPointer first = (listPointer)malloc(sizeof(listNode));
    listPointer trail = (listPointer)malloc(sizeof(listNode));
    
    first = NULL;
    trail = first;
    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, &trail, num);
    }
    print(&first, &trail);

    
    int input = 0;
    while(1) {
        scanf("%d", &input);
        if (input == -1) break;
        append(&first, &trail, input);
        print(&first, &trail);
    }
    print(&first, &trail);
}

void insert(listPointer *first, listPointer *trail, int num) {
    listPointer temp = (listPointer)malloc(sizeof(listNode));
    temp->data = num;
    temp->link = NULL;
    *trail = *first;
    if (*trail == NULL) {
        *first = temp;
        *trail = *first;
        (*trail)->link = NULL;
    }
    else {
        while((*trail)->link != NULL) {
            *trail = (*trail)->link;
        }
        (*trail)->link = temp;
        *trail = temp;
        (*trail)->link = NULL;
    }
}
void append(listPointer *first, listPointer *trail, int input) {
    listPointer temp = (listPointer)malloc(sizeof(listNode));
    listPointer now = *first;
    listPointer prev = NULL;
    
    *trail = *first;
    temp->data = input;
    temp->link = NULL;
    
    if (*trail == NULL || (*trail)->data > input) {
        *trail = temp;
        (*trail)->link = *first;
        *first = temp;
    }
    else {
        while((*trail)->data <= input) {
            prev = *trail;
            *trail = (*trail)->link;
        }
        prev->link = temp;
        temp->link = *trail;
        *trail = temp;
    }
}
void print(listPointer *first, listPointer *trail) {
    *trail = *first;
    while(*trail != NULL) {
        printf("%d ", (*trail)->data);
        *trail = (*trail)->link;
    }
    printf("\n");
}