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

nodePointer createNode(int Node);
edgePointer createEdge(int dstn);
void insertEdge(nodePointer* graph, int src, int dest);
void printGraph(nodePointer graph);

int main() {
    // 그래프 생성 (정점과 간선을 수동으로 추가)
    nodePointer graph = createNode(0);
    graph->nextNode = createNode(1);
    graph->nextNode->nextNode = createNode(2);
    graph->nextNode->nextNode->nextNode = createNode(3);

    // 간선 추가
    insertEdge(&graph, 0, 1);
    insertEdge(&graph, 0, 2);
    insertEdge(&graph, 0, 3);
    insertEdge(&graph, 1, 0);
    insertEdge(&graph, 1, 2);
    insertEdge(&graph, 1, 3);
    insertEdge(&graph, 2, 0);
    insertEdge(&graph, 2, 1);
    insertEdge(&graph, 2, 3);
    insertEdge(&graph, 3, 0);
    insertEdge(&graph, 3, 1);
    insertEdge(&graph, 3, 2);    

    // 그래프 출력
    printGraph(graph);

    // 메모리 해제 코드 필요 (생략)

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

// 간선 삽입 함수
void insertEdge(nodePointer* graph, int src, int dest) {
    nodePointer now = *graph;
    // src 정점 찾기
    while (now != NULL && now->key != src) {
        now = now->nextNode;
    }
    
    if (now != NULL) {
        // 새로운 간선 생성
        edgePointer newEdge = createEdge(dest);
        newEdge->nextEdge = now->edgeList; // 기존의 첫 번째 간선 뒤에 삽입
        now->edgeList = newEdge;
    } else {
        printf("Node %d not found\n", src);
    }
}

// 그래프 출력 함수
void printGraph(nodePointer graph) {
    nodePointer nowNode = graph;
    while (nowNode != NULL) {
        printf("Node %d: ", nowNode->key);
        edgePointer nowEdge = nowNode->edgeList;
        while (nowEdge != NULL) {
            printf("%d ", nowEdge->dstn);
            nowEdge = nowEdge->nextEdge;
        }
        printf("\n");
        nowNode = nowNode->nextNode;
    }
}