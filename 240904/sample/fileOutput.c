#include <stdio.h>

int main () {
    FILE* file = fopen("output,txt", "r");
    if (file == NULL) {
        printf("File error.\n");
        return 1;
    }

    int num;
    while (fscanf(file, "%d", &num) != EOF) {
        printf("%d\n", num);
    }

    fclose(file);
    return 0;
}