// 시간 복잡도 O(n + m)
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
void compare(nodePointer first1, nodePointer trail1, nodePointer first2, nodePointer trail2);

int main() {
    FILE* file1 = fopen("f4.txt", "r");
    FILE* file2 = fopen("f4_1.txt", "r");
    if (file1 == NULL || file2 == NULL) {
        printf("file error\n");
        return 1;
    }

    nodePointer first1 = (nodePointer)malloc(sizeof(struct node));
    nodePointer trail1 = (nodePointer)malloc(sizeof(struct node));
    first1 = NULL;
    trail1 = first1;

    nodePointer first2 = (nodePointer)malloc(sizeof(struct node));
    nodePointer trail2 = (nodePointer)malloc(sizeof(struct node));
    first2 = NULL;
    trail2 = first2;

    int num;
    while(fscanf(file1, "%d", &num) != EOF) {
        insert(&first1, num, &trail1);
    }
    trail1 = first1;
    while(fscanf(file2, "%d", &num) != EOF) {
        insert(&first2, num, &trail2);
    }
    trail2 = first2;

    print(trail1);
    print(trail2);

    compare(first1, trail1, first2, trail2);

    while(trail1 != NULL) {
        nodePointer temp = trail1;
        trail1 = trail1->link;
        free(temp);
    }
    while(trail2 != NULL) {
        nodePointer temp = trail2;
        trail2 = trail2->link;
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
    printf("\n");
}
void compare(nodePointer first1, nodePointer trail1, nodePointer first2, nodePointer trail2) {
    trail1 = first1;
    trail2 = first2;

    while(trail1->link != NULL && trail2->link != NULL) {
        if (trail1->data < trail2->data) {
            printf("%d ", trail1->data);
            trail1 = trail1->link;
        }
        else if (trail1->data == trail2->data) {
            printf("%d ", trail1->data);
            trail1 = trail1->link; trail2 = trail2->link;
        }
        else if (trail1->data > trail2->data) {
            printf("%d ", trail2->data);
            trail2 = trail2->link;
        }
    }
    while (trail1->link != NULL) {
        printf("%d ", trail1->data);
        trail1 = trail1->link;
    }
    while (trail2->link != NULL) {
        printf("%d ", trail2->data);
        trail2 = trail2->link;
    }
}