#define MAX_STACKS 10

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
typedef struct stack *stackPointer;
struct stack {
    element data;
    stackPointer link;
};
stackPointer top[MAX_STACKS] = { NULL };

void push(int i, element item);
element pop(int i);
void stackEmpty();

int main() {
    element item;
    
    // 스택 0에 3개의 요소를 push
    for (int j = 1; j <= 3; j++) {
        item.key = j * 10;
        printf("Push %d to stack 0\n", item.key);
        push(0, item);
    }

    // 스택 1에 2개의 요소를 push
    for (int j = 1; j <= 2; j++) {
        item.key = j * 20;
        printf("Push %d to stack 1\n", item.key);
        push(1, item);
    }

    // 스택 0에서 pop
    printf("Pop from stack 0: ");
    for (int j = 0; j < 3; j++) {
        item = pop(0);
        printf("%d ", item.key);
    }
    printf("\n");

    // 스택 1에서 pop
    printf("Pop from stack 1: ");
    for (int j = 0; j < 2; j++) {
        item = pop(1);
        printf("%d ", item.key);
    }
    printf("\n");

    // 비어있는 스택에서 pop 시도 (오류 메시지 출력 확인)
    printf("Attempt to pop from empty stack 2:\n");
    pop(2);

    return 0;
}

void push(int i, element item) {
    stackPointer temp = (stackPointer)malloc(sizeof(struct stack));
    temp->data = item;
    temp->link = top[i];
    top[i] = temp;
}

element pop(int i) {
    stackPointer temp = top[i];
    element item;
    if (!temp) {
        stackEmpty();
        item.key = -1; // 오류 처리를 위해 -1로 설정
        return item;
    }
    item = temp->data;
    top[i] = temp->link;
    free(temp);
    return item;
}

void stackEmpty() {
    printf("Stack is empty\n");
}
