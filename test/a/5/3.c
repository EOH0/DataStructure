#include <stdio.h>
#include <stdlib.h>

#define MAX_TERM_SIZE 100

typedef struct {
    int row;
    int col;
    int value;
} term;

void readMatrix(char *filename, term matrix[]);
void transpose(term a[], term b[]);
void writeMatrix(const char *filename, term matrix[]);
void printMatrix2D(term matrix[]);

int main() {
    char filenameA[] = "a.txt";
    char filenameB[] = "b.txt";

    term a[MAX_TERM_SIZE] = { 0 };
    term b[MAX_TERM_SIZE] = { 0 };
    readMatrix(filenameA, a);

    transpose(a, b);
    
    writeMatrix(filenameB, b);

    printf("A\n");
    printMatrix2D(a);

    printf("B\n");
    printMatrix2D(b);
}

void readMatrix(char *filename, term matrix[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("fill error");
        return;
    }

    int ind = 0;
    while(fscanf(file, "%d %d %d", &matrix[ind].row, &matrix[ind].col, &matrix[ind].value) != EOF) ind += 1;

    fclose(file);
}
void transpose(term a[], term b[]) {
    // b is set to the transpose of a
    int currentb; // a, b 배열의 인덱스
    int n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;

    if (n > 0) { // non zero matrix
        currentb = 1;
        for (int i = 0; i < a[0].col; i++) { // transpose by the columns in a
            for (int j = 1; j <= n; j++) { // find elements from the current column
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}
void writeMatrix(const char *filename, term matrix[]) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("file error\n");
        return;
    }
    for (int i = 0; i < matrix[0].value; i++) {
        fprintf(file, "%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }
    fclose(file);
}
void printMatrix2D(term matrix[]) {
    int num = 1;
    for (int i = 0; i < matrix[0].row; i++) {
        for (int j = 0; j < matrix[0].col; j++) {
            if(i == matrix[num].row && j == matrix[num].col) {
                printf("%3d", matrix[num].value);
                num++;
            }
            else {
                printf("%3d", 0);
            }
        }
        printf("\n");
    }
}