#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b);

int main() {
    char* arr[] = { "banana", "apple", "orange", "mango", "lemon" };
    int n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(arr[0]), compare);

    for (int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }
}

// int compare(const void* a, const void* b) {
//     return strcmp(a, b); // strcmp 안에 *는 넣을 수 없다
// }

int compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    // a의 주솟값 => *a인 변수의 주솟값을 구하기 위함 **
    // 역참조 한번해주기 => char**를 strcmp쓰려면 char* 여야만 하므로
    const char* str2 = *(const char**)b;

    return strcmp(str1, str2);
}