#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int rows, int cols);
void init2dArray(int** array, int rows, int cols);
int** add2dArray(int** A, int** B, int rows, int cols);
void display2dArray(int** array, int rows, int cols);
void free2dArray(int** array, int rows);

int main() {
    int rows, cols;
    printf("Enter row, column size : ");
    scanf("%d", &rows);
    scanf("%d", &cols);

    int** arrA = make2dArray(rows, cols);
    int** arrB = make2dArray(rows, cols);

    printf("Input A matrix : \n");
    init2dArray(arrA, rows, cols);

    printf("Input B matrix : \n");
    init2dArray(arrB, rows, cols);

    int** arrS = add2dArray(arrA, arrB, rows, cols);

    display2dArray(arrS, rows, cols);

    free2dArray(arrA, rows);
    free2dArray(arrB, rows);
    free2dArray(arrS, rows);
}

int** make2dArray(int rows, int cols) {
    int** arr = (int **)malloc(sizeof(int) * rows);
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(sizeof(int) * cols);
    }

    return arr;
}
void init2dArray(int** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &array[i][j]);
        }
    }
}
int** add2dArray(int** A, int** B, int rows, int cols) {
    int** arrT = make2dArray(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arrT[i][j] = A[i][j] + B[i][j];
        }
    }

    return arrT;
}
void display2dArray(int** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}
void free2dArray(int** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}