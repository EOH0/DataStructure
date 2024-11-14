#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree{
    int key;
    treePointer leftChild, rightChild;
};

int check = 0;

treePointer newNode(int key);
void inorder(treePointer ptr);
treePointer modifiedSearch(treePointer node, int k);
void insert(treePointer* node, int k);
treePointer findMax(treePointer root);

int main() {
    // FILE* file = fopen("in1.txt", "r");
    FILE* file = fopen("in2.txt", "r");
    if (file == NULL) {
        printf("file error");
        return 1;
    }

    int size = 0;
    fscanf(file, "%d", &size);

    int num;
    treePointer root = NULL;
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        insert(&root, num);
    }
    fclose(file);
    inorder(root); printf("\n");

    treePointer max = findMax(root);
    printf("%d", max->key);
}

treePointer findMax(treePointer root) {
    if (root) {
        findMax(root->rightChild);
    }

    return root;
}
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->key);
        inorder(ptr->rightChild);
    }
}
treePointer modifiedSearch(treePointer node, int k) {
    treePointer now = NULL;
    while(node != NULL) {
        now = node;
        if (k == node->key) {
            return NULL;
        }
        else if (k < node->key) {
            node = node->leftChild;
        }
        else {
            node = node->rightChild;
        }
    }
    return now;
}
void insert(treePointer* node, int k) {
    treePointer ptr, temp = modifiedSearch(*node, k);
    if (temp || !(*node)) {
        ptr = (treePointer)malloc(sizeof(struct tree));
        ptr->key = k;
        ptr->leftChild = ptr->rightChild = NULL;
        
        if (*node) {
            if (k < temp->key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        else {
            *node = ptr;
        }
    }
}