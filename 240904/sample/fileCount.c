#include <stdio.h>

int count_integers(FILE* file) {
    int num;
    int cnt = 0;
    while (fscanf(file, "%d", &num) != EOF) {
        cnt++;
    }
    return cnt;
}

int main () {
    FILE* file = fopen("random_numbers.txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    printf("%d", count_integers(file));

    fclose(file);
    return 0;
}