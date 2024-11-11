#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;

    printf("%d\n", a); // 10
    printf("%d\n", &a); // a 주솟값
    printf("%d\n", p); // a 주솟값
    printf("%d\n", &p); // p 주솟값
    printf("%d\n", *p); // p 주솟값이 가리키는 값 = 10 
}