#include <stdio.h>
#include <stdlib.h>

int main() {
    int row = 5;
    int col = 5;

    row += 2;
    col += 2;

    int** maze = (int **)malloc(sizeof(int*) * row);
    int** mark = (int **)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        maze[i] = (int*)malloc(sizeof(int) * col);
        mark[i] = (int*)malloc(sizeof(int) * col);
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 || j == 0 || i == row - 1 || j == col - 1) {
                maze[i][j] = 1;
                mark[i][j] = 1;
            }
            else {
                maze[i][j] = 0;
                mark[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d ", mark[i][j]);
        }
        printf("\n");
    }
}