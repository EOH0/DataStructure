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
    for (;;) {
        for(; node; node = node->leftChild) {
            push(node);
        }
        node = pop();
        if (!node) break;
        printf("%c ", node->data);
        node = node->rightChild;
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