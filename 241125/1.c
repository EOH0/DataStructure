#include <stdio.h>
#include <string.h>

#define MAX_element_SIZE 1000
#define SWAP(a, b, temp) {temp = a; a = b; b = temp;}

typedef struct record {
    char name[50];
    int num;
    double score;
} element;

void quickSort(element a[], int left, int right);

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
    quickSort(Ri, left, right);

    for (int i = 0; i < size; i++) {
        printf("이름: %s, 학번: %d, 평균성적: %.2lf\n", Ri[i].name, Ri[i].num, Ri[i].score);
    }
}

void quickSort(element a[], int left, int right) {
    char pivot[50];
    int i, j;
    element temp;
    if (left < right) {
        i = left;
        j = right + 1;
        strcpy(pivot, a[left].name);
        do {
            do i++; while(strcmp(a[i].name, pivot) < 0);
            do j--; while(strcmp(a[j].name, pivot) > 0);
            if (i < j) SWAP(a[i], a[j], temp);
        } while(i < j);
        SWAP(a[left], a[j], temp);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}