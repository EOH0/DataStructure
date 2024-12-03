#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAX_LENGTH 5
#define RADIX 27 // 'a' ~ 'z' + 빈 자리

typedef struct {
    char key[MAX_LENGTH + 1];
} element;

int radixSort(element a[], int link[], int d, int r, int n);
int digit(const element *a, int i);

int main() {
    FILE *file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    element a[MAX_SIZE];
    int link[MAX_SIZE];
    int ind = 1;

    while (fscanf(file, "%s", a[ind].key) != EOF) {
        ind++;
    }
    ind--; // 실제 데이터 개수는 마지막 인덱스
    fclose(file);

    int max = 0;
    for (int i = 1; i <= ind; i++) {
        int length = strlen(a[i].key);
        if (length > max) {
            max = length;
        }
    }

    int sorted = radixSort(a, link, max, RADIX, ind);

    printf("Sorted words:\n");
    while (sorted != 0) {
        printf("%s\n", a[sorted].key);
        sorted = link[sorted];
    }

    return 0;
}

int digit(const element *a, int i) { // 'a' -> 0, 'b' -> 1, ..., 'z' -> 25, 빈 자리 -> 26
    int len = strlen(a->key);
    if (i < len) {
        return a->key[len - i - 1] - 'a';
    } else {
        return 26; // 빈 자리 수
    }
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r], rear[r];
    int current, bin, first, last;

    first = 1;
    for (int i = 1; i < n; i++) {
        link[i] = i + 1;
    }
    link[n] = 0;

    for (int i = d - 1; i > 0; i--) {
        for (bin = 0; bin < r; bin++) {
            front[bin] = 0;
            rear[bin] = 0;
        }

        for (current = first; current; current = link[current]) { // 연결 리스트를 따라가며 단어를 버킷에 배치
            bin = digit(&a[current], i);
            if (front[bin] == 0) {
                front[bin] = current;
            } else {
                link[rear[bin]] = current;
            }
            rear[bin] = current;
            
        }

        first = 0; // 버킷을 다시 연결하여 새로운 리스트 생성
        for (bin = 0; bin < r; bin++) {
            if (front[bin]) {
                if (first == 0) {
                    first = front[bin];
                } else {
                    link[last] = front[bin];
                }
                last = rear[bin];
            }
        }
        link[last] = 0; // 마지막 노드의 링크는 0
        // current = first; 진행상황체크
        // while (current) {
        //     printf("%s -> ", a[current].key);
        //     current = link[current];
        // }
        // printf("NULL\n");
    }

    

    return first;
}
