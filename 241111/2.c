#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;
element heap[MAX_ELEMENTS];

int n = 0;

void push(element item, int *n);
void printHeap(int size);
element pop(int *n, int *size);

int main() {
    FILE* file = fopen("in3.txt", "r");
    // FILE* file = fopen("in4.txt", "r");
    
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size = 0;
    fscanf(file, "%d", &size);

    int num;
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        element item;
        item.key = num;
        push(item, &n);
    }

    printHeap(size);

    int times = 0;
    fscanf(file, "%d", &times);

    for (int i = 0; i < times; i++) {
        pop(&n, &size);
    }
    fclose(file);

    printHeap(size);
}

void printHeap(int size) {
    for (int i = 1; i <= size; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
}
void push(element item, int *n) {
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full\n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n);
    while((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = item;
}
element pop(int *n, int *size) {
    int parent, child;
    element item, temp;
    if(HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty\n");
        exit(EXIT_FAILURE);
    }

    item = heap[1];
    temp = heap[(*n)--];
    parent = 1;
    child = 2;
    while(child  <= *n) {
        if ((child < *n) && (heap[child].key < heap[child + 1].key)) {
            child++;
        }
        if (temp.key >= heap[child].key) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    *size -= 1;
    return item;
}