#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element {
    char key[4];
    int value;
} element;

element* ht;

unsigned int stringToInt(char* key);
element* Search(int k);
int h(int k);
void printHash(element* ht);

int D;

int main() {
    FILE* fileIn = fopen("in.txt", "r");
    FILE* fileSearch = fopen("search.txt", "r");
    if (fileIn == NULL || fileSearch == NULL) {
        return 1;
    }

    scanf("%d", &D);

    ht = (element*)malloc(sizeof(element) * D);

    for (int i = 0; i < D; i++) {
        ht[i].value = 0;
    }

    char key[4];
    int value = 0;
    int hF = 0;

    while (fscanf(fileIn, "%s", key) != EOF) {
        value = stringToInt(key);
        hF = h(value);
        while (ht[hF].value != 0) {
            hF = (hF + 1) % D;
        }
        strcpy(ht[hF].key, key);
        ht[hF].value = value;
    }
    fclose(fileIn);

    char ch[4];
    while (fscanf(fileSearch, "%s", ch) != EOF) {
        int valueToSearch = stringToInt(ch);
        element* find = Search(valueToSearch);
        if (find != NULL) {
            printf("S\n");
        } else {
            printf("E\n");
        }
    }
    fclose(fileSearch);

    printHash(ht);

    return 0;
}

unsigned int stringToInt(char* key) { // 입력받은 문자열을 키값을 구하기 위한 정수로 바꿔주는 과정
    int num = 0;
    while (*key) { // 문자열을 각 하나의 문자로 나눠서 그냥 더해버림
    // 문자열도 그냥 정수에 더해버리면 아스키코드로 나오니까
        num += *key++;
    }
    return num;
}

int h(int k) {
    // 해시 함수 == 입력받은 키를 해시테이블의 크기에 맞춰서 적절한 인덱스로 바꿔주는 과정
    return k % D;
}

element* Search(int k) {
    int homeBucket = h(k);
    int currentBucket = homeBucket; // 검색하는 값의 인덱스 탐색
    // 검색하고자하는 값이 같다면 인덱스도 같기 때문

    while (strlen(ht[currentBucket].key) != 0 && ht[currentBucket].value != k) { // 탐색하고자하는 값을 찾으면 반복 종료
        // 해시테이블에 문자열이 존재하고 && 값이 다를 때
            // 버킷을 해시테이블의 한 저장공간
            // 전체 서랍장 == 해시테이블 => 서랍 == 버킷 => 서랍 속 물건 == 원소
        currentBucket = (currentBucket + 1) % D; // 탐색에 실패했으니까 다음 인덱스로 넘어가서 탐색함
        if (currentBucket == homeBucket) { // 한바퀴 돌아서 다시 처음으로 돌아왔는데도 못 찾았으면 null 리턴
            return NULL;
        }
    }
    if (ht[currentBucket].value == k) { // 다시하면 점검 -> 탐색하고자하는 값이 맞으면
        return &ht[currentBucket]; // 현재 해시테이블 주소 리턴
    }
    return NULL;
}

void printHash(element* ht) {
    for (int i = 0; i < D; i++) {
        printf("%d: ", i);
        if (ht[i].value != 0) {
            printf("%s (%d)", ht[i].key, ht[i].value);
        }
        printf("\n");
    }
}
