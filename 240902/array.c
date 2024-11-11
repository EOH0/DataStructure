#include <stdio.h>

int sumArray(int num[10], int max) {
    int sum = 0;
    for (int i = 0; i < max; i++) {
        sum += num[i];
    }
    return sum;
}

int averageArray(int num[10], int max);

int main() {
    int max = 10;
    int num[10];
    for (int i = 0; i < max; i++) {
        scanf("%d", &num[i]);
    }
    int sum = sumArray(num, max);
    printf("%d", sum);
    int average = averageArray(num, max);
}