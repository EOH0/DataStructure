#include <stdio.h>
#include <stdlib.h>

void input(double* arr, int size);
int search(double* arr, int size, double data);
void output(double* arr, int size);

int main() {
    FILE* file = fopen("f2.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }
    int size;
    fscanf(file, "%d", &size);
    double *arr = (double *)malloc(size * sizeof(double)); // *arr[]이 아닌 *arr
    // double *arr[] = (double *)malloc(size * sizeof(double)); 문법적 오류
        // 이중포인터도, 1차원 배열도, 포인터도 안됨

    fclose(file);
    input(arr, size); // arr의 첫번째 주소를 넘겨줌

    output(arr, size);

    free(arr);
}

void input(double* arr, int size) { // arr의 첫번째 주소를 받아옴 => main에서처럼 사용할 수 있다
    FILE* file = fopen("f2.txt", "r");
    int num;
    fscanf(file, "%d", &num);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%lf", &arr[i]);
    }
    fclose(file);
}
int search(double* arr, int size, double data) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == data) {
            return i;
        }
    }
    return -1;
}
void output(double* arr, int size) {
    double data;
    scanf("%lf", &data);

    int index = search(arr, size, data);
    printf("index = %d", index);
}