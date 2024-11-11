#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
int front = -1;
int rear = -1;
int capacity = 5;
element *queue;

void Qfull();
void qEmpty();
element* copy(element* start, element* end, element* newqueue);

int main() {
    queue = (element *)malloc(sizeof(element) * capacity);
}

void Qfull() {
    element *newqueue = (element *)malloc(sizeof(element) * capacity * 2);
    int start = (front + 1) % capacity;
    if (start < 2) {
        copy(queue + start, queue + capacity - 1; newqueue);
    }
    else {
        copy(queue + start, queue + capacity, newqueue);
        copy(queue, queue + rear + 1, newqueue + capacity - start);
    }
}

element* copy(element* start, element* end, element* newqueue) {
    while(start != end) {
        *newqueue = *start;
        start++;
        newqueue++;
    }
}

void qEmpty() {
    printf("-1 ");
}