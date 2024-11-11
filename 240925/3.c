#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
} Student;

Student* create(int size);
Student* resize(Student* array, int* size);
Student* add(Student* array, int* count, int* size, int id, char* name);
void removeById(Student* array, int* count, int id);
void print(Student* array, int count);
void freeArray(Student* array);

int main() {
    FILE* file = fopen("f3.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int size = 10;
    Student* stud = create(size);

    int count = 0;
    int n = 1;
    while(fscanf(file, "%d %s", &stud[count].id, &stud[count].name) != EOF) {
        count++;
        if (count >= size) {
            n++;
            size = size * n;
            stud = resize(stud, &size);
        }
    }

    fclose(file);
    
    // for (int i = 0; i < count; i++) {
    //     printf("%d %s\n", stud[i].id, stud[i].name);
    // }

    int selection = 0;
    int id = 0;
    char name[100];
    while(selection != 4) {
        printf(">> 1.추가 / 2.삭제 / 3.출력 / 4.종료: ");
        scanf("%d", &selection);
        switch (selection) {
        case 1:
            printf("학번 이름 입력: ");
            scanf("%d %s", &id, &name);
            add(stud, &count, &size, id, name);
            break;
        case 2:
            printf("학번 입력: ");
            scanf("%d", &id);
            removeById(stud, &count, id);
            break;
        case 3:
            print(stud, count);
            break;
        case 4:
            printf("종료되었습니다.\n");
            break;
        }
    }
}

Student* create(int size) {
    Student *stud = (Student *)malloc(sizeof(Student) * size);

    return stud;
}

Student* resize(Student* array, int* size) {
    Student* resizedArr = (Student *)realloc(array, sizeof(Student)*(*size));

    return resizedArr;
}

Student* add(Student* array, int* count, int* size, int id, char* name) {
    if (*count >= *size) {
        *size = *size * 2;
        array = resize(array, size);
    }

    array[*count].id = id;
    strcpy(array[*count].name, name);
    (*count)++; // *count++랑은 다름

    printf("%d 데이터가 추가되었습니다.\n", id);
    printf("배열 데이터 개수 %d\n", *count);
    printf("\n");

    return array;
}

void removeById(Student* array, int* count, int id) {
    id--; // id = (index + 1)이므로
    if (id + 1 == array[id].id) {
        for (int i = id; i < (*count) - 1; i++) {
            array[i].id = array[i + 1].id;
            strcpy(array[i].name, array[i + 1].name);
        }
        printf("학번 %d 데이터가 삭제 되었습니다.\n", id + 1);
        (*count) -= 1;
    }
    else {
        printf("학번 %d 데이터는 존재하지 않습니다.\n", id + 1);
    }

    printf("배열 데이터 개수 %d\n", *count);
    printf("\n");
    printf("%d", array[id].id);
}

void print(Student* array, int count) {
    for (int i = 0; i < count - 1; i++) {
        printf("%d %s\n", array[i].id, array[i].name);
    }
    printf("\n");
}

void freeArray(Student* array) {
    free(array);
}