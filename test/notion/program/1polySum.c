#include <stdio.h>
#include <math.h>

typedef struct {
    float coef;
    int expon;
} polynomial;
polynomial terms[101];

int avail = 0;

void readPoly(FILE* file, int *start, int *finish);
void attach(float coef, int expon);
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
void printPoly(int start, int finish);
float evalPoly(int startd, int finishd, float x);

int main() {
    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("file error");
        return 1;
    }

    int starta, finisha, startb, finishb, startd, finishd;

    readPoly(file, &starta, &finisha);
    readPoly(file, &startb, &finishb);
    fclose(file);

    padd(starta, finisha, startb, finishb, &startd, &finishd);

    printPoly(starta, finisha);
    printPoly(startb, finishb);
    printPoly(startd, finishd);

    float x;
    scanf("%f", &x);

    float result = evalPoly(startd, finishd, x);
    printf("D(%.2f) = %.2f", x, result);
}

void attach(float coef, int expon) {
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}
void readPoly(FILE* file, int *start, int *finish) {
    int num;
    fscanf(file, "%d", &num);

    float coef;
    int expon;

    *start = avail;

    for (int i = 0; i < num; i++) {
        fscanf(file, "%f %d", &coef, &expon);
        attach(coef, expon);
    }
    *finish = avail - 1;
}
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {
    float coefficient = 0;
    *startd = avail;

    while(starta <= finisha && startb <= finishb) {
        int compare = terms[starta].expon - terms[startb].expon;
        if (compare > 0) { // a지수 > b지수
            attach(terms[starta].coef, terms[starta].expon);
            starta++;
        }
        else if (compare == 0) { // a지수 == b지수
            coefficient = terms[starta].coef + terms[startb].coef;
            if (coefficient != 0) {
                attach(coefficient, terms[starta].expon);
            }
            starta++, startb++;
        }
        else if (compare < 0) {
            attach(terms[startb].coef, terms[startb].expon);
            startb++;
        }
    }
    
    for (int i = starta; i <= finisha; i++) {
        attach(terms[starta].coef, terms[starta].expon);
    }
    for (int i = startb; i <= finishb; i++) {
        attach(terms[startb].coef, terms[startb].expon);
    }
    *finishd = avail - 1;
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
float evalPoly(int startd, int finishd, float x) {
    float result = 0; 
    for (int i = startd; i <= finishd; i++) {
        result += terms[i].coef * (pow(x, terms[i].expon));
    }

    return result;
}