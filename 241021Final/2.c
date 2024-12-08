#include <stdio.h>
#include <stdlib.h>

typedef struct listNode *listPointer;
typedef struct listNode{
    int data;
    listPointer link;
} listNode;

int check = 0;

void insert(listPointer *first, int num, listPointer* trail);
void append(listPointer *first, int input, listPointer* trail);
void printList(listPointer *first, listPointer* trail);

int main() {
    FILE* file = fopen("in1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return -1;
    }

    listPointer first = (listPointer)malloc(sizeof(listPointer));
    listPointer trail = (listPointer)malloc(sizeof(listPointer));
    first = NULL;
    trail = first;
    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, num, &trail);
    }

    printList(&first, &trail);

    int input = 0;
    while(1) {
        scanf("%d", &input);
        if (input == -1) {
            break;
        }
        append(&first, input, &trail);
        printList(&first, &trail);
    }

}

void insert(listPointer *first, int num, listPointer* trail) {
    listPointer temp = (listPointer)malloc(sizeof(listPointer));
    temp->data = num;
    temp->link = NULL;
    if (*first == NULL) {
        *first = temp;
        *trail = temp;
    }
    else {
        (*trail)->link = temp;
        (*trail) = temp;
    }
}
void append(listPointer *first, int input, listPointer *trail) {
    listPointer temp = (listPointer)malloc(sizeof(listNode));
    temp->data = input;
    temp->link = NULL;

    listPointer now = *first;
    listPointer prev = NULL;

    // 여기까진 1.c랑 동일
    if (now == NULL || now->data > input) { // now->data == input 경우를 else에서 처리하도록 수정
        temp->link = now;
        *first = temp;
        return;
    }
    while (now != NULL && now->data <= input) {
        if (now->data == input) { // 만약 현재 노드의 데이터가 입력 데이터와 같다면
            if (prev == NULL) { // prev가 NULL이다 -> 삭제될 데이터가 first이다
                *first = now->link; // first를 현재 노드의 다음 노드로 넘김
            } else { // 삭제할 데이터가 노드의 중간이나 끝에 있다 (now 노드가 삭제할 데이터임)
                // 삭제할 데이터가 노드의 중간에 있다 -> prev의 link가 now 노드의 link로 연결
                // 삭제할 데이터 노드의 끝에 있다 -> prev의 link는 now의 link인 NULL로 연결
                prev->link = now->link;
            }
            free(now); // 삭제한 노드 free
            return; // 함수 종료 아래는 실행하지 않음
        }
        prev = now; // 삭제할 값이 아니면 현재 노드를 prev에 저자하고
        now = now->link; // 현재 노드를 다음으로 넘김
    }

    if (temp->link == NULL) { // list를 다 돌았음에도 삭제할 값을 찾지 못했거나 
    // 중간에 삭제할 데이터와 같은 값을 찾지 못하고 큰 수가 나와서 while이 종료되었을떄
        *trail = temp; // 현재 위치에 저장
    }
}


void printList(listPointer *first, listPointer* trail) {
    *trail = *first;
    while(*trail != NULL) {
        printf("%d ", (*trail)->data);
        *trail = (*trail)->link;
    }
    printf("\n");
}