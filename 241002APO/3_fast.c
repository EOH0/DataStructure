#include <stdio.h>

#define MAX_TERM_SIZE 101

typedef struct {
    int row;
    int col;
    int value;
} term;

void readMatrix(char* filename, term matrix[]);
void fasttranspose(term a[], term b[]); // term a[] == term *a
void writeMatrix(const char *filename, term matrix[]);
void printMatrix2D(term matrix[]);

int main() {
    char filenameA[20] = "a.txt";
    char filenameB[20] = "b.txt";
    term a[MAX_TERM_SIZE] = { 0 }; // 구조체 내의 모든 요소가 0으로 초기화
    term b[MAX_TERM_SIZE] = { 0 };

    readMatrix(filenameA, a);
    fasttranspose(a, b);
    writeMatrix(filenameB, b);

    printf("A\n");
    printMatrix2D(a);

    printf("B\n");
    printMatrix2D(b);

    printf("\n");
    FILE* file = fopen("a.txt", "r");
    int num;
    int i = 0;
    while(fscanf(file, "%d ", &num) != EOF) {
        printf("%3d ", num);
        i++;
        if (i == 3) {
            i = 0;
            printf("\n");
        }
    }
    printf("\n");
    fclose(file);
    FILE* file2 = fopen("a.txt", "r");
    num;
    i = 0;
    while(fscanf(file2, "%d ", &num) != EOF) {
        printf("%3d ", num);
        i++;
        if (i == 3) {
            i = 0;
            printf("\n");
        }
    }
    fclose(file2);
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

void fasttranspose(term a[], term b[]) {
    /*
        a, b matrix는 절대 matrix의 모든 것이 아님
        그냥 0이 아닌 수의 row, col, value만 저장하는 matrix
        => 0으로 가득찬 matrix에 a로부터 row, col, value를 불러와
           b에 col, row, value로 저장하고, b[col][row]에 value만 딱딱 넣어주는 것임
    */
    int rowTerms[10]; // b matrix의 각 행에서 0이 아닌 수의 개수를 저장할 배열
    int startingPos[10]; // startingPos의 값은 b의 인덱스 자체가 됨
    int numCols = a[0].col;
    // a의 열을 따로 저장하는 이유
        // 코드의 가독성과 작성의 용이를 위해

    int numTerms = a[0].value; // 0이 아닌 수의 개수 저장

    // 전치를 위한 베이스 세팅
    b[0].row = numCols; 
    b[0].col = a[0].row;
    b[0].value = numTerms; // 0이 아닌 수의 개수는 같음

    if (numTerms > 0) {
        for (int i = 0; i < numCols; i++) { // rowTerms 초기화
            rowTerms[i] = 0;
        }
        for (int i = 1; i < numTerms; i++) { // 0이 아닌 수의 갯수만큼 반복
            rowTerms[a[i].col]++; // a에서 0이 아닌 수가 b의 각 row에 몇개씩 있을 것인가
            // a에서 각 0, 1, 2, 3, 4, 5 row에 있는 0이 아닌 수의 개수를 b의 col에 넣어줌 (rowTerms의 인덱스는 b의 col)
        }
        startingPos[0] = 1;
        for (int i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1]; 
            // rowTerms에 저장되어있는 0이 아닌 수의 개수를 이전 인덱스에 더함
            //            [0] [1] [2] [3] [4] [5]
            // rowTerms    2   1   2   2   0   1
            // startingPos 1   3   4   6   8   8
            //            i-1  i
        }
        int j = 0;
        for (int i = 1; i <= numTerms; i++) {
            // startingPos = [ 1, 3, 4, 6, 8, 8 ]
            j = startingPos[a[i].col]++;
            // startingPos의 인덱스를 0부터 시작하지 않아도 ()
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
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