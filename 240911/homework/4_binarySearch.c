#include <stdio.h>
#include <stdlib.h>

void selectionsort(int num[], int size);
void swap(int num[], int i, int min);
int binsearch(int num[], int searchnum, int left, int right);
int compare(int middle, int searchnum);

int main() {
    char fileName[100];
    scanf("%s", &fileName);

    // char *fileName; 
    // scanf("%s", fileName);

    FILE* file = fopen(fileName, "r");
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
    
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", num[i]);
    // }
    // printf("\n");
    
    int searchnum;
    scanf("%d", &searchnum);

    int left = 0, right = size - 1;
    int binsearchValue = binsearch(num, searchnum, left, right);
    if (binsearchValue != -1) {
        printf("S (%d)", binsearchValue);
    }
    else {
        printf("F (-1)");
    }

    return 0;
}

void selectionsort(int num[], int size) {
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

int binsearch(int num[], int searchnum, int left, int right) {
    // 탐색할 배열은 이미 정렬이 되어있어야함
    
    // 검색할 값과 배열의 중간값을 비교
    // 검색할 값이 배열의 중간값보다 작으면 right를 중간값의 index로 놓고 다시 중간값을 구해 탐색
    // 검색할 값이 배열의 중간값과 같으면 그대로 중간값의 index 리턴
    // 검색할 값이 배열의 중간값보다 크면 left를 중간값의 index로 놓고 다시 중간값을 구해 탐색
    int middle;
    while(left <= right) {
        middle = (left + right) / 2;
        switch (compare(num[middle], searchnum)) {
        case -1:
            left = middle + 1;
            break;
        case 0:
            return middle;
        case 1:
            right = middle - 1;
        default:
            break;
        }
    }
    return -1;
}

int compare(int middle, int searchnum) {
    if (middle < searchnum) {
        return -1;
    }
    else if (middle == searchnum) {
        return 0;
    }
    else {
        return 1;
    }
}