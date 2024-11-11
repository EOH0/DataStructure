#include <stdio.h>
#include <stdlib.h>

int check = 0;

typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

treePointer newNode(int data);
void cntnull(treePointer ptr, int *nullC);

int main() {
    treePointer root = newNode(4);
    root->leftChild = newNode(3);
    root->rightChild = newNode(6);
    root->leftChild->leftChild = newNode(2);
    root->leftChild->rightChild = newNode(5);
    root->rightChild->rightChild = newNode(8);

    int nullC = 0;
    cntnull(root, &nullC);

    int leaf = nullC / 2;

    printf("%d", leaf);
}
treePointer newNode(int data) {
    treePointer node = (treePointer)malloc(sizeof(struct node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}
void cntnull(treePointer ptr, int *nullC) {
    if (ptr) {
        cntnull(ptr->leftChild, nullC);
        cntnull(ptr->rightChild, nullC);
    }
    else {
        (*nullC) += 1;
    }
}