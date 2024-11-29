#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

int radixSort(element a[], int link[], int d, int r, int n);
int digit(element a, int i, int r);

int main() {
    FILE* file = fopen("in3.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    element a[MAX_SIZE];
    int link[MAX_SIZE];
    int num;
    int ind = 1; // 인덱스를 0으로 시작 (배열의 첫 번째 요소부터)

    // 파일로부터 숫자 읽기
    while(fscanf(file, "%d", &num) != EOF) {
        a[ind].key = num;
        ind++;
    }
    ind--;
    fclose(file);

    int max = 0; // 최대 몇 자리인지
    for (int i = 1; i <= ind; i++) {
        int temp = a[i].key;
        int digits = 0;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }
        if (digits > max) {
            max = digits;
        }
    }

    // 입력 배열 출력
    for (int i = 1; i <= ind; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");

    // radixSort 함수 호출 및 반환 값 저장
    int sortedStart = radixSort(a, link, max, 10, ind);

    // 정렬 결과 출력
    printf("done!\n");
    int current = sortedStart;
    while (current != 0) {
        printf("%d ", a[current - 1].key);
        current = link[current];
    }
    printf("\n");

    return 0;
}

// 특정 자릿수를 반환하는 함수
int digit(element a, int i, int r) {
    int temp = a.key;
    printf("%d %d %d\n", temp, i, r);
    for (int j = 0; j < i; j++) {
        temp /= r;
    }
    return temp % r;
}
int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r], rear[r];
    int i, bin, current, first, last;
    first = 1;
    for(i = 1; i < n; i++) link[i] = i+1;
    link[n] = 0;
    for (i = d - 1; i >= 0; i--) {
        for (bin = 0; bin < r; bin++) front[bin] = 0;
        for (current = first; current; current = link[current]) {
            bin = digit(a[current - 1], i, r);
            if (front[bin] == 0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
        }
        for (bin = 0; !front[bin]; bin++);
        first = front[bin]; last = rear[bin];
        for (bin++; bin < r; bin++) {
            if (front[bin]) {
                link[last] = front[bin];
                last = rear[bin];
            }
        }
        link[last] = 0;
    }

    return first;
}