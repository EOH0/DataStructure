#include <stdio.h>
#include <stdlib.h>

int sumAry1D(int *ary, int size);

int main() {
    FILE* file = fopen("f4.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int rows;
    fscanf(file, "%d", &rows);

    int **ary = (int **)malloc(sizeof(int *) * rows);
    int *sizes = (int *)malloc(sizeof(int) * rows);

    for (int i = 0; i < rows; i++) {
        int cols;
        fscanf(file, "%d", &cols);

        sizes[i] = cols; // 각 열의 요소가 몇개인지 저장
        ary[i] = (int *)malloc(sizeof(int) * cols); // cols만큼 가변 길이 할당

        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &ary[i][j]);
        }
    }

    // 합
    int sum[rows];
    for (int i = 0; i < rows; i++) {
        sum[i] = sumAry1D(ary[i], sizes[i]);
        printf("%d\n", sum[i]);
    }

    int ary_sum = 0;
    for (int i = 0; i < rows; i++) {
        ary_sum = ary_sum + sum[i];
    }
    
    printf("배열 합 = %d\n", ary_sum);

    for (int i = 0; i < rows; i++) {
        free(ary[i]);
    }
    free(ary);
    free(sizes);

    fclose(file);
    return 0;
}

int sumAry1D(int *ary, int size) { // 따로 빼서 더해줌
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum = sum + ary[i];
    }
    return sum;
}