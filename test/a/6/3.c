#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
element *queue;
int front = -1;
int rear = -1;
int capacity = 2;

void QueueEmpty();
void QueueFull();
void addQ(element item);
element deleteQ();
void copy(element* start, element* finish, element* newQueue);

int main() {
    queue = (element *)malloc(sizeof(element) * capacity);
    element item;
    char input;
    while(input != 'F'){
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

    free(queue);
}

void QueueEmpty() {
    printf("-1 ");
}
void QueueFull() {
    element* newQueue = (element *)malloc(sizeof(element) * capacity * 2);
    // copy from queue to newQueue
    int start = (front + 1) % capacity;
    if (start < 2) {
        // no wrap around
        copy(queue + start, queue + start + capacity - 1, newQueue);
    }
    else {
        // queue wraps around
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue +rear + 1, newQueue + capacity - start);
    }
    // switch to newQueue
    front = 2*capacity-1;
    rear = capacity - 2; // queue size = capacity - 1
    capacity *= 2;
    free(queue);
    queue = newQueue;
}
void addQ(element item) {
    if ((rear + 1) % capacity == front) {
        QueueFull();
    }
    rear = (rear + 1) % capacity;
    queue[rear] = item;
}
element deleteQ() {
    if (front == rear) {
        QueueEmpty();
        return queue[rear];
    }
    printf("%d\n", queue[front + 1]);
    front = (front + 1) % capacity;
    return queue[front];
}
void copy(element* start, element* finish, element* newQueue) {
    while(start != finish) {
        *newQueue = *start; // 주솟값 저장
        newQueue++;
        start++;
    }
}