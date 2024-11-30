#include <stdio.h>
#include <stdlib.h>

typedef struct edge* edgePointer;
typedef struct edge {
    int dstn;
    edgePointer nextEdge;
    edgePointer nextMultiEdge; // 다중 간선 그룹을 위한 포인터
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
    newEdge->nextMultiEdge = NULL; // 다중 간선 포인터 초기화
    return newEdge;
}

// 간선 삽입 함수 (다중 간선 허용)
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

        edgePointer nowEdge = now->edgeList;

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
