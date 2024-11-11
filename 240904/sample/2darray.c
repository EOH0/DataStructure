#include <stdio.h>

void printArray(int arr[5][4]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; i++) {
            printf("%8d", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void fillArray(int arr[5][4]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = (i * 10) + j;
        }
    }
}

int main() {
    int arr[5][4] = { 0 };

    printArray(arr);
    fillArray(arr);
    printArray(arr);
}