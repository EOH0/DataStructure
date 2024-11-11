#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("f3.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);
    int* arr = (int *)malloc(sizeof(int) * size);
    
    int i = 0;
    while (fscanf(file, "%d", &arr[i]) != EOF) {
        i++;
    }
    fclose(file);

    for(int i = 0; i < size; i++) {
        for(int j = i; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}