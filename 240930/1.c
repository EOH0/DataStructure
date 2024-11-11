#include <stdio.h>
#include <math.h>

typedef struct {
    float coef;
    int expon;
} polynomial;
polynomial terms[101]; // 각 항을 저장함
// coef는 계수
// expon은 지수
int avail = 0; // 한 배열에 모든 다항식을 저장하기 때문에 진행 상황, 즉 trail의 역할을 하는 avail

// main에서 함수 기능을 구현한 후 넘길 인자와 리턴값 고려
void attach(float coeff, int expone);
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
void readPoly(FILE *file, int *start, int *finish);
void printPoly(int start, int finish);
float evalPoly(int startD, int finishD, float x);

int main() {
    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("File error\n");
        return 1;
    }
    int starta, finisha, startb, finishb, startd, finishd;

    readPoly(file, &starta, &finisha);
    readPoly(file, &startb, &finishb);
    fclose(file);

    padd(starta, finisha, startb, finishb, &startd, &finishd);

    float x = 0;
    scanf("%f", &x);

    printf("A(x) = "); printPoly(starta, finisha);
    printf("B(x) = "); printPoly(startb, finishb);
    printf("D(x) = "); printPoly(startd, finishd);
    printf("\n");
    
    float result = evalPoly(startd, finishd, x);
    printf("D(%.2f) = %.2f", x, result);

    return 0;
}

void attach(float coeff, int expone) {
    terms[avail].coef = coeff;
    terms[avail].expon = expone;
    avail++;
}
void readPoly(FILE *file, int *start, int *finish) {
    int num = 0;
    float coef; int expon;
    fscanf(file, "%d", &num); // 항이 몇개인지

    *start = avail; // global variable avail에 저장된 다항식의 첫번째 index 저장
    // 모든 다항식은 하나의 구조체 배열에 저장되므로
    for (int i = 0; i < num; i++) {
        fscanf(file, "%f %d", &coef, &expon);
        attach(coef, expon);
    }
    *finish = avail - 1;
    // 다항식의 입력이 끝나면 그 다항식의 마지막 인덱스를 avail에 저장
    // avail은 attach 함수 내에서 증가함
}
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {
    float coefficient = 0;
    *startd = avail; 
    // a, b 다항식이 모두 입력되고 난 후 그 둘을 더한 다항식을 시작할 index: startd
    // global variable 이기에 startd에 바로 저장하면서 한 배열에서 모든 다항식을 컨트롤 가능
    
    while(starta <= finisha && startb <= finishb) { // 각 다항식 중 하나라도 끝날 때까지
        int compare = terms[starta].expon - terms[startb].expon; // 지수를 비교함
        if (compare < 0) { // b의 지수가 더 큰 경우 b를 d 다항식에 저장함
            attach(terms[startb].coef, terms[startb].expon);
            startb++; // b의 다음 항으로 넘어감
        }
        else if (compare == 0) { // 두 항의 지수가 같을 경우 두 항의 계수를 더해 d에 저장
            coefficient = terms[starta].coef + terms[startb].coef;
            if (coefficient != 0) {
                attach(coefficient, terms[starta].expon);
            }
            starta++; startb++; // a, b 모두 다음 항으로 넘어감
        }
        else if (compare > 0) { // a의 지수가 더 큰 경우 a를 d 다항식에 저장
            attach(terms[starta].coef, terms[starta].expon);
            starta++; // a의 다음 항으로 넘어감
        }
    }
    // while문의 조건에 의해 더해지지 못한 항이 있을 경우
    // 아래의 for문으로 더해줌
    for (int i = starta; i <= finisha; i++) {
        attach(terms[starta].coef, terms[starta].expon);
    }
    for (int i = startb; i <= finishb; i++) {
        attach(terms[startb].coef, terms[startb].expon);
    }

    *finishd = avail - 1; // d 다항식의 마지막 index 저장
}
void printPoly(int start, int finish) {
    for (int i = start; i <= finish; i++) {
        printf("%.0fx^%d ", terms[i].coef, terms[i].expon);
        if (terms[i].expon != 0) {
            printf("+ ");
        }
    }
    printf("\n");
}
float evalPoly(int startD, int finishD, float x) {
    float result = 0;
    for (int i = startD; i <= finishD; i++) {
        result += terms[i].coef * (pow(x, terms[i].expon));
    }
    return result;
}