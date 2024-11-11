#include <stdio.h>

int fibonacci(int n);

int main() {
    int n;
    scanf("%d", &n);

    int fibo = fibonacci(n);

    printf("%d", fibo);
    // 계산 가능한 최대값 : 46
}

int fibonacci(int n) {
    if (n == 1 || n == 0) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}