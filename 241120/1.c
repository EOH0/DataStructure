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
    scanf("%d", &num1);
    scanf("%d", &num2);
    
    bfs(num1, head);
    init(size);
    bfs(num2, head);
    init(size);

    // dfs
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
    printf("%d ", v);
    visited[v] = TRUE;
    addq(v);
    while(front) {
        v = deleteq();
        for (w = head[v]; w; w = w->link) {
            if (!visited[w->vertex]) {
                printf("%d ", w->vertex);
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
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