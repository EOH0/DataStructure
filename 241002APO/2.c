#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
} element;
element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void addq(element item);
element deleteq();
void queueFull();
void queueEmpty();

int main() {
    char input;
    element item;
    while(input != 'F') {
        scanf("%c", &input);
        switch (input) {
            case 'I':
                scanf("%d", &item);
                addq(item);
                break;
            case 'D':
                deleteq();
            case 'F':
                break;
        }
    }
    for (int i = front + 1; i <= rear; i++) { // front + 1 ~ rear=
        printf("%d ", queue[i].key);
    }
}

void addq(element item) {
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    if (rear == MAX_QUEUE_SIZE) {
        queueFull();
    }
    queue[rear] = item;
}
element deleteq() {
    if (front == rear) {
        queueEmpty();
        return queue[rear];
    }
    printf("%d ", queue[front + 1]);
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}
void queueFull() {
    printf("Queue Full\n");
}
void queueEmpty() {
    printf("-1 ");
}