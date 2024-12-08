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

    nodePointer head = (nodePointer)malloc(sizeof(node)); // doubly linked list
    // 자기자신을 링크함
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
    nodePointer now = header->rlink; // 노드가 들어갈 위치는 header의 오른쪽
    while (now != header && now->data.key < newnode->data.key) { // 작은 수부터 큰수로 삽입
    // now가 header가 아닌 동안 (초기 상태가 아니면) && 새로 들어갈 노드의 key가 들어갈 자리의 key보다 크면(오름차순으로 정렬되야하므로 큰 수가 뒤에 가야됨)
        now = now->rlink; // 계속 다음 노드로 넘김
    }
    newnode->llink = now->llink; // header와 now의 사이에 들어감 (header의 rlink, now의 llink)
    newnode->rlink = now;
    now->llink->rlink = newnode;
    now->llink = newnode;
}

void printIncrease(nodePointer header) { // header의 rlink부터해서 큰수부터 출력되도록 (저장이 llink부터 작은 수로 되어있기 때문) 오름차순
    nodePointer temp = header->rlink;
    while (temp != header) {
        printf("%d ", temp->data.key);
        temp = temp->rlink;
    }
    printf("\n");
}

void printDecrease(nodePointer header) { // header의 llink에서부터 작은 수부터 출력되도록 내림차순
    nodePointer temp = header->llink;
    while (temp != header) {
        printf("%d ", temp->data.key);
        temp = temp->llink;
    }
    printf("\n");
}