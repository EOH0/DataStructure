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
    for (int i = front + 1; i <= rear; i++) { // 애초에 순환 큐의 시작은 queue[front + 1]부터임 (front = -1이니까)
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
    printf("%d ", queue[front + 1]); // 기본적으로 queue[front]는 항상 빈공간이니까 그 다음 위치를 활용
    front = (front + 1) % capacity;
    return queue[front];
}
void queueFull() {
    element* newQueue = (element *)malloc(2 * capacity * sizeof(element)); // queueFull()이 호출될때 이미 newQueue의 크기는 기존 크기의 두배임
    int start = (front + 1) % capacity;
    if (start < 2) { // 원형큐에서 큐 내의 값이 범위를 지나지 않았을때
        copy(queue + start, queue + start + capacity - 1, newQueue);
        // 기존 원형 큐의 시작, 기존 원형 큐의 끝, 기존 큐를 대체할 새로운 큐를 인자로 넘김
    }
    else { // 원형 큐 내의 값이 범위를 지나 둘로 쪼개졌을때 둘을 이어주기 위해 두번 카피
        copy(queue + start, queue + capacity, newQueue);
        copy(queue, queue + rear + 1, newQueue + capacity - start);
    }

    // 카피 다 하고 front, rear, capacity 재설정
    front = 2 * capacity - 1;
    rear = capacity - 2;
    capacity *= 2;
    free(queue); // 기존 큐 삭제하고
    queue = newQueue; // global variable인 queue에 덮어씌우기
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

// I 0 I 2 I 9 D D I 5 I 8 F