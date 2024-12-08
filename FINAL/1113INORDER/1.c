#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree {
    int key;
    treePointer llink;
    treePointer rlink;
} tree;

void insert(treePointer *root, int key);
treePointer modifiedSearch(treePointer root, int key);
void inorder(treePointer root);
treePointer findMax(treePointer root);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);
    int num;
    treePointer root = NULL;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&root, num);
    }

    inorder(root); printf("\n");

    treePointer max = findMax(root);
    printf("%d", max->key);
}
void insert(treePointer *root, int key) {
    treePointer ptr;
    treePointer temp = modifiedSearch(*root, key);

    if (temp != NULL || *root == NULL) {
        ptr = (treePointer)malloc(sizeof(tree)); // ptr 구성
        ptr->key = key;
        ptr->llink = NULL;
        ptr->rlink = NULL;

        if (*root == NULL) { // 맨 처음에 root가 빈 상태면 ptr을 바로 root에 
            *root = ptr;
        }
        else { // root가 비어있지 않다면 key의 대소를 비교해서 왼쪽이나 오른쪽 중에 넣음
        // 어차피 temp는 단말노드라 왼쪽 오른쪽 중 아무데나 넣으면 됨
            if (key > temp->key) {
                temp->rlink = ptr;
            }
            else {
                temp->llink = ptr;
            }
        }
    }
}
treePointer modifiedSearch(treePointer root, int key) {
    treePointer now = NULL;
    while(root != NULL) {
        now = root;
        if (root->key == key) {
            return NULL;
        }
        else if (root->key < key) { // 새로 들어온 값이 현재 노드의 값보다 크면
            root = root->rlink; // 현재 노드의 값보다 큰 값이 모여있는 오른쪽으로 보내줌
        }
        else { // 작으면
            root = root->llink; // 작은 값이 모여있는 왼쪽으로 보내줌
        }
    }

    return now;
}
void inorder(treePointer root) {
    if (root != NULL) {
        inorder(root->llink);
        printf("%d ", root->key);
        inorder(root->rlink);
    }
}
treePointer findMax(treePointer root) {
    treePointer max = root;
    while(max->rlink != NULL) {
        max = max->rlink;
    }

    return max;
}