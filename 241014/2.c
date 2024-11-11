#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

int top = -1;
int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char postExpr[MAX_EXPR_SIZE];
int ind = 0;
int flag = 1;

void postfix();
void printToken(precedence token);
int eval(); 
precedence getToken(char *symbol, int *n);
precedence pop();
void push(precedence value);

int main() {
    // FILE* file = fopen("in21.txt", "r");
    FILE* file = fopen("in22.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    char ch;
    int i = 0;
    while (fscanf(file, "%c", &ch) != EOF) {
        if (ch != '\n' && ch != ' ') {
            expr[i++] = ch;
        }
    }
    expr[i] = '\0';
    fclose(file);

    postfix();
    printf("%d\n", eval());
}

void postfix() {
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c ", symbol);
            postExpr[ind++] = symbol;
        }
        else if (token == rparen) {
            while (stack[top] != lparen) {
                printToken(pop());
            }
            pop();
        }
        else {
            while(isp[stack[top]] >= icp[token]) {
                printToken(pop());
            }
            push(token);
        }
    }
    while((token = pop()) != eos) {
        printToken(token);
    }
    flag = 0;
    printf("\n");
}

precedence getToken(char *symbol, int *n) {
    if (flag) {
        *symbol = expr[(*n)++];
    }
    else {
        *symbol = postExpr[(*n)++];
    }

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

void printToken(precedence token) {
    switch (token) {
        case plus:
            printf("+ ");
            postExpr[ind++] = '+';
            break;
        case minus:
            printf("- ");
            postExpr[ind++] = '-';
            break;
        case times:
            printf("* ");
            postExpr[ind++] = '*';
            break;
        case divide:
            printf("/ ");
            postExpr[ind++] = '/';
            break;
        case mod:
            printf("%% ");
            postExpr[ind++] = '%';
            break;
        default:
            break;
    }
}

int eval() {
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;
    token = getToken(&symbol, &n);
    while (token != eos) {
        if (token == operand) {
            push(symbol - '0'); // 단일 자릿수의 숫자 처리
        } else {
            op2 = pop();
            op1 = pop();
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
                break;
            default:
                break;
            }
        }
        token = getToken(&symbol, &n);
    }
    return pop();
}

precedence pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

void push(precedence value) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = value;
}
