#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printStrings(char* p[], int n);
int compare(const void* a, const void* b);
void freeMemory(char* p[], int n);

int main() {
    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }
    int size;
    fscanf(file, "%d", &size);

    char** arr;
    arr = (char **)malloc(sizeof(char) * 100);
    char buffer[100];
    for (int i = 0; i < size; i++) {
        fscanf(file, "%s", &buffer);
        arr[i] = (char*)malloc(strlen(buffer) + 1);
        strcpy(arr[i], buffer);
    }
    fclose(file);
    
    printStrings(arr, size);
    freeMemory(arr, size);
}

void printStrings(char* p[], int n) {
    qsort(p, n, sizeof(p[0]), compare);
    for (int i = 0; i < n; i++) {
        printf("%s ", p[i]);
    }
}
int compare(const void* a, const void* b) { // 어떤 자료형도 받을 수 있게 하기 위해 void 포인터로 지정
    char *str1 = *(char **)a; // char** 형태로 변환했던 변수를 다시 역참조하여 char*형태로 만들어 줌
    char *str2 = *(char **)b;

    return strcmp(str1, str2);

    // return strcmp((const char*)a, (const char*)b); strcmp()의 arguments는 char*형이어야 함
}
void freeMemory(char* p[], int n) {
    for (int i = 0; i < n; i++) {
        free(p[i]);
    }
    free(p);
}
