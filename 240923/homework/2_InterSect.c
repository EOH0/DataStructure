#include <stdio.h>
#include <stdlib.h>

void printIntersect(int* arr1, int size1, int* arr2, int size2);

int main() {
    FILE* file1 = fopen("f2_1.txt", "r");
    FILE* file2 = fopen("f2_2.txt", "r");

    int *arr1 = (int *)malloc(sizeof(int) * 10);
    int *arr2 = (int *)malloc(sizeof(int) * 10);
    int size1 = 0, size2 = 0;

    while (fscanf(file1, "%d", &arr1[size1]) != EOF) {
        size1++;
    }
    fclose(file1);

    while (fscanf(file2, "%d", &arr2[size2]) != EOF) {
        size2++;
    }
    fclose(file2);

    printIntersect(arr1, size1, arr2, size2);
}

void printIntersect(int* arr1, int size1, int* arr2, int size2) {
    // for (int i = 0; i < size1; i++) {
    //     for (int j = 0; j < size2; j++) {
    //         if (arr1[i] == arr2[j]) {
    //             printf("%d ", arr1[i]);
    //         }
    //     }
    // }
    int i = 0, j = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            i++;
        }
        else if (arr1[i] > arr2[j]) {
            j++;
        }
        else {
            printf("%d ", arr1[i]);
            i++;
            j++;
        }
    }
    printf("\n");
}