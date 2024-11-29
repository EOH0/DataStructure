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

#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100
short int visited[MAX_VERTICES];

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} Node;

void dfs(int v, nodePointer *head);
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

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            visited[j] = FALSE;
        }
    }

    int input;
    scanf("%d", &input);
    dfs(input, head);
}

nodePointer createNode(int vertex) {
    nodePointer newNode = (nodePointer)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->link = NULL;
    return newNode;
}
void insertNode(nodePointer* head, int vertex) {
    nodePointer newNode = createNode(vertex);
    newNode->link = *head;
    *head = newNode;
}
void dfs(int v, nodePointer *head) {
    nodePointer w;
    visited[v] = TRUE; // 방문한 노드는 TRUE로 표시
    printf("%d ", v); // 방문한 노드를 출력

    // 현재 정점 v의 인접 리스트를 탐색
    for (w = head[v]; w; w = w->link) {
        if (!visited[w->vertex]) { // 방문하지 않은 인접 노드 확인
            dfs(w->vertex, head); // 재귀 호출로 탐색
        }
    }
}