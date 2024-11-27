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
    // front, rear 초기화 
    front = 0;
    rear = 0;
    if (!ptr) return; // ptr이 NULL이다(트리가 없다) -> 리턴
    addq(ptr); // queue에 root 추가하고 시작
    
    // 무한 루프를 돌면서 큐에서 노드를 제거하고 레벨 순서대로 처리
    for(;;) {
        ptr = deleteq(); // 큐에서 노드 하나 제거 (제거된 노드가 ptr에 들어감으로써 queue에선 빠짐과 동시에 levelorder의 대상이 됨)
        if (ptr) {
            printf("%d ", ptr->data); // 노드 출력
            if (ptr->leftChild) {
                addq(ptr->leftChild); // 왼쪽 자식 큐에 추가
            }
            if (ptr->rightChild) {
                addq(ptr->rightChild); // 오른쪽 자식 큐에 추가
            }
        }
        else {
            break; // 큐가 비면 종료
        }
    }

    /*
        가장 처음 큐 : [ 4 ]
        ptr == 4 : [ 3, 6 ] (4의 두 자식인 3, 6 추가)
        ptr == 3 : [ 6, 2, 5 ] (3의 두 자식인 2, 5 추가)
        ptr == 6 : [ 2, 5, 8 ] (6의 오른쪽 자식인 8 추가)
        ptr == 2 : [ 5, 8 ] (2는 자식이 없으므로 추가될 요소가 없음)
        ptr == 5 : [ 8 ] (5도 자식이 없으므로 추가될 요소가 없음)
        ptr == 8 : [ NULL ] (8도 자식이 없어 추가될 요소가 없고, 8이 delete되면서 queue가 빔 -> 반복 종료)
    */
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