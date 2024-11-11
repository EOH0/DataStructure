#include <stdio.h>

/*
2
2 10 1 0
4
1 4 10 3 3 2 1 0
*/

typedef struct {
    float coef;
    int expon;
} Poly;
Poly terms[100];
int avail = 0;

Poly readPoly(int startA, int finishA, int startB, int finishB);
float evalPoly(int startD, int finishD, float x);

int main() {
    FILE* file = fopen("f1.txt", "r");
    if (file == NULL) {
        printf("file error\n");
        return 1;
    }
    int startA, finishA, startB, finishB;

    readPoly(file, &startA, &finishA);
    readPoly(file, &startB, &finishB);  
    
    fclose(file);
}
void readPoly(FILE* file, int *start, int *finish) {
    int p;
    fscanf(file, "%d", &p);
    *start = 0;
    *finish = ((*start) + p) - 1;
    int ind = 0;
    for (int i = *start; i <= *finish; i++) {
        fscanf(file, "%d %d", &terms[i].coef, &terms[i].expon);
    }
}