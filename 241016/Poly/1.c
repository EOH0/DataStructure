#include <stdio.h>
#include <stdlib.h>

int check = 0;

typedef struct polyNode *polyPointer;
typedef struct polyNode {
    float coef;
    int expon;
    polyPointer link;
} polyNode;
polyPointer a = NULL, b = NULL;

polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer *ptr);
void erase(polyPointer *ptr);
void print(polyPointer p);

int compare(int a, int b);

int main() {
    FILE* file1 = fopen("in21.txt", "r");
    FILE* file2 = fopen("in22.txt", "r");
    FILE* file3 = fopen("in23.txt", "r");
    FILE* file4 = fopen("in24.txt", "r");
    if (file1 == NULL || file2 == NULL || file3 == NULL || file4 == NULL) {
        printf("file error\n");
        return -1;
    }

    float coef;
    int expon;

    // while (fscanf(file1, "%f %d", &coef, &expon) != EOF) {
    //     attach(coef, expon, &a);
    // }

    // while (fscanf(file2, "%f %d", &coef, &expon) != EOF) {
    //     attach(coef, expon, &b);
    // }

    while (fscanf(file3, "%f %d", &coef, &expon) != EOF) {
        attach(coef, expon, &a);
    }
    while (fscanf(file4, "%f %d", &coef, &expon) != EOF) {
        attach(coef, expon, &b);
    }
    polyPointer result = NULL;

    result = padd(a, b);
    
    print(result);
    
    erase(&a);
    erase(&b);
    erase(&result);

    return 0;
}

void attach(float coefficient, int exponent, polyPointer *ptr) {
    polyPointer temp = (polyPointer)malloc(sizeof(polyNode));
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;
    if (*ptr == NULL) {
        *ptr = temp;
    } else {
        polyPointer current = *ptr;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = temp;
    }
}
polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer c, rear, temp;
    int sum;
    rear = (polyPointer)malloc(sizeof(polyNode));
    c = rear;
    rear->link = NULL;  // rear를 NULL로 초기화

    while(a && b) {
        switch (compare(a->expon, b->expon)) {
        case -1: // a->expon < b->expon
            attach(b->coef, b->expon, &rear);
            b = b->link;
            break;
        case 0: // a->expon == b->expon
            sum = a->coef + b->coef;
            if (sum) attach(sum, a->expon, &rear);
            a = a->link;
            b = b->link;
            break;
        case 1: // a->expon > b->expon
            attach(a->coef, a->expon, &rear);
            a = a->link;
            break;
        }
    }
    for(; a; a = a->link) attach(a->coef, a->expon, &rear);
    for(; b; b = b->link) attach(b->coef, b->expon, &rear);

    temp = c;
    c = c->link;  // 첫 번째 노드 제거
    free(temp);   // 첫 번째 노드 메모리 해제
    return c;    
}
void erase(polyPointer *ptr) {
    polyPointer temp;
    while(*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}
int compare(int a, int b) {
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}
void print(polyPointer p) {
    while (p) {
        printf("%.0f %d ", p->coef, p->expon);
        p = p->link;
    }
    printf("\n");
}
