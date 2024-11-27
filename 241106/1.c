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
    inorder(root); // root(트리의 가장 최상위 노드)에서 inorder 탐색 시작
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
void inorder(treePointer ptr) { // inorder는 왼쪽 서브트리 -> 루트 -> 오른쪽 서브트리 순서로 방문
    if (ptr) { // 현재 노드 ptr이 NULL이 아니면
        inorder(ptr->leftChild); // 왼쪽 서브트리 방문 (왼쪽 서브트리가 왼쪽 자식을 가지면 다시 inorder 실행 => 재귀)
        printf("%d ", ptr->data); // 왼쪽 서브트리를 모두 방문한 후 현재 노드의 data 출력
        inorder(ptr->rightChild); // 그리고 오른쪽 서브트리 방문
    }
}
treePointer copy(treePointer original) {
    treePointer temp = (treePointer)malloc(sizeof(treePointer)); // copy할 노드를 저장함
    if (original) {
        temp->leftChild = copy(original->leftChild); // 왼쪽 서브트리르 다 돌고
        temp->data = original->data; // 재귀 당시의 루트를 복사함
        temp->rightChild = copy(original->rightChild); // 오른쪽 서브트리를 다 돌면서 복사를 다 하면
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