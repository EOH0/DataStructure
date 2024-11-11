#include <stdio.h>
#include <stdlib.h>

#define IS_EMPTY(first)(!(first))

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
};

void insert(listPointer *first, int data);
void printList(listPointer first);

int main() {
    FILE* file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }
    int num;

    listPointer first = (listPointer)malloc(sizeof(listPointer));
    first = NULL;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, num);
    }
    fclose(file);

    printList(first);
}

void insert(listPointer *first, int data) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer));
    
    temp->data = data;
    if (*first != NULL) {
        temp->link = *first;
        *first = temp;
    }
    else {
        temp->link = NULL;
        *first = temp;
    }
}
void printList(listPointer first) {
    listPointer trail = first;
    while(trail->link != NULL) {
        printf("%d ", trail->data);
        trail = trail->link;
    }
    printf("%d ", trail->data);
}