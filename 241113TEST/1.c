#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree{
    int key;
    treePointer leftChild, rightChild;
};

int check = 0;

treePointer newNode(int key);
void inorder(treePointer ptr);
treePointer modifiedSearch(treePointer node, int k);
void insert(treePointer* root, int k);
treePointer findMax(treePointer root);

int main() {
    FILE* file = fopen("in1.txt", "r");
    // FILE* file = fopen("in2.txt", "r");
    if (file == NULL) {
        printf("file error");
        return 1;
    }

    int size = 0;
    fscanf(file, "%d", &size);

    int num;
    treePointer root = NULL;
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        insert(&root, num);
    }
    fclose(file);
    inorder(root); printf("\n");

    treePointer max = findMax(root);
    printf("%d", max->key);
}

treePointer findMax(treePointer root) {
    while(root != NULL && root->rightChild != NULL) {
        root = root->rightChild;
    }

    return root;
}
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->key);
        inorder(ptr->rightChild);
    }
}
treePointer modifiedSearch(treePointer node, int k) { // 중복 검증 함수 / 기본적으로 BinarySearchTree라는 전제로 검증이 수행
    treePointer now = NULL;
    while(node != NULL) {
        now = node;
        // 경우를 중복 값이 있다 / 값이 현재 노드보다 작다 / 값이 현재 노드보다 크다 의 세가지 경우로 나눔
        if (k == node->key) { // 중복이 있으면 아무것도 추가되지 않음
            return NULL;
        }
        else if (k < node->key) { // 넣고자 하는 값이 현재 노드의 값보다 작으면 현재 노드의 왼쪽 서브트리에서 비교하도록 왼쪽 자식으로 보냄
            // BST이므로 k가 node->key보다 작다면 모든 서브트리를 탐색할 필요없이 작은 부분만 탐색만 해도됨
            node = node->leftChild;
        }
        else { // k > node->key
            node = node->rightChild;
        }
    }
    // 탐색이 끝난 후 중복이 없으면 탐색 도착지 리턴 (도착지는 새로운 노드의 부모)
    // while문의 종료는 NULL때문이 맞지만, 그 조건을 while이 있는 문장 하나에서 판단하고, now에 선언이 되진 않음
    // 그러므로 now는 새로운 값의 부모가 될 노드를 가리킴
    return now;
}
void insert(treePointer* root, int k) { // *node == *root
    treePointer ptr; // 새로운 값을 저장할 노드 포인터 / BST는 크기에 상관없이 들어온 순서대로 무조건 자식 위치에 감 (부모와 자리 교체되는 일이 없음)
    treePointer temp = modifiedSearch(*root, k); // 새로 저장할 값의 부모가 될 노드
    if (temp != NULL || (*root) == NULL) {
        ptr = (treePointer)malloc(sizeof(struct tree));
        ptr->key = k;
        ptr->leftChild = ptr->rightChild = NULL;
        
        if (*root) {
            if (k < temp->key) temp->leftChild = ptr;
            else temp->rightChild = ptr;
        }
        else { // 가장 초기 (트리가 비었을때 )
            *root = ptr;
        }
    }
}