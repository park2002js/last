#include "Heap.h"

// 노드 생성
TreeNode* makeNode(int key) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    return node;
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
        return find(temp->left, key); // key 값이 더 작으면 왼쪽으로
    } else {
        return find(temp->right, key); // key 값이 더 크면 오른쪽으로
    }
}

// 재귀를 안쓰고 반복을 사용하는 탐색 알고리즘
TreeNode* searchBST(TreeNode* B, int key){
    TreeNode* temp = B;

    while(temp != NULL){
        if(temp->data == key) {
            return temp;
        }
        if(temp->data > key) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return temp;
}

// 삽입 알고리즘 1 : 반복 사용
// 파라미터 root가 이중 포인터여야 변경사항이 전달됨
void insertKey_1(TreeNode** root, int key){
    
    // 삽입할 노드의 부모 노드까지 이동하는 김에 중복되는 값인지 확인하는 반복
    TreeNode* temp = *root;
    TreeNode* parent = NULL;
    while(temp != NULL){
        if(temp->data == key){
            return;
        }
        parent = temp;
        if(temp->data > key) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    temp = makeNode(key);

    // 이진트리가 공백이었던 경우
    if(*root == NULL){
        *root = temp;
    }
    else
    // 포인터이기 때문에 parent는 root가 가리키는 트리의 노드를 가리킴
    // 따라서 parent를 통한 수정은 root도 공유 받는다.
    if(parent->data > key) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }
    return;

}


// 삽입 알고리즘 2 : 재귀 사용
// 왜 반환형이 존재하는지 이해해볼 것
TreeNode* insertKey_2(TreeNode* root, int key){
    
    // 없으면? 만든다.
    if(root == NULL){
        TreeNode* newNode = makeNode(key);
        root = newNode;
        return root;
    }
    // 현재 node의 key 값보다 삽입하고자 하는 key 값이 더 작을 경우
    if(root->data > key){
        root->left = insertKey_2(root->left, key);  // 왼쪽에 삽입하도록 재귀 호출
        return root;
    } else if(root->data < key){
        root->right = insertKey_2(root->right, key); // 아니면 오른쪽에 삽입하도록 재귀 호출
        return root;
    } else 
    // 중복값 삽입을 방지하기 위함
    {
        printf("이미 존재하는 값\n");
        return root; 
    }
}


// 재귀를 위해서 반환형이 TreeNode* 이여야 함
TreeNode* deleteKey(TreeNode* current, int key){
    if(current == NULL) {
        return current;
    }
    if(current->data > key) {
        current->left = deleteKey(current->left, key);
    } else if(current->data < key) {
        current->right = deleteKey(current->right, key);
    } 
    // 같은 값일 경우 이 곳으로 분기됨
    // 1개 만 NULL 일 경우
    else{
        if(current->left == NULL) {
            TreeNode* temp = current->right;
            free(current); 
            return temp;
        } else if(current->right == NULL) {
            TreeNode* temp = current->left;
            free(current);
            return temp;
        }
        
        TreeNode* temp = current->right; 
        while(temp->left != NULL) {
            temp = temp->left;
        }
        current->data = temp->data;
        current->right = deleteKey(current->right, temp->data);
    }
    return current;
}

/* 교수님이 내주신 코드와 최대한 유사함
 이중 포인터를 쓴 이유는 지역 변수로 선언된 포인터 변수에 대하여, 이 변수를 통해서만 수정한 것이 원본에도 전달되도록 한 것
 위의 경우 직접 매개변수로 받은 포인터에 대해 값을 수정하여 재할당 하였기에 변경사항이 전달됨
 근데 이게 맞나? 
 
 이중포인터를 제거해도 잘만 작동한다.
 insert_1와 다른게 뭔데?
 */
void deleteKey_2(TreeNode* B, int x) {
    TreeNode* p = B;
    TreeNode* parent = NULL;

    // 부모 노드 찾기
    while (p != NULL && p->data != x) {
        parent = p;
        if (x < p->data) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    if (p == NULL) {
        return;
    }

    // 양쪽다 null -> leaf 노드이므로 그냥 삭제
    if (p->left == NULL && p->right == NULL) {
        if (parent == NULL) { 
            B = NULL;
        } else if (parent->left == p) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(p);
    }
    // 한쪽만 null -> 자식이 하나뿐이므로, 지금의 parent와 연결시키면 됨
    else if (p->left == NULL || p->right == NULL) {
        TreeNode* child = (p->left != NULL) ? p->left : p->right;
        
        if (parent == NULL) { 
            B = child;
        } else if (parent->left == p) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(p);
    }
    // 양쪽다 존재할 경우, 오른쪽 서브트리에서 가장 큰 값(혹은 왼쪽 서브트리에서 가장 작은 값)을 현재의 노드에 대체한 뒤,
    // 재귀를 통해 그 값을 제거하도록 이동함.
    else {
        TreeNode* temp = p->right; 
        while(temp->left != NULL) {
            temp = temp->left;
        }
        p->data = temp->data;
        deleteKey_2(p->left, temp->data);
    }

    return;
}

void del(TreeNode* A, int key){
    TreeNode* B = A;
    B->left->left->data = key;
}

void printNode(TreeNode* node){
    if(node != NULL){
        printNode(node->left);
        printf("%d  ", node->data);
        printNode(node->right);
    }
}

void InfixOrder(TreeNode* node, int a[], int* index){
    if(node != NULL){
        InfixOrder(node->left, a, index);
        a[*index] = node->data;
        (*index)++;
        InfixOrder(node->right, a, index);
    }
}

int main(){
    TreeNode* root = NULL;
    int a[] = {50,17,66,19,5,60,92,80,1,13};

    for(int i=0; i< sizeof(a)/sizeof(int); i++){
        //root = insertKey_2(root,a[i]);
        insertKey_1(&root,a[i]);
    }
    
    int b[10]={};
    printNode(root);
    printf("\n");

    int index = 0;
    InfixOrder(root, b, &index);
    for(int i=0; i< 10; i++){
        printf("%d  ", b[i]);
    }
    printf("\n");

    // 지역 변수로 50의 key 값을 가진 노드를 임시 포인터로 반환 받고
    // 그 노드의 왼쪽 자식인 17을, root를 인자로 보내 "포인터를 매개변수로 받는" 함수에 대해 삭제하도록 하였더니
    // 삭제가 반영되어 17이 아닌 19가 대체된 것이 임시포인터로도 확인이 가능했다.
    TreeNode* temp = find(root, 50);
    deleteKey_2(root, 17);
    printf("%d\n", temp->left->data);
}
