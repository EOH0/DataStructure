#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element {
    char key[4];
    int value;
} element;

element* ht;

unsigned int stringToInt(char* key);
element* Search(int k);
int h(int k);
void printHash(element* ht);

int D;

int main() {
    FILE* fileIn = fopen("in.txt", "r");
    FILE* fileSearch = fopen("search.txt", "r");
    if (fileIn == NULL || fileSearch == NULL) {
        return 1;
    }

    scanf("%d", &D);

    ht = (element*)malloc(sizeof(element) * D);

    for (int i = 0; i < D; i++) {
        ht[i].value = 0;
    }

    char key[4];
    int value = 0;
    int hashF = 0;

    while (fscanf(fileIn, "%s", key) != EOF) {
        value = stringToInt(key);
        hashF = h(value);
        while (ht[hashF].value != 0) {
            hashF = (hashF + 1) % D;
        }
        strcpy(ht[hashF].key, key);
        ht[hashF].value = value;
    }
    fclose(fileIn);

    char ch[4];
    while (fscanf(fileSearch, "%s", ch) != EOF) {
        int valueToSearch = stringToInt(ch);
        element* find = Search(valueToSearch);
        if (find != NULL) {
            printf("S\n");
        } else {
            printf("E\n");
        }
    }
    fclose(fileSearch);

    printHash(ht);

    return 0;
}

unsigned int stringToInt(char* key) {
    int num = 0;
    while (*key) {
        num += *key++;
    }
    return num;
}

int h(int k) {
    return k % D;
}

element* Search(int k) {
    int homeBucket = h(k);
    int currentBucket = homeBucket;

    while (strlen(ht[currentBucket].key) != 0 && ht[currentBucket].value != k) {
        currentBucket = (currentBucket + 1) % D;
        if (currentBucket == homeBucket) {
            return NULL;
        }
    }
    if (ht[currentBucket].value == k) {
        return &ht[currentBucket];
    }
    return NULL;
}

void printHash(element* ht) {
    for (int i = 0; i < D; i++) {
        printf("%d: ", i);
        if (ht[i].value != 0) {
            printf("%s (%d)", ht[i].key, ht[i].value);
        }
        printf("\n");
    }
}
