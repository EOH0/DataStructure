#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    char name[20];
    double score1;
    double score2;
    double quiz;
} Student;

void printStudents(Student* students, int n);
void searchStudent(Student* students, int n, char* searchName);
void qsortStudents(Student* students, int n);
int compare(const void *a, const void *b);

int main() {
    FILE* file = fopen("f2.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int size;
    fscanf(file, "%d", &size);
    Student* students = (Student*)malloc(sizeof(Student)*size);
    for (int i = 0; i < size; i++) {
        students[i].number = i + 1;
        fscanf(file, "%s", &students[i].name);
        fscanf(file, "%lf", &students[i].score1);
        fscanf(file, "%lf", &students[i].score2);
        fscanf(file, "%lf", &students[i].quiz);        
    }
    fclose(file);

    printStudents(students, size);

    char *search = (char*)malloc(sizeof(char) * 20);
    scanf("%s", search);

    searchStudent(students, size, search);

    qsortStudents(students, size);
    
    free(students);
    free(search);
}

void printStudents(Student* students, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", students[i].number);
        printf("%s ", students[i].name);
        printf("%.1lf ", students[i].score1);
        printf("%.1lf ", students[i].score2);
        printf("%.1lf ", students[i].quiz);
        double sum = (students[i].score1) + (students[i].score2) + (students[i].quiz);
        printf("%.1lf\n", sum);
    }
    printf("\n");
}
void searchStudent(Student *students, int n, char* searchName) {
    for (int i = 0; i < n; i++) {
        if (strcmp(searchName, students[i].name) == 0) {
            printf("%d ", students[i].number);
            printf("%s ", students[i].name);
            printf("%.1lf ", students[i].score1);
            printf("%.1lf ", students[i].score2);
            printf("%.1lf ", students[i].quiz);
            double sum = (students[i].score1) + (students[i].score2) + (students[i].quiz);
            printf("%.1lf\n", sum);
        }
    }
    printf("\n");
}

void qsortStudents(Student* students, int n) {
    qsort(students, n, sizeof(students[0]), compare); // compare은 인자를 보낼 필요가 없다
    printStudents(students, n);
}

int compare(const void *a, const void *b) { // 인자를 포인터로 직접 지정하기 때문
    // qsort하고자 하는 요소의 메모리 주소를 직접 받아 정렬함
    Student *str1 = (Student *)a;
    Student *str2 = (Student *)b;

    // return str1->name - str2->name;
    return strcmp(str1->name, str2->name);
}


// void searchStudent(Student *students, int n, char *searchName);