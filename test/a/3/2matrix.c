#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int rows, int cols);
void init2dArray(int** array, int rows, int cols);
int** add2dArray(int** A, int** B, int rows, int cols);
void display2dArray(int** array, int rows, int cols);
void free2dArray(int** array, int rows);

int main() {
    int row, col;
    printf("Enter row, column size: ");
    scanf("%d %d", &row, &col);

    int** arrA = make2dArray(row, col);
    int** arrB = make2dArray(row, col);

    printf("Input A matrix: ");
    init2dArray(arrA, row, col);

    printf("Input B matrix: ");
    init2dArray(arrB, row, col);

    int** arrC = add2dArray(arrA, arrB, row, col);

    display2dArray(arrC, row, col);
    
    free2dArray(arrA, row);
    free2dArray(arrB, row);
    free2dArray(arrC, row);
}

int** make2dArray(int rows, int cols) {
    int** arr = (int **)malloc(sizeof(int*) * rows);
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
    int** C = make2dArray(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
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