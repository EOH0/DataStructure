#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int top = -1;
int stack[MAX_STACK_SIZE]; // global stack
char expr[MAX_EXPR_SIZE]; // global input string (a postfix expression)

int eval(); 
precedence getToken(char *symbol, int *n);
precedence pop();
void push(char value);

int main() {
    // char arr[9] = {'5', '1', '2', '+', '4', '*', '+', '3', '-'}; // char 배열
    char arr[10] = "512+4*+3-"; // 문자열
    for (int i = 0; i < 10; i++) {
        expr[i] = arr[i];
    }

    printf("%d", eval());

}

int eval() {
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    token = getToken(&symbol, &n);
    while (token != eos) {
        if (token == operand) { // 연산자가 아닐 경우
            push(symbol - '0'); // char to int
        }
        else {
            op2 = pop(); op1 = pop(); // 
            switch (token) {
            case plus:
                push(op1 + op2);
                break;
            case minus:
                push(op1 - op2);
                break;
            case times:
                push(op1 * op2);
                break;
            case divide:
                push(op1 / op2);
                break;
            case mod:
                push(op1 % op2);
            }
        }
        token = getToken(&symbol, &n);
    }
    return pop(); // 연산 결과;
}
precedence getToken(char *symbol, int *n) {
    *symbol = expr[(*n)++];

    switch (*symbol) {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}

precedence pop() {
    if (top == -1) {
        exit(1);
    }
    return stack[top--];
}
void push(char value) {
    stack[++top] = value;
}