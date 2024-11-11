#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef enum {head, entry} tagfield;
typedef struct matrixNode *matrixPointer;
struct entryNode {
    int row;
    int col;
    int value;
};
struct matrixNode {
    matrixPointer down;
    matrixPointer right;
    tagfield tag;
    union {
        matrixPointer next;
        struct entryNode entry;
    } u;
};
matrixPointer hdnode[MAX_SIZE];

matrixPointer mread();
matrixPointer newNode();
void mwrite(matrixPointer node);
void merase(matrixPointer *node);

int main() {
    int input = 0;
    matrixPointer node = NULL;
    while(input != 4) {
        printf("matrix 작업 선택 (1.입력 2.출력 3.삭제 4.종료): ");
        scanf("%d", &input);
        switch (input) {
        case 1:
            node = mread();
            break;
        case 2:
            mwrite(node);
            break;
        case 3:
            merase(&node);
            break;
        case 4:
            break;
        }
    }
}

matrixPointer mread() {
    int numRows, numCols, numTerms, numHeads;
    int row, col, value, currentRow;
    matrixPointer temp, last, node;

    printf("행과 열의 크기 및 nonzero 항의 개수 입력\n");
    scanf("%d %d %d", &numRows, &numCols, &numTerms);

    numHeads = (numCols > numRows) ? numCols : numRows; // 더 큰 row나 col을 기준으로 head생성

    // 헤더 노드의 연결리스트를 위해 헤더 노드 자체 셋업
    node = newNode();
    node->tag = entry;
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;
    if (!numHeads) node->right = node;
    else { // head node들 생성, 초기화
        for (int i = 0; i < numHeads; i++) { 
            temp = newNode();
            hdnode[i] = temp;
            hdnode[i]->tag = head;
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0]; // 현재 row의 마지막 노드

        printf("행, 열, 값 입력\n");
        for (int i = 0; i < numTerms; i++) {
            scanf("%d %d %d", &row, &col, &value);

            if (row > currentRow) { // 현재 row를 닫는다? 이게 뭐야
                last->right = hdnode[currentRow];
                currentRow = row;
                last = hdnode[row];
            }
            temp = newNode();
            temp->tag = entry;
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;

            last->right = temp; // row 리스트에 링크
            last = temp;

            // col 리스트에 링크
            hdnode[col]->u.next->down = temp;
            hdnode[col]->u.next = temp;
        }
        // 마지막 row 닫기
        last->right = hdnode[currentRow];

        // 모든 column 리스트 닫기
        for (int i = 0; i < numCols; i++){
            hdnode[i]->u.next->down = hdnode[i];
        }

        // 모든 헤더 노드 연결
        for (int i = 0; i < numHeads - 1; i++) {
            hdnode[i]->u.next = hdnode[i + 1];
        }
        hdnode[numHeads - 1]->u.next = node;
        node->right = hdnode[0];
    }
    
    return node;
}

matrixPointer newNode() {
    matrixPointer node = (matrixPointer)malloc(sizeof(struct matrixNode));
    
    return node;
}

void mwrite(matrixPointer node) {
    // row 중점 형태에서 매트릭스 출력
    matrixPointer temp, head = node->right;

    // 매트릭스 차원
    printf("\n numRows = %d, numCols = %d\n", node->u.entry.row, node->u.entry.col);

    printf("매트릭스의 행, 열, 값: \n\n");
    for (int i = 0; i < node->u.entry.row; i++) {
        // 각 row에서 entry 출력
        for (temp = head->right; temp != head; temp = temp->right) {
            printf("%5d %5d %5d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        }
        head = head->u.next; // next row
    }
}

void merase(matrixPointer *node) {
    // 매트릭스 지우기, 노드를 힙으로 리턴
    matrixPointer x, y, head = (*node)->right;
    int numHeads;
    // row에서 entry랑 헤더 노드를 free
    for (int i = 0; i < (*node)->u.entry.row; i++) {
        y = head->right;
        while(y != head) {
            x = y;
            y = y->right;
            free(x);
        }
        x = head;
        head = head->u.next;
        free(x);
    }
    // 남은 헤더노드 free
    y = head;
    while(y != (*node)){
        x = y;
        y = y->u.next;
        free(x);
    }
    free(*node);
    *node = NULL;
}