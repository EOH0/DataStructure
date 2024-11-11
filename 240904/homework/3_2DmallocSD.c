#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** build2DArray(int rows, int cols);
void inputData(int** arr, FILE* file, int rows, int cols);
double getAvg(int** arr, int rows, int cols);
double getSd(int** arr, int rows, int cols, double avg);

int main() {
    FILE* file = fopen("f3.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int rows, cols;
    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &cols);
    printf("%d %d\n", rows, cols);

    int **arr = build2DArray(rows, cols);
    fclose(file);

    inputData(arr, file, rows, cols);

    // printf("====================\n");
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         printf("%d ", arr[i][j]);
    //     }
    //     printf("\n");
    // }
    double DataAvg = getAvg(arr, rows, cols); // 평균
    // printf("%lf\n", DataAvg);

    double Sd = getSd(arr, rows, cols, DataAvg); // 표준편차

    printf("%lf\n", Sd);
    printf("표준편차 = %.2lf", floor(Sd*100)/100); // 소수점이하 버리는 floor

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}

int** build2DArray(int rows, int cols) {
    int **arr = (int **)malloc(sizeof(int) * rows);

    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(sizeof(int) * cols);
    }

    return arr;
}
void inputData(int** arr, FILE* file, int rows, int cols) {
    file = fopen("f3.txt", "r");
    fscanf(file, "%*d");
    fscanf(file, "%*d");
    int one;
    int i = 0, j = 0;
    while (fscanf(file, "%d", &one) != EOF) {
        arr[i][j] = one; // 이중포인터 := 2차원 배열
        j++;
        if (j >= cols) {
            j = 0;
            i++;
        }
    }

    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    fclose(file);
}
double getAvg(int** arr, int rows, int cols) {
    int sum = 0;
    double avg = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum = sum + arr[i][j];
        }
    }

    avg = sum / (rows * cols);
    return avg;
}
double getSd(int** arr, int rows, int cols, double avg) {
    double sub[rows][cols]; // 편차
    double var = 0; // 분산
    double sub_sum = 0; // 편차 제곱합
    double sub_avg = 0; // 편차 제곱의 평균

    for (int i = 0; i < rows; i++) { // sub 초기화
        for (int j = 0; j < cols; j++) {
            sub[i][j] = 0;
        }
    }

    for (int i = 0; i < rows; i++) { // sub
        for (int j = 0; j < cols; j++) {
            sub[i][j] = (double)arr[i][j] - avg;
        }
    }

    // for (int i = 0; i < rows; i++) { // sub 체크
    //     for (int j = 0; j < cols; j++) {
    //         printf("%.2lf ", sub[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < rows; i++) { // 편차 제곱합
        for (int j = 0; j < cols; j++) {
            sub_sum = sub_sum + pow(sub[i][j], 2);
        }
    }

    sub_avg = sub_sum / (rows * cols);  // 분산

    double Sd = pow(sub_avg, 0.5); // 표준 편차

    return Sd;
}