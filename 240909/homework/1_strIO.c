#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printStrings(char* p[], int n);
void freeMemory(char* p[], int n);

int main() {
    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }
    int size;
    fscanf(file, "%d", &size);

    char* arr[size];
    char buffer[100]; // ? gpt가 했나
    for (int i = 0; i < size; i++) {
        fscanf(file, "%s", &buffer); 
        // arr[i]에 직접 입력을 받으면 단어를 받을때마다 동적할당 해줄 수 없음
            // buffer에 입력을 받아 strlen으로 문자열의 길이를 재고, 그것으로 할당
            // 그 후 arr에 strcpy로 입력해줌
        arr[i] = (char*)malloc(strlen(buffer) + 1);
        strcpy(arr[i], buffer);
    }
    fclose(file);
    
    printStrings(arr, size);
    freeMemory(arr, size);
}

void printStrings(char* p[], int n) { // 이중포인터의 첫번째 주솟값
    for (int i = 0; i < n; i++) {
        printf("%s ", p[i]); // 실제로는 2차원 배열의 역할을 하지만, 문자열을 저장하므로 1차원처럼 사용
    }
}
void freeMemory(char* p[], int n) {
    for (int i = 0; i < n; i++) {
        free(p[i]);
    }
}