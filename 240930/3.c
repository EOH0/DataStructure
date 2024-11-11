/*
1 0 0 7
0 0 0 2
0 0 0 0
*/
#include <stdio.h>

#define MAX_TERMS 101
typedef struct {
    int row;
    int col;
    int value;
} term;

void readMatrix(FILE* file, term a[], int rows, int cols, int *count);
void printMatrix(term a[], int row, int cols, int* count);
void search(term a[], int row, int col, int x);

int main() {
    FILE* file = fopen("f2.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }
    term a[MAX_TERMS]; // a == &a[0]
    
    int rows = 0, cols = 0;
    fscanf(file, "%d %d", &rows, &cols);

    int count = 0;
    readMatrix(file, a, rows, cols, &count);
    fclose(file);

    // for (int i = 0; i < rows * cols; i++) {
    //     printf("%d ", a[i].value);
    // }
    int x = 0;
    scanf("%d", &x);

    printMatrix(a, rows, cols, &count);

    search(a, rows, cols, x);
    return 0;
}

void readMatrix(FILE* file, term a[], int rows, int cols, int* count) { // term a[] == term* a --- term* a[] == 이중포인터가 되
    // 배열의 이름인 a는 &a[0]의 포인터로 사용될 수 있음 => a를 &a[0]로 인식해서 포인터인 term a[]로 받음
    // a == a[0]의 주솟값
    // 포인터 배열 a는 1차원 배열처럼 사용 가능
        // 이중포인터가 2차원 배열처럼 사용 가능하듯이
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = (i * cols) + j;
            fscanf(file, "%d", &a[index].value);
            a[index].row = i;
            a[index].col = j;
            if (a[index].value != 0) {
                (*count)++; // *count++ != (*count)++
            }
        }
    }
}
void printMatrix(term a[], int rows, int cols, int* count) {
    printf("%d %d %d\n", rows, cols, (*count));
    for(int i = 0; i < (rows * cols); i++) {
        if (a[i].value != 0) {
            printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
        }
    }
    printf("\n");
}
void search(term a[], int row, int col, int x) {
    for (int i = 0; i < (row * col); i++) {
        if(x == a[i].value) {
            printf("row: %d\n", a[i].row);
            printf("column: %d\n", a[i].col);
        }
    }
}
