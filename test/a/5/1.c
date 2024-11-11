#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
element *stack;
int top = -1;
int capacity = 1;

void push(element item);
void stackFull();
element pop();
void stackEmpty();

int main() {
    stack = (element *)malloc(sizeof(element) * capacity);
    char input = 0;
    element item;
    while (input != 'F') {
        scanf("%c", &input);
        switch (input) {
        case 'I':
            scanf("%d", &item.key);
            push(item);
            break;
        case 'D':
            pop();
        case 'F':
            break;
        }
    }
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i].key);
    }
}

void push(element item) {
    if (top >= capacity) {
        stackFull();
    }
    stack[++top] = item;
}
void stackFull() {
    capacity *= 2;
    element* newStack = (element *)realloc(stack, capacity);
    stack = newStack;
}
element pop() {
    if (top == -1) {
        printf("stack Empty");
    }
    return stack[top--];
}