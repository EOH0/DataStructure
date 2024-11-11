#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
    char phone[20];
} Person;

void initPeople(Person people[], int size);
void printPeopleByAge(Person people[], int size, int minAge, int maxAge);

int main() {
    Person people[5];
    int size = 2;

    initPeople(people, size);
    printPeopleByAge(people, size, 20, 29);

    return 0;
}

void initPeople(Person people[], int size) {
    strcpy(people[0].name, "John Doe");
    people[0].age = 30;
    strcpy(people[0].phone, "123-456-7890");
}
void printPeopleByAge(Person people[], int size, int minAge, int maxAge);