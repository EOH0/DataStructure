#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree {
    int key;
    treePointer llink;
    treePointer rlink;
} tree;

treePointer createnode(int key);
void inorder(treePointer root);
treePointer copy(treePointer root);
int equal(treePointer first, treePointer second);

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