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
    int ind = 0; // 인덱스를 0으로 시작 (배열의 첫 번째 요소부터)

    // 파일로부터 숫자 읽기
    while(fscanf(file, "%d", &num) != EOF) {
        a[ind].key = num;
        ind++;
    }
    fclose(file);

    int max = 0; // 최대 몇 자리인지
    for (int i = 0; i < ind; i++) {
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

    for (int i = 0; i < ind; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");

    int front = radixSort(a, link, max, 10, ind);  // 포인터 수정

    printf("done!\n");
    for (int i = 0; i < ind; i++) {
        printf("%d ", a[i].key);
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
    for(i = 1; i < n; i++) link[i] = i+1;
    link[n] = 0;
    for(i=d-1; i >=0; i--) {
        for(bin = 0; bin < r; bin++) front[bin] = 0;
        for(current = first; current; current = link[current]) {/* put records into queues/bins */
            bin = digit(a[current], i, r);
            if(front[bin] == 0) front[bin] = current;
            else link[ rear[bin] ] = current;
            rear[bin] = current;
        }
            /* find first nonempty queue/bin */
            for (bin= 0; !front[bin]; bin++);
            first= front[bin]; last= rear[bin];
            /* concatenate remaining queues */
            for(bin++; bin < r; bin++) {
                if(front[bin]){
                    link[last] = front[bin];
                    last = rear[bin];
                }
            }
        link[last] = 0;
    }
    return first;
}