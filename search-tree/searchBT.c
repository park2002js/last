#include "Heap.h"
/*
1. 이진 탐색 트리에는 중복되는 값이 없다.
*/


// 노드 생성
TreeNode* makeNode(int key) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}


// 삭제 알고리즘
void deleteBST(){

}

// 삽입 알고리즘
// 왜 반환형이 존재하는지 이해해볼 것
TreeNode* insertKey(TreeNode* root, int key){
    // 없으면? 만든다.
    if(root == NULL){
        TreeNode* newNode = makeNode(key);
        root = newNode;
        return root;
    }

    // 현재 node의 key 값보다 삽입하고자 하는 key 값이 더 작을 경우
    if(root->data > key){
        insertKey(root->left, key);  // 왼쪽에 삽입하도록 재귀 호출
    } else if(root->data < key){
        insertKey(root->right, key); // 아니면 오른쪽에 삽입하도록 재귀 호출
    } else {
        return root; // 중복값 삽입을 방지하기 위함
    }
}

// 특정 키 값을 가지고 있는 TreeNode의 포인터를 반환
// infix order의 형태를 따름
TreeNode* find(TreeNode* node, int key){
    TreeNode* temp = node;

    // 찾으려는 값이 어느 노드를 찾아도 없는 경우
    // leaf-> 말단까지 왔음에도 더 이상 node가 없다는 뜻이므로 NULL로 확인
    if(temp == NULL){
        return NULL;
    }
    // 여기서의 if문의 조건문들은, 사용하는 데이터가 어떤 자료형이냐에 따라 달라질 수 있음
    // 일치하는 값이면 현재 노드의 포인터 반환
    if(temp->data == key){
        return temp;
    }
    else if(temp->data > key) {
        find(temp->left, key); // key 값이 더 작으면 왼쪽으로
    } else {
        find(temp->right, key); // key 값이 더 크면 오른쪽으로
    }
}

void printNode(TreeNode* node){
    if(node != NULL){
        printNode(node->left);
        printf("%d  ", node->data);
        printNode(node->right);
    }
}

// 탐색 알고리즘
void searchBST(TreeNode* B, int key){
    TreeNode* temp = B;

    if(temp == NULL){
        return ;
    }
}


// 이진 정렬 트리와 중위 우선 순회 방법을 이용
// 이진트리가 잘 정렬되어 있다는 가정하에, infix order로 순회할 경우 오름차순 출력이 됨

SearchTree T

T = makeEmpty()

void Insert(){

}

void InfixOrder(){

}

