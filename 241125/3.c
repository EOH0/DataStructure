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

    for (int i = 1; i <= idx; i++) {
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
            // i + s - 1: 두 세그먼트 중 첫번째 세그먼트의 마지막 인덱스
            // i + 2*s - 1: 두 세그먼트 중 두번째 세그먼트의 마지막 인덱스
                // s는 세그먼트의 크기이기 때문
    } 
    if ((i + s - 1) < n) merge(initList, mergedList, i, i + s - 1, n); 
    else {
        for (j = i; j <= n; j++) {
            mergedList[j] = initList[j];
        }
    }
}

void merge(element initList[], element mergeList[], int i, int m, int n) { // 모든 정렬은 병합과 동시에 이루어짐
    int j, k, t;
    j = m + 1; // 두번쨰 sublist의 인덱스 (합칠 두 배열 중 두번째)
    k = i; // 머지리스트의 인덱스 (합칠 두 배열 중 첫번째)

    while(i <= m && j <= n) {
        if (initList[i].key <= initList[j].key) { // 두 배열을 비교해서 더 작은 값을 먼저 넣음
            mergeList[k++] = initList[i++]; // 머지리스트(병합된 최종 리스트)에 작은 값을 넣고 다음 인덱스로 ++
        }
        else {
            mergeList[k++] = initList[j++]; // 마찬가지로 작은 값 넣음
        }
    }
    // 병합을 다하고 남은 요소들을 추가해줌 (세그먼트에 남아있는 것들)
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