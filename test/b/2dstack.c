#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
element *stack;
int capacity = 10;
int top = -1;

void push(element item);
element pop();
void stackEmpty();
void stackFull(); 

int main() {
    stack = (element *)malloc(sizeof(element) * capacity);
    element item;
    char input;
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
        printf("%d ", stack[i]);
    }
}

void push(element item) {
    if (top >= capacity - 1) {
        stackFull();
    }
    stack[++top] = item;
}
element pop() {
    if (top == -1) {
        stackEmpty();
        return stack[top];
    }
    return stack[top--];
}
void stackEmpty() {
    printf("-1 \n");
}
void stackFull() {
    capacity *= 2;
    element* temp = (element *)malloc(sizeof(element) * capacity);
    stack = temp;
}