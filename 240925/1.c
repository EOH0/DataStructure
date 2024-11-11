#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int linearSearch(int* arr, int n, int target);

int main(){
    srand(time(NULL)); // 난수 시드 초기화

    int n;
    scanf("%d", &n);
    int target;
    scanf("%d", &target);

    int* arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    clock_t start = clock(); // 탐색 시간 측정 시작
    int index = linearSearch(arr, n, target);
    clock_t stop = clock(); // 탐색 시간 측정 종료

    double duration = (double)(stop - start) / CLOCKS_PER_SEC; // 탐색 시간 계산

    if (index == -1) {
        printf("Not found\n");
    }
    else {
        printf("Index : %d\n", index);
    } 
    printf("%lf\n", duration);

    free(arr);
}

int linearSearch(int* arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}