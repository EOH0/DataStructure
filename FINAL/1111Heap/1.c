#include <stdio.h>

#define MAX_HEAP_SIZE 101

typedef struct {
    int key;
} element;

element heap[MAX_HEAP_SIZE];
int n = 0; // heap내부 요소의 개수

void push(element item, int* n);


int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);
    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        element item;
        item.key = num;
        push(item, &n);
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
        i /= 2; // 다음 부모로 이동
    }
    heap[i] = item; // 자리가 빈 부모의 자리에 넣고자하는 값 넣음
     // 왜냐? maxheap을 위해
}