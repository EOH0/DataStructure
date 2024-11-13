#include <stdio.h>

void countNode(char tree[], int size, int *N1, int *N2, int *N0);

int main() {
    int size = 10;
    char tree[10];

    // int size = 17;
    // char tree[17];

    for (int i = 0; i < size; i++) {
        tree[i] = '\0';
    }

    tree[1] = 'A';
    tree[2] = 'B';
    tree[3] = 'C';
    tree[4] = 'D';
    tree[5] = 'E';
    tree[6] = 'F';
    tree[7] = 'G';
    tree[8] = 'H';
    tree[9] = 'I';

    // tree[1] = 'A';
    // tree[2] = 'B';
    // tree[4] = 'C';
    // tree[8] = 'D';
    // tree[16] = 'E';

    int N1, N2, N0;
    countNode(tree, size, &N1, &N2, &N0);

    printf("N1 = %d\n", N1);
    printf("N2 = %d\n", N2);
    printf("N0 = %d\n", N0);

    return 0;
}

void countNode(char tree[], int size, int *N1, int *N2, int *N0) {
    *N1 = *N2 = *N0 = 0;

    for (int i = 1; i < size; i++) {
        if (tree[i] != '\0') {
            int leftChild = 2 * i;
            int rightChild = 2 * i + 1;
            int childcnt = 0;

            if (leftChild < size && tree[leftChild] != '\0') {
                childcnt++;
            }
            if (rightChild < size && tree[rightChild] != '\0') {
                childcnt++;
            }

            if (childcnt == 0) {
                (*N0)++;
            }
            else if (childcnt == 1) {
                (*N1)++;
            }
            else if (childcnt == 2) {
                (*N2)++;
            }
        }
    }
}