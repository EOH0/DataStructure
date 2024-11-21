#include <stdio.h>
#include <string.h>

typedef struct record {
    int key;
    char name[20];
    int grade;
} element;

void insertionSort(element a[], int n);
void insert(element e, element a[], int i);

int main() {
    FILE* file = fopen("in2.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);

    element User[100];
    char name[20];
    for (int i = 1; i <= size; i++) {
        fscanf(file, "%d %s %d", &User[i].key, name, &User[i].grade);
        strcpy(User[i].name, name);
    }
    fclose(file);

    insertionSort(User, size);

    for (int i = 1; i <= size; i++) {
        printf("%d %s %d\n", User[i].key, User[i].name, User[i].grade);
    }
}

void insertionSort(element a[], int n) {
    for (int j = 2; j < n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1);
    }
}
void insert(element e, element a[], int i) {
    a[0] = e;
    while(e.key < a[i].key) {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}