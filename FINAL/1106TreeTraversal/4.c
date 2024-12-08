#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct tree* treePointer;
typedef struct tree {
    char key;
    treePointer llink;
    treePointer rlink;
} tree;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer createnode(char key);
void iterInOrder(treePointer root);
void push(treePointer root);
treePointer pop();

int main() {
    treePointer root = createnode('+');
    root->llink = createnode('*');
    root->rlink = createnode('E');
    root->llink->llink = createnode('*');
    root->llink->rlink = createnode('D');
    root->llink->llink->llink = createnode('/');
    root->llink->llink->rlink = createnode('C');
    root->llink->llink->llink->llink = createnode('A');
    root->llink->llink->llink->rlink = createnode('B');

    iterInOrder(root);
}

treePointer createnode(char key) {
    treePointer newnode = (treePointer)malloc(sizeof(tree));
    newnode->key = key;
    newnode->llink = NULL;
    newnode->rlink = NULL;

    return newnode;
}
void iterInOrder(treePointer root) {
    for (;;) {
        for (; root; root = root->llink) {
            push(root);
        }

        root = pop();
        if (root == NULL) {
            break;
        }
        printf("%c ", root->key);
        root = root->rlink;
    }
}
void push(treePointer root) {
    if (top == MAX_STACK_SIZE - 1) {
        printf("stack full\n");
        return ;
    }
    stack[++top] = root;
}
treePointer pop() {
    if (top == -1) {
        return NULL;
    }
    return stack[top--];
}