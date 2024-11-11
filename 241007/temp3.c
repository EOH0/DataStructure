#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;
int rear = -1;
int front = -1;
int capacity = 5; // capacity 초기값 문제?
element *queue;

void addq(element item);
element deleteq();
void queueFull();
void queueEmpty();
void copy(element *start, element *end, element *PrevQueue);

int main() {
    queue = (element *)malloc(sizeof(element) * capacity);
    char input;
    element item;
    while(input != 'F') {
        scanf("%c", &input);
        switch (input) {
            case 'I':
                scanf("%d", &item.key);
                addq(item);
                break;
            case 'D':
                deleteq();
                break;
            case 'F':
                break;
        }
    }
    for (int i = 0; i <= rear; i++) {
        printf("%d ", queue[i].key);
    }

    free(queue);
}

void addq(element item) {
    if ((rear + 1) % capacity == front) { // 큐가 가득 찼는지 확인
        queueFull();
    }
    rear = (rear + 1) % capacity; // rear 증가 후 아이템 추가 + 순환의 기능
    queue[rear] = item;
}
element deleteq() {
    if (front == rear) {
        queueEmpty();
        return queue[rear];
    }
    front = (front + 1) % capacity;
    return queue[front];
}
void queueFull() {
    element* newQueue = (element *)malloc(2 * capacity * sizeof(element)); // queueFull()이 호출될때 이미 newQueue의 크기는 기존 크기의 두배임
    int start = (front + 1) % capacity;
    if (start < 2) {
        copy(queue + start, queue + start + capacity - 1, newQueue);
        // 기존 원형 큐의 시작, 기존 원형 큐의 끝, 기존 큐를 대체할 새로운 큐를 인자로 넘김
    }
    else {
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacity - start);
    }
    front = 2 * capacity - 1;
    rear = capacity - 2; // queue size = capacity - 1
    capacity *= 2;
    free(queue);
    queue = newQueue;
}
void queueEmpty() {
    printf("-1 ");
}

void copy(element *start, element *end, element *newQueue) { // 각 인자는 각 element의 메모리 주소
    while (start != end) { // 값의 시작 주소값이 값의 마지막 값과 다른 동안
        *newQueue = *start; // 새로운 큐의 첫번째에 기존의 start에 위치한 값을 저장
        newQueue++; // 다음 값을 저장할 새로운 큐의 다음 주소로 이동
        start++; // 기존 큐에 있던 다음 값을 저장하기 위해
    }
}
