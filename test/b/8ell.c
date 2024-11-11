#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
    int data;
    listPointer link;
};

void insert(listPointer *first, int num, listPointer* trail);
void append(listPointer *first, int input, listPointer* trail);
void printList(listPointer *first, listPointer* trail);

int main() {
    FILE* file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return -1;
    }

    listPointer first = (listPointer)malloc(sizeof(listPointer));
    listPointer trail = (listPointer)malloc(sizeof(listPointer));
    first = NULL;
    trail = first;
    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, num, &trail);
    }

    printList(&first, &trail);

    int input = 0;
    while(1) {
        scanf("%d", &input);
        if (input == -1) {
            break;
        }
        append(&first, input, &trail);
        printList(&first, &trail);
    }
}

void insert(listPointer *first, int num, listPointer* trail) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer));
    temp->data = num;
    temp->link = NULL;
    if (*first == NULL) {
        *first = temp;
        *trail = temp;
    }
    else {
        (*trail)->link = temp;
        (*trail) = temp;
    }
}
void append(listPointer *first, int input, listPointer* trail) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer));
    listPointer prev = (listPointer)malloc(sizeof(listPointer));
    listPointer now = (listPointer)malloc(sizeof(listPointer));

    now = *first;
    prev = NULL;
    temp->data = input;
    temp->link = NULL;
    trail = first;
    
    if (now == NULL || now->data > input) { // now가 첫번째이거나 input이 가장 작을때
        temp->link = now;
        *first = temp;
    }
    else {
        while (now != NULL && now->data < input) {
            prev = now;
            now = now->link;
        }
        temp->link = now;
        prev->link = temp;
    }
}
void printList(listPointer *first, listPointer* trail) {
    *trail = *first;
    while(*trail != NULL) {
        printf("%d ", (*trail)->data);
        *trail = (*trail)->link;
    }
    printf("\n");
}