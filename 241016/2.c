#include <stdio.h>
#include <stdlib.h>

#define IS_EMPTY(first)(!(first))

typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
};

void insert(listPointer *first, int data, listPointer *trail);
void printList(listPointer first);
void delete(listPointer *first, listPointer trail, listPointer x);

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

    //-------------

    while (1) {
        int input;
        scanf("%d", &input);
        if (input == -1) {
            break;
        }
        listPointer x = (listPointer)malloc(sizeof(listPointer)); // 삭제하고자하는 값의 노드 (삭제될 노드)
        x = first;
        trail = NULL; // 삭제하고자하는 값의 이전 노드

        while (x != NULL && x->data != input) {  // 삭제할 값 찾기 (x가 첫번째 값이 아니고, x의 data가 삭제할 값이 아닐 때)
            trail = x;
            x = x->link;
        }
        if (x != NULL) {  // 삭제할 노드가 존재할 경우
            delete(&first, trail, x);
            printList(first);
        }
    }

    free(first);
    free(trail);
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
    printf("\n");
}
void delete(listPointer *first, listPointer trail, listPointer x) {
    if (trail) {
        trail->link = x->link;
    }
    else {
        *first = (*first)->link;
    }
    free(x);
}
