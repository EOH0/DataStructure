#include <stdio.h>
#include <stdlib.h>

void selectionsort(int num[], int size);
void swap(int num[], int i, int min);

int main() {
    FILE* file = fopen("f3.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);

    int *num = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num[i]);
    }

    fclose(file);

    selectionsort(num, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", num[i]);
    }

    return 0;
}

void selectionsort(int num[], int size) { // 0 ~ end -> 1 ~ end 식으로 범위를 줄이며 값을 정렬
    int min;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if(num[j] < num[min]) {
                min = j;
            }
        }
        swap(num, i, min);
    }
}
void swap(int num[], int i, int min) {
    int temp = num[i];
    num[i] = num[min];
    num[min] = temp;
}