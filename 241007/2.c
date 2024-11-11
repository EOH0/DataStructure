#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
    short int vert;
    short int horiz;
} offsets;
offsets move[9];

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;
element stack[MAX_STACK_SIZE];

int top = 0;
int capacity = 1;

void setOffset();
void path(int **maze, char **mark, int MazeRow, int MazeCol, int entRow, int entCol, int exitRow, int exitCol);
element pop();
void stackEmpty();
void push(element item);
void stackFull();
void FileOutput(char** mark, int Mazerow, int Mazecol);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error.\n");
    }

    setOffset();

    int Mazerow, Mazecol;
    fscanf(file, "%d %d", &Mazerow, &Mazecol);
    Mazerow += 2;
    Mazecol += 2;

    int entRow, entCol;
    int exitRow, exitCol;
    scanf("%d %d %d %d", &entRow, &entCol, &exitRow, &exitCol);

    int **maze = (int **)malloc(sizeof(int*) * Mazerow);
    char **mark = (char **)malloc(sizeof(char*) * Mazerow);
    for (int i = 0; i < Mazerow; i++) {
        maze[i] = (int *)malloc(sizeof(int) * Mazecol);
        mark[i] = (char *)malloc(sizeof(char) * Mazecol);
    }

    for (int i = 0; i <= Mazerow - 1; i++) {
        for (int j = 0 ; j <= Mazecol - 1; j++) {
            if (i == 0 || j == 0 || i == Mazerow - 1 || j == Mazecol - 1) {
                maze[i][j] = 1;
                mark[i][j] = '1';
            }
            else {
                fscanf(file, "%d", &maze[i][j]);
                if (maze[i][j] == 0) {
                    mark[i][j] = '0';
                }
                else {
                    mark[i][j] = '1';
                }
            }
        }
    }

    path(maze, mark, Mazerow, Mazecol, entRow, entCol, exitRow, exitCol);

    FileOutput(mark, Mazerow, Mazecol);

    for (int i = 0; i < Mazerow; i++) {
        free(maze[i]);
        free(mark[i]);
    }
    free(maze);
    free(maze);
}

void setOffset() {
    int vert[9] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int horiz[9] = {0, 1, 1, 1, 0, 0, -1, -1, -1};
    for (int i = 0; i < 8; i++) {
        move[i].vert = vert[i];
        move[i].horiz = horiz[i];
    }
}
void path(int **maze, char **mark, int MazeRow, int MazeCol, int entRow, int entCol, int exitRow, int exitCol) {
    int row, col, nextRow, nextCol, dir;
    int flag = 0;
    element position;
    mark[entRow][entCol] = 'x'; top = 0;
    stack[0].row = entRow; stack[0].col = entCol;
    stack[0].dir = 0;
    while(top > -1 && nextRow != exitRow && nextCol != exitCol) {
        position = pop(); // position <- stack[prev] (back tracking)
        row = position.row;
        col = position.col;
        dir = position.dir;
        if (flag) { // 길이 막혀 다시 돌아가는 경우 '0'으로 초기화하고 진행 (첫 값이자 flag가 0인 [entRow][entCol]에서는 시행 X)
            mark[row][col] = '0';
        }
        flag = 1;
        while (dir < 8) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (maze[nextRow][nextCol] == 0 && mark[nextRow][nextCol] != 'x') {
                mark[nextRow][nextCol] = 'x';
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            }
            else {
                ++dir;
            }
        }
    }
}

element pop() {
    if (top == -1) {
        exit(1);
    }
    return stack[top--];
}
void push(element item) {
    if (top >= capacity - 1) {
        stackFull();
    }
    stack[++top] = item;
}
void stackFull() {
    realloc(stack, 2 * capacity * sizeof(stack));
    capacity *= 2;
}

void FileOutput(char** mark, int Mazerow, int Mazecol) {
    FILE* file = fopen("out.txt", "w");
    if (file == NULL) {
        printf("file error.\n");
        return ;
    }

    for (int i = 1; i < Mazerow - 1; i++) {
        for (int j = 1 ; j < Mazecol - 1; j++) {
            fprintf(file, "%c ", mark[i][j]);
        }
        fprintf(file, "\n");
    }
}