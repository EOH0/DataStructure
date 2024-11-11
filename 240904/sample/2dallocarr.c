#include <stdio.h>
#include <stdlib.h>

int main() {
    int d1, d2;
    int** table;
    int row;

    // 행과 열의 크기
    scanf("%d%d", &d1, &d2);
    table = (int **)calloc(d1, sizeof(int *)); // 행 메모리 할당
    for (int i = 0; i < d1; i++) {
        table[i] = (int *)calloc(d2, sizeof(int)); // 열 메모리 할당
    }

    for (int i  = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            scanf("%d", &table[i][j]); // 행렬의 각 자리에 넣을 숫자
        }
    }

    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            printf("%3d ", table[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < d2; i++) {
        free(table[i]);
    }
    free(table);
}