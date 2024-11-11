// 시간복잡도 O(n)
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;
struct node {
    int data;
    nodePointer link;
};

nodePointer newNode(int data){
    nodePointer node = (nodePointer)malloc(sizeof(struct node));
    node->data = data;
    node->link = NULL;

    return node;
}

void insert(nodePointer *first, int num, nodePointer *trail);
void print(nodePointer trail);

int main() {
    FILE* file = fopen("f4.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }

    nodePointer first = (nodePointer)malloc(sizeof(struct node));
    nodePointer trail = (nodePointer)malloc(sizeof(struct node));
    first = NULL;
    trail = first;

    int num;
    while(fscanf(file, "%d", &num) != EOF) {
        insert(&first, num, &trail);
    }
    trail = first;
    
    print(trail);

    while(trail != NULL) {
        nodePointer temp = trail;
        trail = trail->link;
        free(temp);
    }
}
void insert(nodePointer *first, int num, nodePointer *trail) {
    nodePointer temp = (nodePointer)malloc(sizeof(struct node));
    temp->data = num;
    temp->link = NULL;

    if (*first == NULL) {
        *first = temp;
        *trail = *first;
    }
    else {
        (*trail)->link = temp;
        *trail = temp;
    }
}

void print(nodePointer trail) {
    while(trail->link != NULL) {
        printf("%d ", trail->data);
        trail = trail->link;
    }
}