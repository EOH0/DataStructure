#include <stdio.h>
#include <string.h>

int sequentialSearch(char arr[][4], int n, char target[]);
int iterativeBinarySearch(char arr[][4], int n, char target[]);
int recursiveBinarySearch(char arr[][4], int n, int left, int right, char target[]);
int compare(int middle, int target);

int main() {
    char arr[20][4];
    int n = 0;

    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int i = 0;
    while (fscanf(file, "%s", &arr[i]) != EOF) {
        i++;
        n++;
    }
    fclose(file);

    for(int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
    char target[4];
    scanf("%s", &target);

    int sS = sequentialSearch(arr, n, target);
    char RsS;
    if (sS >= 0) {
        RsS = 'S';
    }
    else {
        RsS = 'F';
    }

    int iB = iterativeBinarySearch(arr, n, target);
    char RiB;
    if (RiB >= 0) {
        RiB = 'S';
    }
    else {
        RiB = 'F';
    }

    int left = 0;
    int right = n;
    int rB = recursiveBinarySearch(arr, n, left, right, target);
    char RrB;
    if (RrB >= 0) {
        RrB = 'S';
    }
    else {
        RrB = 'F';
    }

    printf("Sequential search result: %c\n", RsS);
    printf("Iterative binary search result: %c\n", RiB);
    printf("Recursive binary search result: %c\n", RrB);
}

int sequentialSearch(char arr[][4], int n, char target[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i], target) == 0) {
            return i;
        }
    }
    return -1;
}
int iterativeBinarySearch(char arr[][4], int n, char target[]) {
    int left = 0;
    int right = n;
    int middle = 0;
    while (left <= right) {
        middle = (left + right) / 2;
        switch (strcmp(arr[middle], target)) {
        case -1: // middle > target
            left = middle + 1;
            break;
        case 0:
            return middle;
        case 1:
            right = middle - 1;
            break;
        }
    }
    return -1;
}
int recursiveBinarySearch(char arr[][4], int n, int left, int right, char target[]) { // 재귀에서는 반복문 X
    int middle = (left + right) / 2;
    if (left <= right) {
        switch (strcmp(arr[middle], target)) {
        case -1: // arr[middle] > target
            recursiveBinarySearch(arr, n, middle + 1, right, target);
            break;
        case 0:
            return middle;
        case 1:
            recursiveBinarySearch(arr, n, left, middle - 1, target);
            break;
        }        
    }
}
