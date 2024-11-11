#include <stdio.h>
#include <math.h>

typedef struct poly{
    float coef;
    int expon;
} poly;
poly terms[101];
int avail = 0;

void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
void readPoly(FILE* file, int *start, int *finish);
void attach(float coef, int expon);
void printPoly(int start, int finish);
float evalPoly(int start, int finish, float x);


int main() {
    FILE* file = fopen("poly.txt", "r");
    if (file == NULL) {
        printf("file error.\n");
    }

    int starta, finisha, startb, finishb, startd, finishd;

    readPoly(file, &starta, &finisha);
    readPoly(file, &startb, &finishb);
    fclose(file);

    printPoly(starta, finisha);
    printPoly(startb, finishb);

    padd(starta, finisha, startb, finishb, &startd, &finishd);

    printPoly(startd, finishd);

    float x;
    scanf("%f", &x);
    evalPoly(startd, finishd, x);
}

void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {
    *startd = avail;
    while(starta != finisha && startb != finishb) {
        if (terms[starta].expon > terms[startb].expon) {
            attach(terms[starta].coef, terms[starta].expon);
            starta++;
        }
        else if (terms[starta].expon == terms[startb].expon) {
            float coeff = terms[starta].coef + terms[startb].coef;
            if (coeff != 0) {
                attach(, terms[starta].expon);
            }
            starta++;
            startb++;
        }
        else if (terms[starta].expon < terms[startb].expon) {
            attach(terms[startb].coef, terms[startb].expon);
            startb++;
        }
    }
    for (int i = starta; i < finisha; i++) {
        attach(terms[i].coef, terms[i].expon);
    }
    for (int i = startb; i < finishb; i++) {
        attach(terms[i].coef, terms[i].expon);
    }
    *finishd = avail;
}
void readPoly(FILE* file, int *start, int *finish) {
    *start = avail;
    int num;
    float coef; int expon;
    fscanf(file, "%d", &num);
    for(int i = 0; i < num; i++) {
        fscanf(file, "%f %d", &coef, &expon);
        attach(coef, expon);
    }
    *finish = avail;
}
void attach(float coef, int expon) {
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}
void printPoly(int start, int finish) {
    for (int i = start; i < finish; i++) {
        printf("%.0lfx^%d ", terms[i].coef, terms[i].expon);
        if (i != finish - 1) {
            printf("+ ");
        }
        else {
            printf("\n");
        }
    }
}
float evalPoly(int start, int finish, float x) {
    float sum = 0;
    for (int i = start; i < finish; i++) {
        sum += terms[i].coef * pow(x, terms[i].expon);
    }
    printf("%.2f", sum);
}