#include <stdio.h>
#include <stdlib.h>

#define MALLOC(ptr, size)                              \
    do {                                               \
        (ptr) = malloc(size);                          \
        if ((ptr) == NULL) {                           \
            fprintf(stderr, "메모리 할당 실패\n");    \
            exit(EXIT_FAILURE);                        \
        }                                              \
    } while (0)
    
int check = 0;

typedef struct node *treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

treePointer newNode(int data);
void cntnull(treePointer ptr, int *nullC);

int main() {
    treePointer root = newNode(4);
    root->leftChild = newNode(3);
    root->rightChild = newNode(6);
    root->leftChild->leftChild = newNode(2);
    root->leftChild->rightChild = newNode(5);
    root->rightChild->rightChild = newNode(8);

    int nullC = 0;
    cntnull(root, &nullC); // 주솟값을 넘겨서 변수를 직접 수정할 수 있게 함

    int leaf = nullC / 2; // LeafNode(말단 노드)는 항상 NULL인 노드의 1/2배이므로 반으로 나눠줌

    printf("%d", leaf);
}
treePointer newNode(int data) {
    treePointer node;
    MALLOC(node, sizeof(*node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;

    return node;
}
void cntnull(treePointer ptr, int *nullC) { // 트리를 재귀로 돌면서 ptr이 NULL이면 else로 하나 추가함
    if (ptr) {
        cntnull(ptr->leftChild, nullC);
        cntnull(ptr->rightChild, nullC);
    }
    else {
        (*nullC) += 1;
    }
}