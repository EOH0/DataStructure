#include <stdio.h>

void countNode(char tree[], int size, int* n0, int* n1, int* n2);

int main() {
    char tree[10];
    int size = 10;

    for (int i = 1; i < size; i++) {
        tree[i] = i + 'a' - 1;
    }

    int n0, n1, n2;
    countNode(tree, size, &n0, &n1, &n2);
    printf("n0 %d\n",n0);
    printf("n1 %d\n",n1);
    printf("n2 %d\n",n2);
}
void countNode(char tree[], int size, int* n0, int* n1, int* n2) {
    *n1 = *n2 = *n0 = 0;

    for (int i = 1; i < size; i++) {
        if (tree[i] != '\0') {
            int Lchild, Rchild;
            int childCnt = 0;
            Lchild = i * 2;   
            Rchild = i * 2 + 1;
            if (Lchild < size && tree[Lchild] != '\0') {
                childCnt++;
            }
            if (Rchild < size && tree[Rchild] != '\0') {
                childCnt++;
            }
            if (childCnt == 0) {
                (*n0)++;
            }
            else if (childCnt == 1){
                (*n1)++;
            }
            else if (childCnt == 2) {
                (*n2)++;
            }
            printf("%d %d %d\n", *n0, *n1, *n2);
        }
    }
}