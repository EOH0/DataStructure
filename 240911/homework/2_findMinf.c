#include <stdio.h>

int findMin(int n, int min);

int main() {
    FILE* file = fopen("f2.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int num;
    int size;
    int min = 2147483647;
    fscanf(file, "%d", &size);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
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