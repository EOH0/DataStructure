#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b);

int main() {
    char arr[][10] = { "banana", "apple", "orange", "mango", "lemon" };
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(arr[0]), compare);

    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}

int compare(const void* a, const void* b) {
    const char* str1 = (const char*)a;
    const char* str2 = (const char*)b;

    return strcmp(str1, str2);
}