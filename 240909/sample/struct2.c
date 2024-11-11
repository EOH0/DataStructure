#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name[50];
    int age;
    char gender[10];
} UserInfo;

void inputUserInfo(UserInfo* user);
void printUserInfo(const UserInfo* user);

int main() {
    UserInfo user;

    inputUserInfo(&user);
    printUserInfo(&user);

    return 0;
}

void inputUserInfo(UserInfo* user) {
    printf("이름을 입력하세요: ");
    scanf("%s", user->name);
    printf("나이를 입력하세요: ");
    scanf("%d", &user->age);
    printf("성별을 입력하세요 ( 남성/여성 ): ");
    scanf("%s", user->gender);
}
void printUserInfo(const UserInfo* user) {
    printf("--- 사용자 정보 ---\n");
    printf("이름: %s\n", user->name);
    printf("나이: %d\n", user->age);
    printf("성별: %s\n", user->gender);
}