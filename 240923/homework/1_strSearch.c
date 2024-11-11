#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequentialSearch(char arr[][4], int n, char target[]);
int iterativeBinarySearch(char arr[][4], int n, char target[]);
int recursiveBinarySearch(char arr[][4], int left, int right, char target[]);

int main() {
    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    char arr[20][4];
    int num; // EOF 판단용 num 특별한 의미는 없음
    int index = 0;
    int count = 0;
    while (fscanf(file, "%d", &num) != EOF) {
        fscanf(file, "%s ", &arr[index]);
        index++;
        count++;
    }

    char target[4];
    scanf("%s", &target);

    int sqS = sequentialSearch(arr, count, target);
    printf("Sequential search result: %c\n", sqS == 1 ? 'S' : 'F');

    int iBS = iterativeBinarySearch(arr, count, target);

    char iBSResult;
    if (iBS != -1) {
        iBSResult = 'S';
    }
    else {
        iBSResult = 'F';
    }
    printf("Iterative search result: %c\n", iBSResult);

    int left = 0; int right = count - 1;
    int rBS = recursiveBinarySearch(arr, left, right, target);
    char rBSResult;
    if (rBS != -1) {
        rBSResult = 'S';
    }
    else {
        rBSResult = 'F';
    }
    printf("Recursive search result: %c\n", rBSResult);

    return 0;
}

int sequentialSearch(char arr[][4], int n, char target[]) { // 순차탐색 = index 0부터 끝까지 전부 탐색함
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i], target) == 0) {
            return 1;
        }
    }
    return 0;
}
int iterativeBinarySearch(char arr[][4], int n, char target[]) { // 일반적인 이진 탐색
    int middle;
    int left = 0; int right = n - 1;

    while(left <= right) {
        middle = (left + right) / 2;
        switch (strcmp(arr[middle], target))
        {
        case -1:
            left = middle + 1;
            break;
        case 0:
            return middle;
        case 1:
            right = middle - 1;
        }
    }

    return -1;
}

int recursiveBinarySearch(char arr[][4], int left, int right, char target[]) {
    // 재귀 이진 탐색
    int middle;
    if (left <= right) {
        middle = (left + right) / 2;
        switch (strcmp(arr[middle], target)) // 문자열의 아스키코드값에 따라 비교
        {
        case -1: // target이 arr[middle]보다 크다
            return recursiveBinarySearch(arr, middle + 1, right, target);
        case 0: // target과 arr[middle]이 같다
            return middle;
        case 1: // target이 arr[middle]보다 작다
            return recursiveBinarySearch(arr, left, middle - 1, target);
        }
    }
    return -1;
}
