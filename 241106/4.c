#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer newNode(char data);
void push(treePointer node);
treePointer pop();
void iterInorder(treePointer node);

int main() {
    treePointer root = newNode('+');
    root->leftChild = newNode('*');
    root->rightChild = newNode('E');
    root->leftChild->leftChild = newNode('*');
    root->leftChild->rightChild = newNode('D');
    root->leftChild->leftChild->leftChild = newNode('/');
    root->leftChild->leftChild->rightChild = newNode('C');
    root->leftChild->leftChild->leftChild->leftChild = newNode('A');
    root->leftChild->leftChild->leftChild->rightChild = newNode('B');

    printf("LVR : ");
    iterInorder(root);
}

treePointer newNode(char data) {
    treePointer node = (treePointer)malloc(sizeof(struct node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}
void iterInorder(treePointer node) {
    // iterInorder는 inorder와 탐색하는 순서는 같지만 방법에 차이가 있음
    // iterInorder: 반복문과 스택을 사용
    // Inorder: 재귀 사용

    // 반복문 내에서 break가 걸릴때까지 무한 반복
    for (;;) {
        for(; node; node = node->leftChild) { // node의 왼쪽 자식이 NULL일때까지(왼쪽 서브트리의 끝까지) 이동
            push(node); // 스택에 노드 push
        } // 이 시점에 각 level의 가장 왼쪽 노드는 스택에 존재함

        node = pop(); // 스택에서 pop한 노드를 node에 저장
        if (!node) break; // node가 NULL이면 반복 종료
        printf("%c ", node->data);
        node = node->rightChild;
        // 오른쪽 자식이 있으면 그냥 pop하고 출력됨
        // 없으면 노드는 스택에서 가장 위에 있는 값을 pop하여 가져옴
    }
}
void push(treePointer node) {
    if (top == MAX_STACK_SIZE - 1) {
        printf("stack full");
        return ;
    }
    stack[++top] = node;
}
treePointer pop() {
    if (top == -1) {
        return NULL;
    }
    return stack[top--];
}