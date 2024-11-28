#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;
element heap[MAX_ELEMENTS];

int n = 0; // heap 최대 사이즈

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
void push(element item, int *n) { // MaxHeap 형성
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
    int parent, child; // 부모, 자식의 인덱스
    element item, temp;
    if(HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty\n");
        exit(EXIT_FAILURE);
    }

    item = heap[1]; // MaxHeap의 최상단에 위치한 노드는 항상 최댓값임 => 그 노드를 item에 저장
    temp = heap[(*n)--]; // Heap의 마지막 원소를 temp에 저장하고 원소 개수를 하나 줄임 (temp에 들어간 원소를 Heap에서 삭제)
    parent = 1; // 현재 부모 노드
    child = 2; // 현재 자식 노드
    while (child <= *n) {
        // 자식 중 더 큰 값을 찾는다.
        if ((child < *n) && (heap[child].key < heap[child + 1].key)) {
            child++;
        }
        // 부모 노드가 자식 노드보다 크거나 같으면 멈춘다.
        if (temp.key >= heap[child].key) break;

        // 자식 노드를 부모로 올림.
        heap[parent] = heap[child]; // 노드랑
        parent = child; // 인덱스 값을 둘다 옮겨줌
        child *= 2; // 다음 자식으로 이동
    }
    heap[parent] = temp;
    *size -= 1;
    return item;
}