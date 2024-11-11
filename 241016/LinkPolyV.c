#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode *polyPointer;
struct polyNode {
    float coef;
    int expon;
    polyPointer link;
};
polyPointer a = NULL, b = NULL;

polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer ptr);  // 값으로 ptr 넘기기
void erase(polyPointer ptr);  // 값으로 ptr 넘기기
void printPoly(polyPointer p);

int compare(int a, int b);

int main() {
    polyPointer result = NULL;
    
    // 다항식 a를 정의 (예시: 3x^4 + 2x^2 + 1)
    attach(3.0, 4, a);
    attach(2.0, 2, a);
    attach(1.0, 0, a);
    
    // 다항식 b를 정의 (예시: 4x^3 + 2x^2)
    attach(4.0, 3, b);
    attach(2.0, 2, b);
    
    // 다항식 덧셈
    result = padd(a, b);
    
    // 결과 출력
    printf("Resultant Polynomial: ");
    printPoly(result);
    
    // 메모리 해제
    erase(a);
    erase(b);
    erase(result);

    return 0;
}

polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer c, rear, temp;
    int sum;
    rear = (polyPointer)malloc(sizeof(struct polyNode));  // 크기 수정
    c = rear;
    rear->link = NULL;  // rear를 NULL로 초기화

    while(a && b) {
        switch (compare(a->expon, b->expon)) {
        case -1: // a->expon < b->expon
            attach(b->coef, b->expon, rear);
            b = b->link;
            break;
        case 0: // a->expon == b->expon
            sum = a->coef + b->coef;
            if (sum) attach(sum, a->expon, rear);
            a = a->link;
            b = b->link;
            break;
        case 1: // a->expon > b->expon
            attach(a->coef, a->expon, rear);
            a = a->link;
            break;
        }
    }
    for(; a; a = a->link) attach(a->coef, a->expon, rear);
    for(; b; b = b->link) attach(b->coef, b->expon, rear);

    rear->link = NULL;
    temp = c;
    c = c->link;  // 첫 번째 노드 제거
    free(temp);   // 첫 번째 노드 메모리 해제
    return c;    
}

void attach(float coefficient, int exponent, polyPointer ptr) {
    polyPointer temp = (polyPointer)malloc(sizeof(struct polyNode));  // 크기 수정
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;
    if (ptr == NULL) {
        ptr = temp;  // 처음 노드를 설정
    } else {
        ptr->link = temp;  // 새로운 노드를 연결
    }
    ptr = temp;  // 포인터를 끝으로 이동
}

void erase(polyPointer ptr) {
    polyPointer temp;
    while(ptr) {
        temp = ptr;
        ptr = ptr->link;
        free(temp);
    }
}

int compare(int a, int b) {
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

void printPoly(polyPointer p) {
    while (p) {
        printf("%.1fx^%d", p->coef, p->expon);
        if (p->link) printf(" + ");
        p = p->link;
    }
    printf("\n");
}
