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
}

// void searchStudent(Student *students, int n, char *searchName);