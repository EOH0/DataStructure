#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_element_SIZE 1000
#define SWAP(a, b, temp) {temp = a; a = b; b = temp;}

typedef struct record {
    char name[50];
    int num;
    double score;
} element;

int compare (const void * a, const void * b);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (file == NULL) {
        printf("file error");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);

    element Ri[MAX_element_SIZE];
    char name[50];
    int num;
    double score;

    for (int i = 0; i < size; i++) {
        fscanf(file, "%s %d %lf", &name, &num, &score);
        strcpy(Ri[i].name, name);
        Ri[i].num = num;
        Ri[i].score = score;
    }

    qsort(Ri, size, sizeof(element), compare);
    // qsort(비교할 배열, 배열의 크기, 배열의 메모리 사용량, 비교함수)
        // 비교함수는 compare로 지정

    for (int i = 0; i < size; i++) {
        printf("이름: %s, 학번: %d, 평균성적: %.2lf\n", Ri[i].name, Ri[i].num, Ri[i].score);
    }
}

int compare (const void *a, const void *b) {
    element *recordA = (element *)a;
    element *recordB = (element *)b;
    return strcmp(recordA->name, recordB->name);
    // 앞에 있는 문자열이 뒤에 있는 문자열보다 크면 1 작으면 -1 같으면 0을 리턴
    // 앞에 있는 문자열이 더 큰 1을 리턴할때만 교환 수행
}