#include <stdio.h>

#define MAX_HEAP_SIZE 101

typedef struct {
    int key;
} element;

element heap[MAX_HEAP_SIZE];
int n = 0; // heap내부 요소의 개수

void push(element item, int* n);
element pop(int *n, int *size);

int main() {
    FILE* file = fopen("in2.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);
    int num;
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        element item;
        item.key = num;
        push(item, &n);
    }

    for (int i = 1; i <= size; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");

    int target;
    fscanf(file, "%d", &target);
    printf("%d\n", target);
    for (int i = 0; i < target; i++) {
        pop(&n, &size);
    }

    for (int i = 1; i <= size; i++) {
        printf("%d ", heap[i].key);
    }
}
void push(element item, int* n) {
    int i;
    if (*n == MAX_HEAP_SIZE - 1) {
        printf("heap full\n");
        return ;
    }
    i = ++(*n);
    while((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2]; // 자식 자리에 현재의 부모를 넣음
        i /= 2;
    }
    heap[i] = item; // 자리가 빈 부모의 자리에 넣고자하는 값 넣음
     // 왜냐? maxheap을 위해
}
element pop(int *n, int *size) {
    int parent, child;
    element temp, item;
    if (n == 0) {
        printf("heap empty");
        return item;
    }

    item = heap[1];
    temp = heap[(*n)--];
    parent = 1;
    child = 2;
    while(child <= *n) {
        if ((child < *n) && (heap[child].key < heap[child + 1].key)) {
            child++;
        }

        if (temp.key >= heap[child].key) {
            break;
        }

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    (*size)--;
    return item;
}