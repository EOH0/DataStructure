#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} term;

void readMatrix(FILE* file, int row, int col, int *cnt, term a[]);
void printMatrix(int cnt, term a[]);
void search(int cnt, int input, term a[]);

int main() {
    FILE* file = fopen("f2.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }
    term a[100];

    int row, col;
    int cnt = 0;
    fscanf(file, "%d %d", &row, &col);

    readMatrix(file, row, col, &cnt, a);
    
    fclose(file);

    printMatrix(cnt, a);

    int input;
    scanf("%d", &input);

    search(cnt, input, a);
}

void readMatrix(FILE* file, int row, int col, int *cnt, term a[]) {
    a[0].row = row;
    a[0].col = col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int num;
            fscanf(file, "%d", &num);
            if (num != 0) {
                (*cnt)++;
                a[*cnt].row = i;
                a[*cnt].col = j;
                a[*cnt].value = num;
            }
        }   
    }
    (*cnt)++;
    a[0].value = *cnt;
}
void printMatrix(int cnt, term a[]) {
    for (int i = 0; i < cnt; i++) {
        printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
    }
}
void search(int cnt, int input, term a[]) {
    for (int i = 1; i < cnt; i++) {
        if (a[i].value == input) {
            printf("row: %d\ncolumn: %d\n", a[i].row, a[i].col);
        }
    }
}