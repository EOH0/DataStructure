#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b);

int main() {
    int arr[] = {4, 2, 5, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n , sizeof(int), compare);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}