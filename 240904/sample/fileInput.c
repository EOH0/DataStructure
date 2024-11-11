#include <stdio.h>

int main () {
    FILE* file = fopen("output,txt", "w");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int arr[] = { 1, 2, 3, 4, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);

    return 0;
}