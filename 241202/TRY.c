#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct hash{
    char key[10];
    int value;
} hash;

unsigned int stringToInt(char* key);
int hashingfunction(int value, int D);
void SearchKey(hash* hashTable, FILE* fileSearch, int D);
void PrintHT(hash* hashTable, int D);

int main() {
    FILE* fileIn = fopen("in.txt", "r");
    FILE* fileSearch = fopen("search.txt", "r");
    if (fileIn == NULL || fileSearch == NULL) {
        return 1;
    }

    int D;
    scanf("%d", &D);

    hash* hashTable = (hash*)malloc(sizeof(hash) * D);

    char key[10]; int idx = 0; int value = 0;
    int hashF = 0;

    while(fscanf(fileIn, "%s", &key) != EOF) {
        value = stringToInt(key);
        hashF = hashingfunction(value, D);

        strcpy(hashTable[hashF].key, key);
        hashTable[hashF].value = value;

        idx++;
    }

    SearchKey(hashTable, fileSearch, D);

    fclose(fileIn);
    fclose(fileSearch);

    PrintHT(hashTable, D);
}

unsigned int stringToInt (char* key) {
    int num = 0;
    while(*key) {
        num += *key++;
    }
    return num;
}
int hashingfunction(int value, int D) {
    int hashF = value % D;

    return hashF;
}
void SearchKey(hash* hashTable, FILE* fileSearch, int D) {
    char ch[10]; int idx = 0;
    while(fscanf(fileSearch, "%s", &ch) != EOF) {
        for (int i = 0; i < D; i++) {
            if (strcmp(hashTable[i].key, ch) == 0 && hashTable[i].key) {
                printf("S\n");
                break;
            }
            else {
                printf("E\n");
                break;
            }
        }
    }
}
void PrintHT(hash* hashTable, int D) {
    for (int i = 0; i < D; i++) {
        printf("%d: %s (%d)\n", i, hashTable[i].key, hashTable[i].value);
    }
}