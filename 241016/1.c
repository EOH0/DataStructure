#include <stdio.h>
#include <stdlib.h>

#define IS_EMPTY(first)(!(first))

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
};

void insert(listPointer *first, int data, listPointer *trail);
void printList(listPointer first);

int main() {
    FILE* file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }
    int num;

    listPointer first = (listPointer)malloc(sizeof(listPointer));
    listPointer trail = (listPointer)malloc(sizeof(listPointer)); // 진행 상황 저장할 trail
    first = NULL;
    trail = first;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, num, &trail);
    }
    fclose(file);

    printList(first);
}

void insert(listPointer *first, int data, listPointer *trail) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer));
    temp->data = data;
    if (*first == NULL) {
        temp->link = NULL;
        *first = temp;
        *trail = *first;
    }
    else {
        temp->link = NULL;
        (*trail)->link = temp;
        *trail = temp;
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