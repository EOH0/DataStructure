#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
element *queue;
int rear = -1;
int front = -1;
int capacity = 10;

void queuefull();
void copy(element* start, element* end, element* newqueue);
void addQ(element item);
element deleteQ();

int main() {
    queue = (element *)malloc(sizeof(element) * capacity);
    
    char input;
    element item;
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
        }
    }
    for (int i = (front + 1) % capacity; i != (rear + 1) % capacity; i = (i + 1) % capacity) {
        printf("%d ", queue[i].key);
    }
}

void queuefull() {
    element* newqueue = (element *)malloc(sizeof(element) * 2 * capacity);
    int start = (front + 1) % capacity;
    if (start < 2) {
        copy(queue + start, queue + start + capacity - 1, newqueue);
    }
    else {
        copy(queue + start, queue + capacity, newqueue);
        copy(queue, queue + rear + 1, newqueue + start - capacity);
    }

    front = 2 * capacity - 1;
    rear = capacity - 2;
    capacity *= 2;
    free(queue);
    queue = newqueue;
}
void copy(element* start, element* end, element* newqueue) {
    while(start != end) {
        *newqueue = *start;
        newqueue++;
        start++;
    }
}
void addQ(element item) {
    rear = (rear + 1) % capacity;   
    if (rear == front) {
        queuefull();
        rear = (rear + 1) % capacity;   
    }
    queue[rear] = item;
}
element deleteQ() {
    if (front == rear) {  // 큐가 비어 있는 상태
        printf("-1 ");
        element empty = { -1 };  // 빈 상태의 값을 반환
        return empty;
    }
    printf("%d ", queue[front + 1]);
    front = (front + 1) % capacity;
    return queue[front];
}

