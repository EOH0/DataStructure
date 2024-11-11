#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int key;
} element;

typedef struct node *nodePointer;
typedef struct node {
    nodePointer llink;
    element data;
    nodePointer rlink;
} node;

void dinsert(nodePointer node, nodePointer newnode);
void printIncrease(nodePointer header);
void printDecrease(nodePointer header);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    nodePointer head = (nodePointer)malloc(sizeof(node));
    head->llink = head;
    head->rlink = head;

    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        nodePointer newNode = (nodePointer)malloc(sizeof(node));
        newNode->data.key = num;
        dinsert(head, newNode);
    }
    fclose(file);
    
    printIncrease(head);

    printDecrease(head);

    // 메모리 해제
    nodePointer temp = head->rlink;
    while (temp != head) {
        nodePointer next = temp->rlink;
        free(temp);
        temp = next;
    }
    free(head);

    return 0;
}   
void dinsert(nodePointer header, nodePointer newnode) {
    // 새 노드를 현재 노드의 오른쪽에 삽입
    nodePointer now = header->rlink;
    while (now != header && now->data.key < newnode->data.key) {
        now = now->rlink;
    }
    newnode->llink = now->llink;
    newnode->rlink = now;
    now->llink->rlink = newnode;
    now->llink = newnode;
}

void printIncrease(nodePointer header) {
    nodePointer temp = header->rlink;
    while (temp != header) {
        printf("%d ", temp->data.key);
        temp = temp->rlink;
    }
    printf("\n");
}

void printDecrease(nodePointer header) {
    nodePointer temp = header->llink;
    while (temp != header) {
        printf("%d ", temp->data.key);
        temp = temp->llink;
    }
    printf("\n");
}