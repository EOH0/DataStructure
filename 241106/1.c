#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

treePointer newNode(int data);
void inorder(treePointer ptr);
treePointer copy(treePointer original);
int equal(treePointer first, treePointer second);

int main() {
    treePointer root = newNode(4);
    root->leftChild = newNode(3);
    root->rightChild = newNode(6);
    root->leftChild->leftChild = newNode(2);
    root->leftChild->rightChild = newNode(5);
    root->rightChild->rightChild = newNode(8);

    printf("original inorder : ");
    inorder(root);
    printf("\n");

    treePointer copied = copy(root);
    if (copied) {
        printf("copy finished!\n");
    }
    else {
        printf("copy failed\n");
    }

    int eq = equal(root, copied);
    if (eq == 1) {
        printf("equal test success!\n");
    }
    else {
        printf("equal test failed\n");
    }

    printf("copied inorder : ");
    inorder(copied);
    printf("\n");

}
treePointer newNode(int data) {
    treePointer node = (treePointer)malloc(sizeof(struct node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data);
        inorder(ptr->rightChild);
    }
}
treePointer copy(treePointer original) {
    treePointer temp = (treePointer)malloc(sizeof(treePointer));
    if (original) {
        temp->leftChild = copy(original->leftChild);
        temp->rightChild = copy(original->rightChild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}
int equal(treePointer first, treePointer second) {
    int eq = ((!first && !second)
    || (first && second && first->data == second->data)
    && equal(first->leftChild, second->leftChild)
    && equal(first->rightChild, second->rightChild));
    
    return eq;
}