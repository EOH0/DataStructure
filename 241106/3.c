#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

treePointer queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

treePointer newNode(int data);
void inorder(treePointer ptr);
void addq(treePointer item);
treePointer deleteq();
void levelOrder(treePointer ptr);

int main() {
    treePointer root = newNode(4);
    root->leftChild = newNode(3);
    root->rightChild = newNode(6);
    root->leftChild->leftChild = newNode(2);
    root->leftChild->rightChild = newNode(5);
    root->rightChild->rightChild = newNode(8);

    levelOrder(root);
}
treePointer newNode(int data) {
    treePointer node = (treePointer)malloc(sizeof(struct node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}
void levelOrder(treePointer ptr) {
    front = 0;
    rear = 0;
    if (!ptr) return;
    addq(ptr);  
    for(;;) {
        ptr = deleteq();
        if (ptr) {
            printf("%d ", ptr->data);
            if (ptr->leftChild) {
                addq(ptr->leftChild);
            }
            if (ptr->rightChild) {
                addq(ptr->rightChild);
            }
        }
        else {
            break;
        }
    }
}
void addq(treePointer ptr) {
    if (rear == MAX_QUEUE_SIZE - 1) {
        printf("Queue is full\n");
        return;
    }
    queue[++rear] = ptr;
}

treePointer deleteq() {
    if (front == rear) {
        return NULL;
    }
    return queue[++front];
}