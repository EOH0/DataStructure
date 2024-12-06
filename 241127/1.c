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
    // 배열에서 이진 트리의 구조를 지켜 작동하는 구조
    // 그래서 인덱스 child는 항상 부모가 되는 root의 두배
    int child, rootkey;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = 2 * root; // left child
    
    while(child <= n) { // child값이 배열 크기 범위 내다 == 어떤 부모의 자식이 존재한다
        if ((child < n) && (a[child].key > a[child + 1].key)) { // 내림차순을 위한 값 (최소 힙을 구현)
        // child가 n보다 작다 == 절대 마지막 오른쪽 자식은 아니다 or 오른쪽 자식이 존재한다
        // && 오른쪽 자식의 값이 왼쪽 자식의 값보다 크다 == 두 자식 주 더 큰 값을 가지는 자식을 구하기 위함
            // 트리의 구조는 minheap으로 root부터 시작해서 내림차순으로 출력하는 거라 level기준 왼쪽에서 오른쪽으로 갈 수록 작아져야함
            child++; // 
        }
        if (rootkey < a[child].key) { // root, max, child 비교 (minheap을 통한 내림차순 구현) maxheap으로 오름차순으로 하려면 조건 반대로 
            break;
        }
        else {
            a[child / 2] = a[child]; // 부모 자리에 자식을 넣음
            child *= 2;
        }
    }
    a[child / 2] = temp;
}