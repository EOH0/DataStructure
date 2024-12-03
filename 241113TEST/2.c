#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree {
    int key;
    treePointer leftChild, rightChild;
};

void inorder(treePointer ptr);
treePointer search(treePointer node, int k);
void insert(treePointer* node, int k);
void delete(treePointer* node, int k);
treePointer findMax(treePointer root);
treePointer findMin(treePointer node);

int main() {
    FILE* file = fopen("in4.txt", "r");
    if (file == NULL) {
        printf("file error");
        return 1;
    }

    int size = 0;
    int num;
    treePointer root = NULL;

    fscanf(file, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        insert(&root, num);
    }

    fscanf(file, "%d", &size);
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &num);
        delete(&root, num);
    }

    fclose(file);

    inorder(root);
    printf("\n");
}

void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->key);
        inorder(ptr->rightChild);
    }
}

treePointer search(treePointer node, int k) {
    while (node != NULL) {
        if (k == node->key) {
            return node;
        } else if (k < node->key) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
    return NULL;
}

void insert(treePointer* node, int k) {
    if (*node == NULL) {
        treePointer newNode = (treePointer)malloc(sizeof(struct tree));
        newNode->key = k;
        newNode->leftChild = newNode->rightChild = NULL;
        *node = newNode;
        return;
    }

    if (k < (*node)->key) {
        insert(&(*node)->leftChild, k);
    } else if (k > (*node)->key) {
        insert(&(*node)->rightChild, k);
    }
}

void delete(treePointer* node, int k) {
    if (*node == NULL) {
        printf("E ");
        return;
    }

    if (k < (*node)->key) { // 삭제하고자 하는 값이 현재 노드의 key보다 작으면 왼쪽 서브트리 탐색
        delete(&(*node)->leftChild, k); // 재귀적으로 다음 서브트리 탐색
    } else if (k > (*node)->key) { // 삭제하고자 하는 값이 현재 노드의 key보다 크면 오른쪽 서브트리 탐색
        delete(&(*node)->rightChild, k);
    } else { // 삭제하고자 하는 값을 트리에서 찾았을떄
        printf("S ");
        treePointer temp = *node; // 삭제할 노드를 temp에 할당

        // Case 1: No children (leaf node)
        if (temp->leftChild == NULL && temp->rightChild == NULL) {
            *node = NULL; // 그냥 노드를 NULL로 바꾸고
            free(temp); // node = temp free 해줌
        }
        // Case 2: One child
        else if (temp->leftChild == NULL || temp->rightChild == NULL) { 
            treePointer child = (temp->leftChild != NULL) ? temp->leftChild : temp->rightChild; // 둘 중 NULL이 아닌 쪽을 child로 선언
            *node = child; // 자식을 부모에 할당
            free(temp); // temp free 해줌
        }
        // Case 3: Two children
        else {
            treePointer maxNode = findMax(temp->leftChild); // 자식이 두개면 왼쪽 서브트리에서 가장 큰 값을 부모로 교체함
            // BST의 구조를 따르려면 부모가 오른쪽 서브트리보다 크면 안되므로 부모보다 작은 서브트리 중 가장 큰 값으로 교체
            // 삭제하는 노드는 왼쪽 서브트리의 모든 노드보다 무조건 크고, 오른쪽 서브트리의 모든 노드보다 무조건 작음
                // 왼쪽 서브트리에서 가장 큰 값은 이러한 부모의 조건을 항상 완벽히 만족
            temp->key = maxNode->key; // 어차피 교체를 해야하니까 free는 하지말고, 그냥 값만 바꿔줌
            delete(&temp->leftChild, maxNode->key); // 삭제한 노드의 자식 중 최대인 값을 복사해왔기 때문에 원본을 삭제해줌
        }
    }
}

treePointer findMax(treePointer root) {
    while (root != NULL && root->rightChild != NULL) {
        root = root->rightChild;
    }
    return root;
}

// treePointer findMin(treePointer node) {
//     while (node != NULL && node->leftChild != NULL) {
//         node = node->leftChild;
//     }
//     return node;
// }
