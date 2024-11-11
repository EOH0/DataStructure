#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getNum(int num[10000]);
int getMax(int num[10000]);
int getMin(int num[10000]);

int main() {
    FILE* file = fopen("f1.txt", "w");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int arr[10000] = { 0 };
    srand(time(NULL)); 
        // 난수를 만들기 위해 현재 시간을 seed로 초기화
        // 프로그램 기준의 현재 시간은 항상 다르기 때문에 항상 다른 시드에서의 난수 생성 가능
        // time(NULL) 자리에 특정값을 넣으면 고정된 seed로 같은 난수 생성
    for (int i = 0; i < 10000; i++) {
        arr[i] = rand() % 10000 + 1; // 10000 이하의 난수
    }
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);

    int num[10000] = { 0 };
    getNum(num);

    printf("최댓값 = %d\n", getMax(num));
    printf("최솟값 = %d", getMin(num));

    return 0;
}

int getNum(int num[10000]) {
    FILE* file = fopen("f1.txt", "r");

    int one;
    int i = 0;
    while (fscanf(file, "%d", &one) != EOF) {
        num[i] = one;
        i++;
    }

    fclose(file);
}

int getMax(int num[10000]) {
    int max = num[0];
    for (int i = 0; i < 10000; i++) {
        if (max < num[i]) {
            max = num[i];
        }
    }
    return max;
}

int getMin(int num[10000]) {
    int min = num[0];
    for (int i = 0; i < 10000; i++) {
        if (min > num[i]) {
            min = num[i];
        }
    }
    return min;
}
