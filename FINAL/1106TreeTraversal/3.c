#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct tree* treePointer;
typedef struct tree {
    int key;
    treePointer llink;
    treePointer rlink;
} tree;

treePointer queue[MAX_QUEUE_SIZE];
int front, rear;

treePointer createnode(int key);
void inorder(treePointer root);
treePointer copy(treePointer root);
int equal(treePointer first, treePointer second);
int countLeaf(treePointer root);
void levelorder(treePointer root);
void addq(treePointer root);
treePointer deleteq();

int main() {
    treePointer root = createnode(4);
    root->llink = createnode(3);
    root->rlink = createnode(6);
    root->rlink->rlink = createnode(8);
    root->llink->llink = createnode(2);
    root->llink->rlink = createnode(5);

    inorder(root);
    printf("\n");

    treePointer copied = copy(root);

    inorder(copied);
    printf("\n");

    int eq = equal(root, copied);
    printf("%d\n", eq);

    int leaf = countLeaf(root);
    printf("%d\n", leaf);

    levelorder(root);
}

treePointer createnode(int key) {
    treePointer newnode = (treePointer)malloc(sizeof(tree));
    newnode->key = key;
    newnode->llink = NULL;
    newnode->rlink = NULL;
    return newnode;
}
void inorder(treePointer root) {
    if (root != NULL) {
        inorder(root->llink);
        printf("%d ", root->key);
        inorder(root->rlink);
    }
}
treePointer copy(treePointer root) {
    treePointer temp = (treePointer)malloc(sizeof(tree));
    if (root != NULL) {
        temp->llink = copy(root->llink);
        temp->key = root->key;
        temp->rlink = copy(root->rlink);
        return temp;
    }
    return NULL;
}
int equal(treePointer first, treePointer second) {
    int eq = ((!first && !second) || (first && second && first->key == second->key)
    && equal(first->llink, second->llink) && equal(first->rlink, second->rlink));

    return eq;
}
int countLeaf(treePointer root) {
    if (root != NULL) {
        if (root->llink == NULL && root->rlink == NULL) {
            return countLeaf(root->llink) + countLeaf(root->rlink) + 1;
        }
        return countLeaf(root->llink) + countLeaf(root->rlink);
    }
    return 0;
}
void levelorder(treePointer root) {
    front = rear = 0;

    if (root == NULL) {
        return ;
    }
    addq(root);

    for (;;) {
        root = deleteq();
        if (root) {
            printf("%d ", root->key);
            if (root->llink != NULL) {
                addq(root->llink);
            }
            if (root->rlink != NULL) {
                addq(root->rlink);
            }
        }
        else {
            break;
        }
    }
}
void addq(treePointer root) {
    if (rear + 1 == front) {
        printf("queue full");
        return ;
    }
    queue[++rear] = root;
}
treePointer deleteq() {
    if (front == rear) {
        return NULL;
    }
    return queue[++front];
}