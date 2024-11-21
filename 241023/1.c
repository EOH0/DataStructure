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
    // node는 헤더노드이지만 matrix의 행, 열 값을 저장하기 위해 header임에도 entry를 가짐
    node = newNode(); 
    node->tag = entry; // 데이터를 저장하는 모든 노드는 entry태그를 가짐
    // matrix의 행, 열 수를 저장
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;
    if (!numHeads) node->right = node;
    else { // head node들 생성, 초기화
        for (int i = 0; i < numHeads; i++) { 
            temp = newNode();
            hdnode[i] = temp;
            hdnode[i]->tag = head; // header 노드는 head태그를 가짐 -> 데이터를 저장하지 않음
            // 각 header노드는 초기엔 자기 자신을 가리키도록 초기화함 (비어있는 상태에)
            hdnode[i]->right = temp;
            hdnode[i]->u.next = temp;
        }
        currentRow = 0; // 현재 처리 중인 행의 인덱스를 나타내는 변수
        // 첫번쨰 행부터 시작하기 때문에 0으로 초기화
        last = hdnode[0]; // 현재 행의 마지막 노드를 첫번쨰 해의 헤더 노드로 초기화
        // last는 행렬의 각 행에서 마지막으로 추가된 노드를 가리키는 포인터임
        // 오직 행에서 가장 마지막에 있는 노드를 위치함
        // 열의 last를 굳이 하지않는 이유는 열은 다 독립적인 리스트기 때문에
        // last는 row값에 따라 어떤 row의 last인지 달라짐(매 반복마다 row값에 따라 달라짐)


        printf("행, 열, 값 입력\n");
        for (int i = 0; i < numTerms; i++) {
            scanf("%d %d %d", &row, &col, &value);

            if (row > currentRow) { // 현재 row를 닫는다
                // 입력은 무조건 row 순서대로 들어오기 때문에 한 row가 끝나고 새로운 row에 대한 작업을 시작할때
                last->right = hdnode[currentRow]; // 현재row의 마지막 노드의 link를 헤더에 연결해주고
                currentRow = row; // 현재row를 입력된 row로 변경
                last = hdnode[row]; // 또다시 row의 마지막 노드인 last를 초기화
            }
            temp = newNode();
            temp->tag = entry; // 값을 저장하는 노드이므로 entry 태그
            // temp가 위치할 row, col과 temp의 value 저장
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;

            last->right = temp; // last는 header이거나 가장 마지막의 노드이므로 last뒤에 붙히고
            last = temp; // last는 마지막이 된 temp가 됨

            // 열 리스트에 삽입 (모르겠다 다시 봐)
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