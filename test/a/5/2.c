#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;
element queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

void addQ(element item);
element deleteQ();
void queueFull();
void queueEmpty();

int main() {
    element item;
    char input;
    while(input != 'F') {
        scanf("%c", &input);
        switch (input) {
        case 'I':
            scanf("%d", &item.key);
            addQ(item);
            break;
        case 'D':
            deleteQ();
            break;
        case 'F':
            break;
        }
    }
    for (int i = front + 1; i <= rear; i++) {
        printf("%d ", queue[i].key);
    }
}

void addQ(element item) {
    if (rear == MAX_QUEUE_SIZE) {
        queueFull();
    }
    queue[++rear] = item;
}
element deleteQ() {
    if (front == rear) {
        queueEmpty();
        return queue[front];
    }
    printf("%d\n", queue[front + 1]);
    front += 1;
    return queue[front];
}
void queueFull() {
    printf("queueFull\n");
    exit(EXIT_FAILURE);
}
void queueEmpty() {
    printf("-1 ");
}