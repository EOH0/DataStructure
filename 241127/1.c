// unstable
// 같은 정수값을 가진 쌍에서도 알파벳의 위치가 순서대로 되어있지 않은 것을 봤을때 기존 배열의 순서가 보장되지 않음
#include <stdio.h>

#define MAX_HEAP_SIZE 10
#define SWAP(a, b, temp) {temp = a; a = b; b = temp;}

typedef struct {
    int key;
} element;

void heapSort(element a[], int n);
void adjust(element a[], int root, int n);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int num;
    int ind = 1;
    element a[MAX_HEAP_SIZE];
    while(fscanf(file, "%d", &num) != EOF) {
        a[ind].key = num;
        ind += 1;
    }
    fclose(file);
    
    int size = ind - 1;
    heapSort(a, size);

    for (int i = 1; i <= size; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");

}

void heapSort(element a[], int n) { // a[1:n]에서 heap sort 수행
    int i;
    element temp;

    for (i = n/2; i > 0; i--) {
        adjust(a, i, n);
    }
    for (i = n - 1; i > 0; i--) {
        SWAP(a[1], a[i + 1], temp);
        adjust(a, 1, i);
    }
}
void adjust(element a[], int root, int n) { // 이진트리에서 힙을 만들기 위해 조정하는 함수
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root; // left child

    while(child <= n) {
        if ((child < n) && (a[child].key > a[child + 1].key)) {
            child++;
        }
        if (rootkey < a[child].key) { // root, max, child 비교
            break;
        }
        else {
            a[child / 2] = a[child]; // 부모로 이동
            child *= 2;
        }
    }
    a[child / 2] = temp;
}