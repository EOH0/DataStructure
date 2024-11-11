#include <stdio.h>

#define MAX_TERM_SIZE 101

typedef struct {
    int row;
    int col;
    int value;
} term;

void readMatrix(char* filename, term matrix[]);
void transpose(term a[], term b[]); // term a[] == term *a
void writeMatrix(const char *filename, term matrix[]);
void printMatrix2D(term matrix[]);

int main() {
    char filenameA[20] = "a.txt";
    char filenameB[20] = "b.txt";
    term a[MAX_TERM_SIZE] = { 0 }; // 구조체 내의 모든 요소가 0으로 초기화
    term b[MAX_TERM_SIZE] = { 0 };

    readMatrix(filenameA, a);
    transpose(a, b);
    writeMatrix(filenameB, b);

    printf("A\n");
    printMatrix2D(a);

    printf("B\n");
    printMatrix2D(b);
}

void readMatrix(char* filename, term matrix[]) {
    FILE* file = fopen(filename, "r"); // a.txt
    if (file == NULL) {
        printf("file error\n");
        return;
    }

    fscanf(file, "%d %d %d", &matrix[0].row, &matrix[0].col, &matrix[0].value);

    for (int i = 1; i <= matrix[0].value; i++) {
        fscanf(file, "%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }

    fclose(file);
}
void transpose(term a[], term b[]) {
    int n;
    int currentb;
    n = a[0].value; // n은 원 행렬에서 0인 아닌 요소의 개수
    
    b[0].row = a[0].col; // a의 열 -> b의 행
    b[0].col = a[0].row; // a의 행 -> b의 열
    b[0].value = n; // b[0].value = n = a[0],value --- 결국 0이 아닌 요소의 수는 같음
    
    // a랑 b 구조체는 1차원 배열 형태로 사용되지만 2차원 배열에 각 행, 열, 원소값이 차례로 있는 형태
    /*
        a[0] [ row, col, value ]
        a[1] [ row, col, value ]
    */
   // 전치해주는 것도 통쨰로 뒤집는게 아니라
   // a에서 0이 아닌 원소의 row, col, value값을 0으로 초기화된 b의 row, col, value에 넣어주는 것
   // 이때 a_row -> b_col / a_col -> b_row로 바뀌는 정도
    if (n > 0) { // 0이 아닌 요소가 있으면
        currentb = 1; // 행렬 입력은 구조체의 [currentb]부터 <- index
        for (int i = 0; i < a[0].col; i++) { // 0이 아닌 요소가 존재하는 열만 판단하도록
            for (int j = 1; j <= n; j++) { // 0이 아닌 요소의 개수로 몇번째 요소인지 판별하도록
                if (a[j].col == i) { // a[j].col 이 0이 아닌 요소가 존재하는 열이라면
                    // b에 입력
                    // 어차피 나머지는 다 0으로 초기화되어있으니까 0이 아닌 요소만 알맞은 자리에 넣어주면됨
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}

void writeMatrix(const char *filename, term matrix[]){
    FILE* file = fopen(filename, "w");

    fprintf(file, "%d %d %d\n", matrix[0].row, matrix[0].col, matrix[0].value);

    for (int i = 1; i <= matrix[0].value; i++) {
        fprintf(file, "%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].value);
    }

    fclose(file);
}
void printMatrix2D(term matrix[]) {
    int row = matrix[0].row;
    int col = matrix[0].col;
    
    int num = 1; // 1부터 시작, 0은 row, col, value
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {    
            if (matrix[num].row == i && matrix[num].col == j) {
                printf("%3d ", matrix[num].value);
                num++;
            }
            else {
                printf("  0 ");
            }
        }
        printf("\n");
    }
}