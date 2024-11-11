#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;
int check = 0;
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
}

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    return node;
}
void appendNode(Node** head, int data) {
    Node* node = createNode(data);
    node->data = data;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
    }
    else {
        Node* trail = createNode(data);
        trail = *head;
        while(trail->next != NULL) {
            trail = trail->next;
        }
        trail->next = node; // 바로 노드 붙혀주기
    }
}
void printList(Node* head) {
    Node* trail = head;
    while(trail->next != NULL) {
        printf("%d -> ", trail->data);
        trail = trail->next;
    }
    printf("%d -> NULL", trail->data);
}
void freeList(Node* head) {
    Node* temp = head; // trail말고 원본 free
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
}
