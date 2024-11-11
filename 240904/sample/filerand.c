#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("output,txt", "w");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int arr[10] = { 0 };
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);

    return 0;
}