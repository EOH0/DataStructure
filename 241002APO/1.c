#include <stdio.h>
#include <stdlib.h>

// #define MALLOC(p,s) \
//     if (!(p = malloc(s))) { \
//         fprintf(stderr, "Insufficient memory"); \
// 		exit(EXIT_FAILURE); \
//     }

// #define REALLOC(p, s) \
//     if (!(p = realloc(p, s))) { \
//         fprintf(stderr, "Insufficient Memory"); \
//         exit(EXIT_FAILURE); \
//     }

typedef struct {
    int key;
} element;
element* stack;
int capacity = 1;
int top = -1;

void push(element item);
void stackFull();
element pop();
void stackEmpty();

int main() {
    // MALLOC(stack, sizeof(*stack));
    stack = (element *)malloc(sizeof(element) * capacity);
    char input;
    element item;
    while(input != 'F') {
        scanf("%c", &input);
        switch (input) {
            case 'I':
                scanf("%d", &item.key);
                push(item);
                break;
            case 'D':
                pop();
                break;
            case 'F':
                break;
        }
    }
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i].key);
    }
}
void push(element item) {
    if (top >= capacity - 1) {
        stackFull();
    }
    stack[++top] = item;
}
void stackFull() {
    // REALLOC(stack, 2 * capacity * sizeof(*stack));
    // realloc 할때 temp로 새로운 크기의 배열 할당 후 stack에 다시 입력해주기
    element *temp = realloc(stack, 2 * capacity * sizeof(element));
    capacity *= 2;
    stack = temp;
}
element pop() {
    if (top == -1) {
        stackEmpty();
        return stack[top];
    }
    return stack[top--];
}
void stackEmpty() {
    printf("Stack empty\n");
}
// I 0 I 2 I 9 D D I 5 F