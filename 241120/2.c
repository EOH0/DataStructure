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

    for (int i = 1; i <= size; i++) {
        printf("%d %s %d\n", User[i].key, User[i].name, User[i].grade);
    }

    insertionSort(User, size);

    for (int i = 1; i <= size; i++) {
        printf("%d %s %d\n", User[i].key, User[i].name, User[i].grade);
    }
}

void insertionSort(element a[], int n) {
    for (int i = 2; i < n; i++) {
        element temp = a[i];
        insert(temp, a, i - 1);
    }
}
void insert(element e, element a[], int i) {
    // 기본적으로 정렬하려고 가져온 e라는 원소는 배열의 가장 마지막 원소부터 비교하여 들어가기에 적당한 자리를 찾음
    // 또한, 삽입 정렬은 삽입하고자하는 원소의 앞부분은 이미 정렬이 되어있음을 전제로 동작
        // 왜 굳이 뒤에서부터 찾지
        // 삽입하고자 원소는 i번째 원소
        // i번째 원소를 정렬할떄 1 ~ i - 1 번째 원소는 이미 정렬이 끝난 상태
        // 그래서 정렬이 된 부분만 비교해서 원소를 넣음
        // 정렬도 안된 뒷부분을 비교해봤자 하등 쓸모없으니까
        // 1 ~ i - 1 사이의 원소는 크기 순으로 되어 있으므로
        // i - 1부터 1까지 탐색하다가 자신보다 작은 원소가 나오면 그때 삽입
    a[0] = e;
    // a[0]는 빈자리
        // 빈자리에 현재 정렬할 원소를 세팅
    while(e.key < a[i].key) { // 삽입할 원소보다 크면 계속 반복하면서 배열의 앞쪽으로 이동
        a[i + 1] = a[i]; // 자신보다 값이 큰 원소는 배열의 한칸 뒤로 계속 옮김
        // 자신이 들어갈 자리를 미리 확보하면서 들어감
        // 책을 번호 순으로 꽂기 위해서 꽂으려는 책보다 번호가 큰 책을 옆 칸으로 옮기는 작업이랑 같음
        i--;
    }
    // 적당한 위치를 찾았다면
    a[i + 1] = e; // while의 마지막에 실행된 i--를 고려해 i + 1로 해서 삽입
}