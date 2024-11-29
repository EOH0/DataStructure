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
    int ind = 1; // 인덱스를 1로 시작 (배열의 첫 번째 요소를 a[1]로 설정)

    while (fscanf(file, "%d", &num) != EOF) {
        a[ind].key = num;
        ind++;
    }
    ind--; // 실제 데이터 개수는 마지막 인덱스
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

    int sorted = radixSort(a, link, max, 10, ind);

    printf("done!\n");
    while (sorted != 0) {
        printf("%d ", a[sorted].key);
        sorted = link[sorted];
    }
    printf("\n");

    return 0;
}

// 특정 자릿수를 반환하는 함수
int digit(element a, int i, int r) {
    int temp = a.key;
    for (int j = 0; j < i; j++) {
        temp /= r;
    }
    return temp % r;
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r], rear[r];
    int i, bin, current, first, last;
    first = 1;
    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;
    for (i = 0; i <= d - 1; i++) { // ???????
    // 1의 자리수 -> 10의 자리수 -> .... 순서가 맞긴한데
    // 예제는 왜 감소 반복
        for (bin = 0; bin < r; bin++) front[bin] = 0;
        for (current = first; current; current = link[current]) {
            bin = digit(a[current], i, r);
            if (front[bin] == 0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
        }
        for (bin = 0; !front[bin]; bin++);
        first = front[bin];
        last = rear[bin];
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
