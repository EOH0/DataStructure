#include <stdio.h>
#include <stdlib.h>

int binsearch(int list[], int searchnum, int left, int right);
int compare(int list, int searchnum);

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

    int num;
    scanf("%d", &num);

    int left = 0;
    int right = size;
    int index = binsearch(arr, num, left, right);

    if (index >= 0) {
        printf("S (%d)\n", index);
    }
    else {
        printf("F (%d)\n", index);
    }
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }
}

int binsearch(int list[], int searchnum, int left, int right) {
    int middle = 0;
    int flag = 1;
    while(left <= right) {
        middle = (left + right) / 2;
        switch (compare(list[middle], searchnum)) {
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

int compare(int list, int searchnum) {
    if (list > searchnum) {
        return 1;
    }
    else if (list == searchnum) {
        return 0;
    }
    else if (list < searchnum) {
        return -1;
    }
}