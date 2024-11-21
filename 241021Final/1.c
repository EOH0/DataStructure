#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
    int data;
    listPointer link;
};

void insert(listPointer *first, int num, listPointer* trail);
void append(listPointer *first, int input);
void printList(listPointer *first, listPointer* trail);

int main() {
    FILE* file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return -1;
    }

    listPointer first = (listPointer)malloc(sizeof(listPointer)); // head의 역할로 항상 첫번째 노드를 가리킴
    listPointer trail = (listPointer)malloc(sizeof(listPointer));
    // trail은 insert에서 항상 마지막에 노드를 입력하기 위해 마지막 노드의 위치 저장
    first = NULL; // 초기엔 아무것도 없기 때문에 NULL로 지정
    trail = first; // trail은 처음엔 first를 따라감
    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, num, &trail); // first와 trail을 계속해서 바꿔주기 위해 주솟값 전달
    }

    printList(&first, &trail);

    int input = 0;
    while(1) {
        scanf("%d", &input);
        if (input == -1) {
            break;
        }
        append(&first, input);
        printList(&first, &trail);
    }
}

void insert(listPointer *first, int num, listPointer* trail) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer)); // 노드 입력을 위한 temp노드
    temp->data = num;
    temp->link = NULL;
    if (*first == NULL) { // 현재 linkedlist에 아무것도 없다면
        *first = temp; // first는 temp
        *trail = temp; // trail 또한 temp
    }
    else {
        (*trail)->link = temp; // trail은 계속해서 마지막이므로 현재 linkedlist에 무언가가 있다면 그것의 link에 temp 저장
        (*trail) = temp; // trail은 가장 마지막에 있을 temp가 됨
    }
}
void append(listPointer *first, int input) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer)); // 입력받은 data가 있는 temp 노드
    listPointer prev = (listPointer)malloc(sizeof(listPointer)); // temp 노드가 중간에 있을 경우 이전 노드와 link를 해줄 때 필요한 노드
    listPointer now = (listPointer)malloc(sizeof(listPointer)); // 탐색을 할때 사용할 노드

    now = *first; // 탐색은 first부터
    prev = NULL; // first의 prev는 NULL
    temp->data = input;
    temp->link = NULL;
    
    if (now == NULL || now->data >= input) { // now가 첫번째이거나 input이 가장 작을때
        temp->link = now; // 현재 입력받은 노드의 다음이 first
        *first = temp; // first는 temp가 됨
    }
    else {
        while (now != NULL && now->data < input) { // now를 linkedlist의 끝까지 탐색하는 동안 입력데이터보다 큰 값이 안 나올때 까지
            prev = now;
            now = now->link;
        }
        // 이때 입력데이터가 linklist내에서 가장 크거나 temp의 다음 노드가 입력데이터보다 큼 (while 반복 조건)
        temp->link = now; 
        // temp가 가장 큰 경우 now는 NULL이므로 가장 마지막 노드에 제대로 자리를 잡음
        // temp보다 now가 클 경우 temp->link에 now가 연결되므로 적절한 선언
        prev->link = temp;
        // prev는 언제나 temp 이전에 위치
    }
}
void printList(listPointer *first, listPointer* trail) {
    *trail = *first; // 현재 위치를 first로 초기화
    while(*trail != NULL) { // 마지막 노드까지 탐색
        printf("%d ", (*trail)->data);
        *trail = (*trail)->link;
    }
    printf("\n");
}