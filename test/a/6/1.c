#include <stdio.h>

#define MAX_STACK_SIZE 100

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;
element stack[MAX_STACK_SIZE];

typedef struct {
    short int vert;
    short int horiz;
} offsets;
offsets move[8];

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error\n");
    }

    vert[8] = [-1, -1, 0, 1, 1, 1, 0, -1];
    horiz[8] = [0, 1, 1, 1, 0, -1, -1, -1];

    for (int i = 0; i < 8; i++) {
        move[i].vert = vert[i];
        move[i].horiz = horiz[i];
    }
}