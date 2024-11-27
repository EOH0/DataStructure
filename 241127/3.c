#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int key;
} element;

int radixSort(element a[], int link[], int d, int r, int n);
int digit(element a[], int i, int r);

int main() {
    FILE* file = fopen("in3.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    element a[MAX_SIZE];
    int link[MAX_SIZE];

    int num;
    int ind = 0;
    while(fscanf(file, "%d", &num) != EOF) {
        a[ind].key = num;
        ind++;
    }

    radixSort(a, link, ind, ind - 1, ind);
    printf("done!\n");
    for (int i = 0; i < ind; i++) {
        printf("%d ", a[i].key);
    }
}

int digit(element a[], int i, int r) {
    int temp = a[i].key;
    int cnt = 0;
    while(temp > 0) {
        temp /= 10;
        cnt++;
    }
    switch (cnt) {
    case 1:
        return 1;
        break;
    case 2:
        return 10;
        break;
    case 3:
        return 100;
        break;
    default:
        break;
    }
}
int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r];
    int rear[r];
    int i, bin, current, first, last;
    first = 1;
    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;
    for (i = d - 1; i >= 0; i--) { // 왜 자꾸 감소반복을 하지
        for (bin = 0; bin < r; bin++) front[bin] = 0;
        for (current = first; current; current = link[current]) { // records를 queue, bin에 넣음
            bin = digit(a, i, r);
            if (front[bin] == 0) front[bin] = current;
            else link[rear[bin]] = current;
            rear[bin] = current;
        }
        // 첫번째 nonempty queue, bin 찾기
        for (bin = 0; !front[bin]; bin++);
        first = front[bin]; last = rear[bin];
        // 남은 queue 연결
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