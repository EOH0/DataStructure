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
void printGraph(nodePointer graph);

int main() {
    nodePointer graph = createNode(0);
    graph->nextNode = createNode(1);
    graph->nextNode->nextNode = createNode(2);
    graph->nextNode->nextNode->nextNode = createNode(3);
    graph->nextNode->nextNode->nextNode->nextNode = createNode(4);
    graph->nextNode->nextNode->nextNode->nextNode->nextNode = createNode(5);

    insertEdge(&graph, 1, 0);
    insertEdge(&graph, 1, 3);
    insertEdge(&graph, 2, 1);
    insertEdge(&graph, 2, 5);
    insertEdge(&graph, 3, 2);
    insertEdge(&graph, 3, 4);
    insertEdge(&graph, 3, 5);
    insertEdge(&graph, 4, 0);
    insertEdge(&graph, 5, 0);
    insertEdge(&graph, 5, 1);
    insertEdge(&graph, 5, 4);

    printGraph(graph);


    return 0;
}

nodePointer createNode(int key) {
    nodePointer newNode = (nodePointer)malloc(sizeof(node));
    newNode->key = key;
    newNode->edgeList = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

edgePointer createEdge(int dstn) {
    edgePointer newEdge = (edgePointer)malloc(sizeof(edge));
    newEdge->dstn = dstn;
    newEdge->nextEdge = NULL;
    return newEdge;
}

void insertEdge(nodePointer* graph, int start, int dest) {
    nodePointer now = *graph;
    // start 정점 찾기
    while (now != NULL && now->key != start) { // 시작하고자하는 위치인 start와 같은 key를 가진 노드를 찾기 위한 반복
    // 찾으면 now는 start 노드가 됨
    // 찾지 못하면 now는 NULL이 되고 아래의 조건문을 실행하지 못함
        now = now->nextNode;
    }

    if (now != NULL) { // start의 노드가 존재할떄
        // 새로운 간선 생성
        edgePointer newEdge = createEdge(dest);

        edgePointer nowEdge = now->edgeList; // nowEdge는 now에서 adjacency multilist를 작업할 수 있도록 함
        // now 노드의 간선 리스트를 수정, 탐색할때 이용

        // 같은 목적지를 가진 다중 간선이 있는지 확인
        if (nowEdge == NULL) { // 없으면 리스트의 첫번쨰 요소로 추가
            now->edgeList = newEdge;
        } else { // 있으면 현재 리스트 끝으로 이동하여 새 간선을 추가
            while (nowEdge->nextEdge != NULL) {
                nowEdge = nowEdge->nextEdge;
            }
            nowEdge->nextEdge = newEdge;
        }
    } else {
        printf("Node %d not found\n", start);
    }
}

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
