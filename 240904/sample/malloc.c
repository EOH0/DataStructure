#include <stdio.h>
#include <stdlib.h>

int* createArray(int size) {
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        return NULL;
    }
    for(int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
    return array;
}
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int size;
    printf("Array size: ");
    scanf("%d", &size);

    int *arr = createArray(size);
    if (arr == NULL) {
        printf("ALloc failed\n");
        return 1;
    }

    printArray(arr, size);
    free(arr);

    return 0;
}