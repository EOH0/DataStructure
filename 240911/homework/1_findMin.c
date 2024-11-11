#include <stdio.h>

int findMin(int n, int min);

int main() {
    int num;
    int size;
    int min = 2147483647;
    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &num);
        min = findMin(num, min);
    }
    printf("%d", min);

    return 0;
}

int findMin(int n, int min) {
    if (min > n) {
        min = n;
    }

    return min;
}