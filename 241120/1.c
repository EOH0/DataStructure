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
typedef struct queue* queuePointer;
typedef struct queue {
    int vertex;
    queuePointer link;
} Queue;
queuePointer front;
queuePointer rear;
int capacity = 10;

int QueueEmpty();
void init(int size);
void dfs(int v, nodePointer *head);
void bfs(int v, nodePointer *head);
void addq(int vertex);
int deleteq();
nodePointer createNode(int vertex);
void insertNode(int vertex, nodePointer *head);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size = 0;
    fscanf(file, "%d", &size);

    front = (queuePointer)malloc(sizeof(Queue) * capacity);
    rear = (queuePointer)malloc(sizeof(Queue) * capacity);

    nodePointer *head = (nodePointer *)malloc(sizeof(nodePointer) * (size + 1));
    for (int i = 0; i <= size; i++) {
        head[i] = NULL;
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            int num;
            fscanf(file, "%d", &num);
            if (num == 1) {
                insertNode(i, &head[j]);
                insertNode(j, &head[i]);
            }
        }
    }

    fclose(file);

    for (int i = 0; i <= size; i++) {
        visited[i] = FALSE;
    }

    int num1, num2;

    // bfs
    printf("bfs:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    
    bfs(num1, head);
    init(size);
    bfs(num2, head);
    init(size);

    // dfs
    printf("dfs:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);

    dfs(num1, head);
    init(size);
    dfs(num2, head);
    init(size);
}

void init(int size) {
    for (int i = 0; i <= size; i++) {
        visited[i] = FALSE;
    }
    printf("\n");
}
nodePointer createNode(int vertex) {
    nodePointer newnode = (nodePointer)malloc(sizeof(Node));
    newnode->vertex = vertex;
    newnode->link = NULL;
    return newnode;
}
void insertNode(int vertex, nodePointer *head) {
    // newnode->link = *head;
    // *head = newnode;
    nodePointer newnode = createNode(vertex);
    if (*head == NULL) {
        newnode->link = NULL;
        *head = newnode;
    }
    else {
        nodePointer trail = *head;
        while(trail->link != NULL) {
            trail = trail->link;
        }
        trail->link = newnode;
    }
}
void bfs(int v, nodePointer *head) {
    nodePointer w;
    front = rear = NULL;
    printf("%d ", v); // 시작하는 값 출력
    visited[v] = TRUE; // 시작하는 값 마킹
    addq(v); // 큐에 시작 값 추가
    while(front) { // front가 NULL이 아닐 때까지
        v = deleteq(); // 현재 queue에 있는 값 
        for (w = head[v]; w; w = w->link) {
            if (!visited[w->vertex]) {
                printf("%d ", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
        }
    }
    /*
        0 1 2 3 4 5 6 7 이 있다고 가정
        그래프는 니가 생각하는 그 그래프
        1. 맨 처음 큐에 0을 넣음 v = NULL / queue: [ 0 ]
        2. queue에서 0을 delete하고 v에 할당 v = 0 / queue: [ ]
        3. 0이랑 연결된 노드들을 탐색, 이때 for 반복의 w를 head를 0으로 지정 -> 연결된 리스트 탐색하는데 이점
            연결된 리스트를 printf하고 queue에 추가 v = 0 / queue: [ 1, 2 ] => front = 1 / rear = 2
            queue에 추가할때는 연결된 리스트의 값이 존재하더라도 visited가 FALSE인 경우만 추가
        4. 0 반복 종료하고 queue에서 1을 delete하고 v에 할당 v = 1 / queue: [ 2 ]
        6. 1에 연결된 노드들을 탐색
            인접 노드 (1 연결리스트에 연결된 노드 중 방문하지 않은 것) 3, 4 추가 v = 1 / queue: [ 2, 3, 4 ] => front = 2 / rear = 4
            1에는 0도 연결되어 있으나 visited[0]은 TRUE(방문을 했음)이므로 queue에 추가되지 않음
        7. 과정을 계속 반복
        8. for문을 다 돌고 나왔는데 front가 비었다 == for에서 어떤 것도 queue에 추가되지 않았다
        9. front가 비었으므로 while문의 조건에 의해 종료
    */
}
void dfs(int v, nodePointer *head) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%d ", v);
    for (w = head[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex, head);
        }
    }
}
void addq(int vertex) {
    queuePointer temp = (queuePointer)malloc(sizeof(Queue));
    temp->vertex = vertex;
    temp->link = NULL;
    if (front) {
        rear->link = temp;
    }
    else {
        front = temp;
    }
    rear = temp;
}
int deleteq() {
    int item;
    if(!front) {
        return QueueEmpty();
    }
    queuePointer temp = front;
    item = temp->vertex;
    front = temp->link;
    free(temp);
    if (!front) {
        rear = NULL;
    }
    return item;
}
int QueueEmpty() {
    printf("queueEmpty");
    return -1;
}