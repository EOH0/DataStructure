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

    int left = 0;
    int right = size - 1;
    qsort(Ri, size, sizeof(element), compare);

    for (int i = 0; i < size; i++) {
        printf("이름: %s, 학번: %d, 평균성적: %.2lf\n", Ri[i].name, Ri[i].num, Ri[i].score);
    }
}

int compare (const void * a, const void * b) {
    element *recordA = (element *)a;
    element *recordB = (element *)b;
    return strcmp(recordA->name, recordB->name);
}