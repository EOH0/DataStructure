#include <stdio.h>
#include <string.h>

int checkL = 0;
int checkR = 0;

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

    for (int i = 0; i < size; i++) {
        printf("이름: %s, 학번: %d, 평균성적: %.2lf\n", Ri[i].name, Ri[i].num, Ri[i].score);
    }
    printf("=========\n");
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
        // 인덱스를 반으로 나누고 전달, 반으로 나누고 전달하다가 왼쪽 인덱스가 오른쪽을 넘어가면 넘어감
        // 조건문으로 시행하기 때문에 종료조건이 따로 필요하지 않음
            // 조건에 안맞으면 재귀가 실행이 안됨
        i = left;
        j = right + 1;
        strcpy(pivot, a[left].name); // pivot은 주어진 구간의 가장 왼쪽 끝 요소
        do { // 구간을 두 구간으로 나누기 위한 과정
            // pivot을 기준으로 범위를 줄여나감
            do { 
                i++;
            } while (strcmp(a[i].name, pivot) < 0);
            // 현재 인덱스가 가리키는 이름이 pivot보다 작으면
            // 가장 왼쪽에서 오른쪽으로 한칸 옮김
                // 그러다가 pivot보다 큰 이름이 나오면 반복 종료
                // 이때 pivot보다 큰 이름이 교환할 이름 
            do {
                j--;
            } while (strcmp(a[j].name, pivot) > 0);
            // 현재 인덱스가 가리키는 이름이 pivot보다 크면0
            // 가장 오른쪽에서 왼쪽으로 한칸 옮김
                // 그러다가 piviot보다 작은 이름이 나오면 반복 종료
                // 이 pivot보다 작은 이름이 교환할 이름
            if (i < j) {
                // pivot보다 큰 이름이 작은 이름보다 왼쪽에 있으면 안되니까
                // 두 이름의 위치를 바꿔줌
                    // 큰 이름이 작은 이름보다 오른쪽에 있으면 굳이 안바꿔도 됨
                SWAP(a[i], a[j], temp);
            }
        } while (i < j);
        // 가장 왼쪽에 있는 거랑 pivot보다 작은거 a[j]랑 바꿔줌
        // pivot을 기준으로 크기를 비교
        // 가장 바깥 do while문의 조건으로 인해 do while이 끝난 상태는 i가 j보다 큰 상태
            // 이 상태는 배열을 전부 돈 상태
            // 근데 이 상태에서 a[j]는 pivot보다 작은거로 세팅되어있음
        // 즉, 배열에서 가장 왼쪽에 있는거랑 그거보다 작은거 교환하는 거임
        SWAP(a[left], a[j], temp);

        // 왼쪽 오른쪽 파티션 정렬 재귀로 해주기
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}