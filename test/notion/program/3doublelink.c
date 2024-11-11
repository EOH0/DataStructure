#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

typedef struct node *nodePointer;
struct node {
    nodePointer rlink;
    element data;
    nodePointer llink;
};

void dinsert(nodePointer header, nodePointer newNode);

int main() {
    FILE* file = fopen("f3.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }
    nodePointer head = (nodePointer)malloc(sizeof(struct node));
    head->rlink = head;
    head->llink = head;

    int num = 0;
    while(fscanf(file, "%d",  &num) != EOF) {
        nodePointer newnode = (nodePointer)malloc(sizeof(struct node));
        newnode->data.key = num;
        dinsert(head, newnode);
    }

    nodePointer trail = head->rlink;
    while(trail != head) {
        printf("%d ", trail->data.key);
        trail = trail->rlink;
    }
    trail = head->llink;
    printf("\n");
    while (trail != head) {
        printf("%d ", trail->data.key);
        trail = trail->llink;
    }
}

void dinsert(nodePointer header, nodePointer newNode) {
    nodePointer now = header->rlink;
    while(now != header && now->data.key < newNode->data.key) {
        now = now->rlink;
    }
    newNode->llink = now;
    newNode->rlink = now->rlink;
    now->rlink->llink = newNode;
    now->rlink = newNode;
}