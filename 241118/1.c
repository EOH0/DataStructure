// 5 1 1 0 1 1 0 1 0 0 1
/*
    1-2 O
    1-3 O
    1-4 X
    1-5 O

    2-3 O
    2-4 X
    2-5 O
    
    3-4 X
    3-5 X

    4-5 O
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

nodePointer createNode(int vertex);
void insertNode(nodePointer* head, int vertex);
void printList(nodePointer* head, int size);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);

    nodePointer* head = (nodePointer*)malloc(sizeof(nodePointer) * (size + 1));
    for (int i = 1; i <= size; i++) {
        head[i] = NULL;
    }

    for (int i = 1; i < size; i++) {
        for (int j = i + 1; j <= size; j++) {
            int num;
            fscanf(file, "%d", &num);
            if (num == 1) {
                insertNode(&head[i], j);
                insertNode(&head[j], i);
            }
        }
    }
    fclose(file);

    printList(head, size);
}

nodePointer createNode(int vertex) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->link = NULL;
    return newNode;
}
void insertNode(nodePointer* head, int vertex) { // 가장 앞에 새로운 노드를 위치
    nodePointer newNode = createNode(vertex);
    newNode->link = *head;
    *head = newNode;
}
// row, col개의 head를 기준으로 연결리스트가 다 따로 있음
// head부터 NULL까지 출력하기
void printList(nodePointer* head, int size) {
    for (int i = 1; i <= size; i++) {
        printf("Vertex %d: ", i);
        nodePointer now = head[i];
        while (now != NULL) {
            printf("%d ", now->vertex);
            now = now->link;
        }
        printf("\n");
    }
}
