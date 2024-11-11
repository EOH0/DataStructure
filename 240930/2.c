/*
1 0 0 7
0 0 0 2
0 0 0 0
*/
#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} term;
term a[101];

void readMatrix(FILE* file, int rows, int cols, int *count);
void printMatrix(int row, int cols, int* count);
void search(int row, int col, int x);

int main() {
    FILE* file = fopen("f2.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }
    
    int rows = 0, cols = 0;
    fscanf(file, "%d %d", &rows, &cols);

    int count = 0;
    readMatrix(file, rows, cols, &count);
    fclose(file);

    int x = 0;
    scanf("%d", &x);

    printMatrix(rows, cols, &count);

    search(rows, cols, x);
    return 0;
}

void readMatrix(FILE* file, int rows, int cols, int* count) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = (i * cols) + j;
            fscanf(file, "%d", &a[index].value); // 일단 matrix의 모든 요소를 저장
            a[index].row = i;
            a[index].col = j;
            if (a[index].value != 0) {
                (*count)++; // *count++ != (*count)++
            }
        }
    }
}
void printMatrix(int rows, int cols, int* count) {
    printf("%d %d %d\n", rows, cols, (*count));
    for(int i = 0; i < (rows * cols); i++) {
        if (a[i].value != 0) { // 출력할때 0이 아닌 값만 출력하도록 if
            printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
        }
    }
    printf("\n");
}
void search(int row, int col, int x) {
    for (int i = 0; i < (row * col); i++) {
        if(x == a[i].value) {
            printf("row: %d\n", a[i].row);
            printf("column: %d\n", a[i].col);
        }
    }
}
