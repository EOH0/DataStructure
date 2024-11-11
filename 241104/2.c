#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

treePointer createNode(char data);
int countNodes(treePointer root);

int main() {
    treePointer root = createNode('A');

    // root->leftChild = createNode('B');
    // root->rightChild = createNode('C');
    // root->leftChild->leftChild = createNode('D');
    // root->leftChild->rightChild = createNode('E');
    // root->rightChild->leftChild = createNode('F');
    // root->rightChild->rightChild = createNode('G');
    // root->leftChild->leftChild->leftChild = createNode('H');
    // root->leftChild->leftChild->rightChild = createNode('I');
    
    root->leftChild = createNode('B');
    root->leftChild->leftChild = createNode('C');
    root->leftChild->leftChild->leftChild = createNode('D');
    root->leftChild->leftChild->leftChild->leftChild = createNode('E');

    int nodes = countNodes(root);
    printf("nodes = %d", nodes);
}

treePointer createNode(char data) {
    treePointer newnode = (treePointer)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;
    return newnode;
}
int countNodes(treePointer root) {
    if (root == NULL) {
        return 0;
    }
    return countNodes(root->leftChild) + countNodes(root->rightChild) + 1;
}