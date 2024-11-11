#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data; // 노드의 값
    struct Node* next; // 다음 노드의 주소
} Node;

Node* createNode(int data);
void appendNode(Node** head, int data);
void printList(Node* head);
void freeList(Node* head);

int main() {
    Node* head = NULL;
    int newData[] = { 1, 2, 3 };

    for (int i = 0; i < 3; i++) {
        appendNode(&head, newData[i]);
    }

    printList(head);
    freeList(head);

    return 0;
}

Node* createNode(int data) {
    Node* node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void appendNode(Node** head, int data) {
    Node* NewNode = createNode(data);
    if (*head == NULL) { // head는 항상 첫번째 노드
        *head = NewNode;
    }
    else {
        Node *trail = *head; // trail은 head(첫번째 노드)부터
        while(trail->next != NULL) { // 다음 노드가 NULL인 값의 마지막 노드로 이동
            trail = trail->next;
        }
        trail->next = NewNode; 
        // 값의 마지막 노드로 이동했으면 다음 노드인 NULL 자리에 새로운 노드 입력
        // struct의 성질에 따라 자연스럽게 새로운 값과 NULL이 자연스럽게 붙음
    }
}
void printList(Node* head) {
    Node* trail = head;
    while(trail != NULL) {
        printf("%d ", trail->data);
        if (trail != NULL) {
            printf("-> ");
        }
        trail = trail->next;
    }
    if (trail == NULL) {
        printf("NULL");
    }
    printf("\n");
}
void freeList(Node* head) {
    Node* trail;
    while (head != NULL) {
        trail = head;
        head = head->next;
        free(trail);
    }
}