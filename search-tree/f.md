
다음의 코드에서 문제가 발생했었습니다.

1. 동적 배열의 크기를 넘어설 경우 realloc으로 확장하는 것을 구현
```
int M_Size = 10;

void extend_heap(int* heap){
  M_Size *= 2;
  int* new_heap = (int*)realloc(heap, (M_Size+1)*sizeof(int));
  return new_heap;
}

void insertHeap(int* heap, int key){
  if(heap[0]+1 > M_Size){
      heap = extend_heap(heap);
      if(heap==NULL){
          printf("failed\n");
          return;
      }
  }
  heap[0]++;
  ....
}
int main(){
  int list[] = {...} // 대강 20개가 넘는 배열
  int* heap = calloc(M_Size+1,sizeof(int));
  while(){
    insertHeap(heap, list[i];
    ...
}
```
이 코드는 배열의 값을 동적 할당한 heap 배열에 추가하는 코드입니다.
이때, 코드의 heap의 동적 할당한 크기보다 더 커져서 extend_heap() 함수가 호출되고, 그렇게 realloc이 일어났을 때,
insertHeap() 함수가 종료되고 heap에 저장된 배열은 아무것도 없는 배열입니다.

즉, 참조에 의한 호출이 일어난 것으로 예상하고 하였는데, 호출한 함수 내에서 변경한 것들이 main에선 아무것도 반영되지 않았습니다.

대체 왜그런 건지 모르겠습니다..

+ 추가적으로 insertHeap에서 return한 값을 쓰도록 하였더니 문제가 해결되엇습니다.
+ 이중 포인터로 파라미터를 설정하여 main으로부터 
+ 참조로 전달이 된다고 생각하였던게, 그것은 통하지 않고 직접 return을 해야 함수내에서 수정한 값이 그대로 반영이 되더군요
+ 왜 그런건지 궁금합니다

+ 왜냐하면, isnertHeap내에서 heap 내에 있는 데이터를 옮기는건 가능했는데, 동적할당은 안된다는 것이 이해가 안가서..



2. 이것도 비슷한 경우인데, 하나는 성공하고 하나는 실패한 경우입니다.

다음은 이진 트리 탐색의 코드중 일부입니다.
```
TreeNode* makeNode(int key) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insertKey_1(TreeNode** root, int key){

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

    if(*root == NULL){
        *root = temp;
    }
    else if(parent->data > key) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }
    return;
}

TreeNode* insertKey_2(TreeNode* root, int key){
    if(root == NULL){
        TreeNode* newNode = makeNode(key);
        root = newNode;
        return root;
    }
    if(root->data > key){
        root->left = insertKey_2(root->left, key);  
        return root;
    } else if(root->data < key){
        root->right = insertKey_2(root->right, key); 
        return root;
    } else 
    {
        printf("이미 존재하는 값\n");
        return root; 
    }
}

void deleteKey_2(TreeNode* B, int x) {
    TreeNode* p = B;
    TreeNode* parent = NULL;

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

int main(){
    TreeNode* root = NULL;
    int a[] = {50,17,66,19,5,60,92,80,1,13};

    for(int i=0; i< sizeof(a)/sizeof(int); i++){
        //root = insertKey_2(root,a[i]);
        //insertKey_1(&root,a[i]);
    }
    ...

```
처음 insertKey_1 함수는 이중포인터가 아니라 그냥 구조체 포인터 였습니다.
당연히 insertKey_1은 파라미터로 보내진 main의 구조체 포인터를 지역변수 temp에 할당하여 동일한 메모리를 가리키게 하였으니,
insertKey_1에서 temp를 이용한 변경사항은 그대로 main이 가리키는 메모리상의 트리와 동일하게 적용될 것으로 생각하였습니다. (같은 메모리를 가리키니 같은 트리를 공유한다고 생각)

그런데 전혀 반영이 안되고 오류가 발생하길래 이중 포인터로 하여 주소를 전달하게 하였더니 되더군요

포인터를 사용하면 자연스럽게 참조되어 반영될 줄 알았는데 안되는 이유가 무엇인지 궁금합니다.

반대로 deleteKey_2에서는 반환형도, 이중포인터도 없는데도 함수내부에서의 수정사항이 그대로 공유가 되었습니다.
이건 또 무슨 차이인지 궁급합니다..
