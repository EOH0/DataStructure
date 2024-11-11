#include <stdio.h>
#include <stdlib.h>

void readStrings(char strings[][20], int size);
void printStrings(char strings[][20], int size);

int main() {
    char strings[5][20];

    readStrings(strings, 5);
    printStrings(strings, 5);

    return 0;
}

void readStrings(char strings[][20], int size) {
    for (int i = 0; i < size; i++) {
        scanf("%s ", strings[i]);
    }
}
void printStrings(char strings[][20], int size) {
    for (int i = 0; i < size; i++) {
        printf("%19s\n", strings[i]);
    }
}