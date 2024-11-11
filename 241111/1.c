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

int main() {
    FILE* file = fopen("in1.txt", "r");
    // FILE* file = fopen("in2.txt", "r");
    
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size = 0;
    fscanf(file, "%d", &size);

    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        element item;
        item.key = num;
        push(item, &n);
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