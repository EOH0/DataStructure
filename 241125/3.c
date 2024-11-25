#include <stdio.h>

#define MAX_ELEMENT_SIZE 11

typedef struct {
    int key;
} element;

void mergeSort(element a[], int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void merge(element initList[], element mergeList[], int i, int m, int n);

int main() {
    FILE* file = fopen("in3.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    element a[MAX_ELEMENT_SIZE];
    int num;
    int idx = 0;
    while(fscanf(file, "%d", &num) != EOF) {
        a[idx].key = num;
        idx++;
    }

    mergeSort(a, idx);

    for (int i = 0; i < idx; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}

void mergeSort(element a[], int n) { // 전체적 mergeSort
    int s = 1; // 현재 세그먼트 사이즈
    element extra[MAX_ELEMENT_SIZE];

    while(s < n) {
        mergePass(a, extra, n, s);
        s *= 2;
        mergePass(extra, a, n, s);
        s *= 2;
    }
}

void mergePass(element initList[], element mergedList[], int n, int s) { // mergePass의 세그먼트를 병합하는 과정을 진행
    // n: 리스트의 요소의 개수
    // s: 각 정렬된 세그먼트 크기
    int i, j;
    for (i = 0; i < n - 2*s + 1; i+= 2*s) {
        merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
    }
    if ((i + s - 1) < n) merge(initList, mergedList, i, i + s - 1, n);
    else {
        for (j = i; j <= n; j++) {
            mergedList[j] = initList[j];
        }
    }
}

void merge(element initList[], element mergeList[], int i, int m, int n) { // 병합만 담당
    int j, k, t;
    j = m + 1; // 두번쨰 sublist의 인덱스
    k = i; // 머지리스트의 인덱스

    while(i <= m && j <= n) {
        if (initList[i].key <= initList[j].key) {
            mergeList[k++] = initList[i++];
        }
        else {
            mergeList[k++] = initList[j++];
        }
    }
    if (i > m) { // mergeList[k:n] = initList[j:n]
        for (t = j; t <= n; t++) {
            mergeList[t] = initList[t];
        }
    }
    else { // mergeList[k:n] = initList[i:m]
        for (t = i; t <= m; t++) {
            mergeList[k + t - i] = initList[t];
        }
    }
}