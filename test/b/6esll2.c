#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} node;

void insertnode(nodePointer *first, nodePointer *trail, int data);
void printnode(nodePointer first);
void delete(nodePointer *first, nodePointer trail, nodePointer x);

int main() {
    FILE* file = fopen("link.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    nodePointer first = (nodePointer)malloc(sizeof(node));
    nodePointer trail = (nodePointer)malloc(sizeof(node));
    first = NULL;
    trail = first;

    int data;
    while(fscanf(file, "%d", &data) != EOF) {
        insertnode(&first, &trail, data);
    }

    int num = 0;
    nodePointer x = (nodePointer)malloc(sizeof(node));
    while (num != -1) {
        printnode(first);
        scanf("%d", &num);
        x->data = num;
        delete(&first, trail, x);
    }
}

void insertnode(nodePointer *first, nodePointer *trail, int data) {
    nodePointer temp = (nodePointer)malloc(sizeof(node));
    temp->data = data;
    temp->link = NULL;
    
    if (*first == NULL) {
        *first = temp;
        *trail = *first;
    }
    else {
        while ((*trail)->link != NULL) {
            *trail = (*trail)->link;
        }
        (*trail)->link = temp;
        temp = *trail;
    }
}
void printnode(nodePointer first) {
    nodePointer trail = (nodePointer)malloc(sizeof(node));
    trail = first;
    while(trail != NULL) {
        printf("%d ", trail->data);
        trail = trail->link;
    }
    printf("\n");
}
void delete(nodePointer *first, nodePointer trail, nodePointer x) {
    trail = *first;
    nodePointer prev = NULL;

    while(trail != NULL) { // 반복 조건
        if (trail->data == x->data) {
            if (prev == NULL) { // 초기 값 고려
                *first = trail->link;
            }
            else {
                prev->link = trail->link;
            }
            free(trail);
            return ; // 삭제하면 탐색 종료
        }
        prev = trail;
        trail = trail->link;
    }
}
