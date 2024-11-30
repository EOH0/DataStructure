#include <stdio.h>
#include <stdlib.h>

typedef struct edge* edgePointer;
typedef struct edge {
    int dstn;
    edgePointer nextEdge;
} edge;

typedef struct node* nodePointer;
typedef struct node {
    int key;
    edgePointer edgeList;
    nodePointer nextNode;
} node;

nodePointer createNode(int key);
edgePointer createEdge(int dstn);
void insertEdge(nodePointer* graph, int start, int dest);
void printAdjacencyList(nodePointer* graph, int key);

int main() {
    int vertexCount;
    scanf("%d", &vertexCount);

    // Adjacency matrix 입력
    int **adjMatrix = (int **)malloc(vertexCount * sizeof(int *));
    for (int i = 0; i < vertexCount; i++) {
        adjMatrix[i] = (int *)malloc(vertexCount * sizeof(int));
        for (int j = 0; j < vertexCount; j++) {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    // 그래프 초기화
    nodePointer* graph = (nodePointer*)malloc(vertexCount * sizeof(nodePointer));
    for (int i = 0; i < vertexCount; i++) {
        graph[i] = createNode(i);
    }

    // Adjacency list 구성
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (adjMatrix[i][j] == 1) { // 간선이 존재하는 경우
                insertEdge(graph, i, j);
                insertEdge(graph, j, i); // 무방향 그래프이므로 역방향도 추가
            }
        }
    }

    // 특정 노드의 인접 리스트 출력
    int query;
    scanf("%d", &query);
    printAdjacencyList(graph, query);

    // 메모리 해제
    for (int i = 0; i < vertexCount; i++) {
        free(adjMatrix[i]);
        free(graph[i]);
    }
    free(adjMatrix);
    free(graph);

    return 0;
}

// 정점 생성 함수
nodePointer createNode(int key) {
    nodePointer newNode = (nodePointer)malloc(sizeof(node));
    newNode->key = key;
    newNode->edgeList = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

// 간선 생성 함수
edgePointer createEdge(int dstn) {
    edgePointer newEdge = (edgePointer)malloc(sizeof(edge));
    newEdge->dstn = dstn;
    newEdge->nextEdge = NULL;
    return newEdge;
}

// 간선 삽입 함수 (무방향 그래프용)
void insertEdge(nodePointer* graph, int start, int dest) {
    nodePointer currentNode = graph[start];
    edgePointer newEdge = createEdge(dest);

    if (currentNode->edgeList == NULL) {
        currentNode->edgeList = newEdge;
    } else {
        edgePointer lastEdge = currentNode->edgeList;
        while (lastEdge->nextEdge != NULL) {
            lastEdge = lastEdge->nextEdge;
        }
        lastEdge->nextEdge = newEdge;
    }
}

// 특정 노드의 인접 리스트 출력 함수
void printAdjacencyList(nodePointer* graph, int key) {
    nodePointer currentNode = graph[key];
    if (currentNode != NULL) {
        printf("Node %d: ", key);
        edgePointer currentEdge = currentNode->edgeList;
        while (currentEdge != NULL) {
            printf("%d ", currentEdge->dstn);
            currentEdge = currentEdge->nextEdge;
        }
        printf("\n");
    } else {
        printf("Node %d not found\n", key);
    }
}
