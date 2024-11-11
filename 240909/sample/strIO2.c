#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputStrings(char* strings[], int numStrings);
void printStrings(char* strings[], int numStrings);
void freeStrings(char* strings[], int numStrings);

int main() {
    char* strings[5];

    inputStrings(strings, 5);
    printStrings(strings, 5);
    freeStrings(strings, 5);

    return 0;
}

void inputStrings(char* strings[], int numStrings) {
    char buffer[100];

    for (int i = 0; i < numStrings; i++) {
        printf("문자열 %d 입력: ", i + 1);
        scanf("%99s", buffer);
        strings[i] = (char*)malloc(strlen(buffer) + 1);
        if (strings[i] != NULL) {
            strcpy(strings[i], buffer);
        }
    }
}
void printStrings(char* strings[], int numStrings) {
    printf("입력된 문자열: \n");
    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }
}
void freeStrings(char* strings[], int numStrings) {
    for (int i = 0; i < numStrings; i++) {
        free(strings[i]);
    }
}