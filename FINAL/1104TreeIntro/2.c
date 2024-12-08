#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree {
    char key;
    treePointer llink, rlink;
} tree;

treePointer createNode(char key);
int countNode(treePointer root);

int main() {
    treePointer root = createNode('A');
    root->llink = createNode('B');
    root->rlink = createNode('C');
    root->llink->llink = createNode('D');
    root->llink->rlink = createNode('E');
    root->rlink->llink = createNode('F');
    root->rlink->rlink = createNode('G');
    root->llink->llink->llink = createNode('H');
    root->llink->llink->rlink = createNode('I');

    int size = 9;

    int cnt = countNode(root);
    printf("%d\n", cnt);
}

int countNode(treePointer root) {
    if (root == NULL) {
        return 0;
    }
    return countNode(root->llink) + countNode(root->rlink) + 1;
}
treePointer createNode(char key) {
    treePointer newnode = (treePointer)malloc(sizeof(tree));
    newnode->key = key;
    newnode->llink = NULL;
    newnode->rlink = NULL;
    return newnode;
}