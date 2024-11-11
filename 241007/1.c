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
void path(int **maze, int **mark, int MazeRow, int MazeCol);
element pop();
void stackEmpty();
void push(element item);
void stackFull();

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error.\n");
    }

    setOffset();

    int Mazerow, Mazecol;
    fscanf(file, "%d %d", &Mazerow, &Mazecol);
    Mazerow += 2; // 1로 둘러싸인 경계를 위해
    Mazecol += 2;

    int **maze = (int **)malloc(sizeof(int*) * Mazerow); // 2차원 동적 배열 -> 이중포인터
    int **mark = (int **)malloc(sizeof(int*) * Mazerow);
    for (int i = 0; i < Mazerow; i++) {
        maze[i] = (int *)malloc(sizeof(int) * Mazecol); // 포인터로 2차원 아래의 1차원 할당
        mark[i] = (int *)malloc(sizeof(int) * Mazecol);
    }

    for (int i = 0; i <= Mazerow - 1; i++) {
        for (int j = 0 ; j <= Mazecol - 1; j++) {
            mark[i][j] = 0; // mark의 전체를 0으로 초기화
            if (i == 0 || j == 0 || i == Mazerow - 1 || j == Mazecol - 1) {
                maze[i][j] = 1; // maze의 경계를 1로 설정
                
            }
            else {
                fscanf(file, "%d", &maze[i][j]); // 경계를 제외한 부분에 미로 입력
            }
        }
    }

    path(maze, mark, Mazerow, Mazecol);

    for (int i = 0; i < Mazerow; i++) {
        for (int j = 0; j < Mazecol; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
    printf("========\n");
    for (int i = 0; i < Mazerow; i++) {
        for (int j = 0; j < Mazecol; j++) {
            printf("%d ", mark[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < Mazerow; i++) {
        free(maze[i]);
        free(mark[i]);
    }
    free(maze);
    free(maze);
}

void setOffset() { // 이동방향을 미리 설정
    int vert[9] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int horiz[9] = {0, 1, 1, 1, 0, 0, -1, -1, -1};
    for (int i = 0; i < 8; i++) {
        move[i].vert = vert[i];
        move[i].horiz = horiz[i];
    }
}
void path(int **maze, int **mark, int MazeRow, int MazeCol) {
    int row, col, nextRow, nextCol, dir;
    int found = 0;
    element position; // 현재 위치를 저장할 구조체
    mark[1][1] = 1; top = 0; // 시작 위치와 스택의 top 초기 설정
    // 지나온 길을 저장할 stack에 현재 지점인 1, 1, 1 (row, col, dir) 저장
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 1;
    while(top > -1 && !found) { // 스택이 존재하고, 종점에 도달하지 못했을때
        position = pop(); // position <- stack[prev] (back tracking) 길이 막혔을때 진출하기 전의 위치로 돌아옴(stack의 이전 index를 불러옴으로써)
        // 맨 처음에는 stack의 top값이 -1이 됨
            // 이때는 while문의 조건을 만족한 후의 반복에서 -1이 되므로 정상적으로 반복 진행
            // 그러나 계속해서 길을 찾지못하고 pop()을 통해 stack[top--]으로 top이 -1이 된 후에 while문에 들어오면
                // 그때는 조건을 만족하지 못해 while문을 종료하게됨
        // row, col, dir에 현재 position의 row, col, dir을 저장
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) { // dir을 증가시킴에도 길을 찾지 못하면서, 종점에 도달하지 못했을때
            // 현재 row, col에 각 dir방향으로 진출시켰을때의 움직임 값을 더함
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == MazeRow - 1 && nextCol == MazeCol - 1) { // 다음 위치가 종점이라면
                found = 1;
            }
            else if (maze[nextRow][nextCol] == 0 && mark[nextRow][nextCol] == 0) {
            // 다음 위치가 maze에서 막혀있지 않은 곳이고, mark에서 가지 않았던 곳이라면
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow; col = nextCol; dir = 0;
            }
            else { // 다음으로 가야할 길이 막혀있다면 (maze에서 다음 위치가 1이라면)
                ++dir;
            }
            // printf("%d %d %d %d %d\n\n", row, col, dir, nextRow, nextCol);
        }
    }
    if(found) { // 종점에 도착했다면
        printf("The path is:\n");
        printf("row col\n");
        for (int i = 0; i <= top; i++) {
            printf("%2d%5d\n", stack[i].row, stack[i].col); // 지금까지 저장했던 경로를 스택에서 순차적으로 저장
        }
        printf("%2d%5d\n", row, col);
    }
    else {
        printf("The maze does not have a path\n");
    }
}

element pop() {
    if (top == -1) { // stack이 존재하지 않는 경우
        exit(1);
    }
    // stack이 하나라도 존재한다면
    return stack[top--]; // 가장 상위 stack를 없애고, 이전 stack를 리턴해줌
    // 길을 찾지 못해서 초기 값인 0에서 top--으로 -1이 된 상태에서 while로 들어가면 while이 종료됨
}
void push(element item) {
    if (top >= capacity - 1) { // top이 실질적 스택의 크기인 capacity - 1보다 크거나 같을때
        stackFull();
    }
    stack[++top] = item; // 크기가 충분하다면 stack의 index를 1 증가시키고, 현재 row, col, dir을 저장
}
void stackFull() {
    realloc(stack, 2 * capacity * sizeof(stack));
    capacity *= 2;
}