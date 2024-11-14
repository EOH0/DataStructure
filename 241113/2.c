#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree{
    int key;
    treePointer leftChild, rightChild;
};

void inorder(treePointer ptr);
treePointer modifiedSearch(treePointer node, int k);
void insert(treePointer* node, int k);
void delete(treePointer node, int k);
treePointer findMax(treePointer root);
treePointer DupSearch(treePointer node, int k);

int main() {
    // FILE* file = fopen("in3.txt", "r");
    FILE* file = fopen("in4.txt", "r");
    if (file == NULL) {
        printf("file error");
        return 1;
    }

    int size = 0;
    int num;
    treePointer root = NULL;

    fscanf(file, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        insert(&root, num);
    }
    
    fscanf(file, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        delete(root, num);
    }

    fclose(file);

    inorder(root);
}

void delete(treePointer node, int k) {
    treePointer ptr = DupSearch(node, k);
    if (ptr == NULL) {
        printf("E ");
        return;
    } else {
        printf("S ");
        treePointer temp = ptr;
        treePointer LChild = temp->leftChild;
        treePointer RChild = temp->rightChild;
        
        if (LChild == NULL && RChild == NULL) {
            free(temp);

        } else if (LChild == NULL) {
            ptr->key = RChild->key;
            ptr->leftChild = RChild->leftChild;
            ptr->rightChild = RChild->rightChild;

            free(RChild);

        } else if (RChild == NULL) {
            ptr->key = LChild->key;
            ptr->leftChild = LChild->leftChild;
            ptr->rightChild = LChild->rightChild;

            free(LChild);

        } else {
            treePointer maxNode = LChild;
            treePointer maxParent = ptr;
            
            while (maxNode->rightChild != NULL) {
                maxParent = maxNode;
                maxNode = maxNode->rightChild;
            }
            
            ptr->key = maxNode->key;
            
            if (maxParent->rightChild == maxNode) {
                maxParent->rightChild = maxNode->leftChild;
            } else {
                maxParent->leftChild = maxNode->leftChild;
            }
            
            free(maxNode);
        }
    }
}
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->key);
        inorder(ptr->rightChild);
    }
}
treePointer DupSearch(treePointer node, int k) {
    treePointer now = NULL;
    while(node != NULL) {
        now = node;
        if (k == node->key) {
            return now;
        }
        else if (k < node->key) {
            node = node->leftChild;
        }
        else {
            node = node->rightChild;
        }
    }
    return NULL;
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