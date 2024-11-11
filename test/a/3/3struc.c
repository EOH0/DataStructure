#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[100];
} Student;

int del = 0;
Student* create(int size);
Student* resize(Student* array, int* size);
Student* add(Student* array, int* count, int* size, int id, char* name);
void removeById(Student* array, int* count, int id);
void print(Student* array, int count);
void freeArray(Student* array);

int main() {
    int size = 10;
    Student* stud = create(size);

    FILE* file = fopen("f3.txt", "r");
    if (file == NULL) {
        printf("file error.\n");
        return 1;
    }

    int index = 0;
    int count = 0;
    while(fscanf(file, "%d %s", &stud[index].id, &stud[index].name) != EOF) {
        index++;
        count++;
        if (index >= size) {
            stud = resize(stud, &size);
        }
    }
    fclose(file);

    int input = 0;
    while(input != 4) {
        printf(">> 1.추가 2.삭제 3.출력 4.종료: ");
        scanf("%d", &input);
        switch (input) {
        case 1: // 추가
            printf("학번 이름 입력: ");
            int id;
            char name[100];
            scanf("%d %s", &id, &name);
            add(stud, &count, &size, id, name);
            break;
        case 2: // 삭제
            printf("학번 입력: ");
            scanf("%d", &id);
            removeById(stud, &count, id);
            break;
        case 3: // 출력
            print(stud, count);
            break;
        case 4: // 종료
            free(stud);
            break;
        }
        printf("배열 데이터 개수 %d\n", count);
    }   
}

Student* create(int size) {
    Student* stud = (Student *)malloc(sizeof(Student) * size);

    return stud;
}
Student* resize(Student* array, int* size) {
    *size *= 2;
    Student* Resizedarray = (Student *)realloc(array, sizeof(Student) * (*size));

    return Resizedarray;
}
Student* add(Student* array, int* count, int* size, int id, char* name) {
    *count += 1;
    if ((*count) >= *size) {
        array = resize(array, size);
    }
    array[(*count)].id = id;
    strcpy(array[(*count)].name, name);
    printf("%d 데이터가 추가되었습니다.\n", id);

    return array;
}
void removeById(Student* array, int* count, int id) {
    int removeId = 0;
    for (int i = 0; i < *count; i++) {
        if (array[i].id == id) {
            removeId = id;
        }
    }
    if (removeId == id) {
        *count -= 1;
        del++;
        for (int i = removeId - del; i < *count; i++) {
            array[i].id = array[i+1].id;
            strcpy(array[i].name, array[i+1].name);
        }
        printf("학번 %d 데이터가 삭제되었습니다.\n", id);
    }
    else {
        printf("학번 %d 데이터는 존재하지 않습니다.\n", id);
    }
}
void print(Student* array, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d %s\n", array[i].id, array[i].name);
    }
}
void freeArray(Student* array) {
    free(array);
}