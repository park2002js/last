#include "Heap.h"

Heap* makeHeap(){
    Heap* heap = malloc(sizeof(Heap));
    heap->N = 0;
    // buf_size 만큼의 TreeNode 포인터 원소를 가질 수 있는 배열 생성
    // calloc으로 동적할당 했기 때문에 nodeArray에 들어있는 값은 모두 NULL ('포인터'를 원소로 하는 배열이기에)
    heap->nodeArray = (TreeNode**)calloc(Buf_Size,sizeof(TreeNode*));
    return heap;
}

TreeNode* makeNode(int key) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 교환 전문 함수, parent와 child를 교환함
void interChange(Heap* h, int parent, int child){
    TreeNode* temp = h->nodeArray[parent];
    h->nodeArray[parent] = h->nodeArray[child];
    h->nodeArray[child] = temp;
}


void insertHeap(Heap* h, int child){
    int parent;
    if(child%2==1){
        parent = (child-1)/2;
    } else {
        parent = child/2;
    }

    // root 노드에 도달하면 더이상 교환할 필요 없음
    // max heap이면 parent >= child 여야 하므로 재귀의 조건(교환을 계속하는 조건)은 parent < child
    // min heap은 그 반대
    if(child != 1 && h->nodeArray[parent]->data < h->nodeArray[child]->data){
        // 교환
        //printf("exchange!! : child - %d  parent - %d\n", h->nodeArray[child]->data, h->nodeArray[parent]->data);
        interChange(h, parent, child);

        // 교환한 위치에서도 더 교환해야 하는지 판단하기 위한 재귀
        insertHeap(h, parent);
    }
}


// 계속 insertHeap을 호출해서 삽입
void makeHeapTree(Heap* heap, int* data, int size){
    // data의 key들을 차례대로 꺼냄
    // Heap의 배열의 마지막 원소에 추가, 이후 부모 노드와 비교를 재귀적으로 수행
    // 모든 data에 대해서 수행

    for(int i = 0; i < size; i++){
        int key = data[i];
        TreeNode* newNode = makeNode(key);
        heap->N++;
        heap->nodeArray[heap->N] = newNode;

        insertHeap(heap, heap->N);
    }
}

// max heap을 기준으로 삭제 ()는 minheap일때의 수정사항
void deleteHeap(Heap* heap, int index){
//printf("p_key = %d, p_index = %d, L_____L_child_value : %d, child_index : %d\n", p_key, p, left->data, left_index);
    // 현재 노드에 들었는 것이 없을 경우 종료
    if(heap->N == 0){
        return;
    }

    // 입력받은 인덱스에 존재하는 원소를 맨 끝과 교환
    int p = index;
    printf("%d  ", heap->nodeArray[p]->data);
    heap->nodeArray[p] = heap->nodeArray[heap->N];
    heap->nodeArray[heap->N] = NULL;
    heap->N = (heap->N)-1;

    // p의 값 = 현재 노드 인덱스
    // 현재의 위치를 인덱스로 판정하여 확인
    // 자식이 존재한다면, 노드의 수 N 보다 무조건 작아야함
    int left_index = p*2;
    int right_index = p*2+1;

    // 오른쪽 자식을 기준으로 할 경우 왼쪽 자식이 있는 경우가 아예 무시되버림
    while(left_index <= heap->N){

        int p_key = heap->nodeArray[p]->data;
        TreeNode* left = heap->nodeArray[left_index];
        TreeNode* right = heap->nodeArray[right_index];

        // 조건문의 조건을 통과함 => 왼쪽 자식은 존재함
        // 오른쪽 자식의 인덱스가 노드의 수보다 많다는 것은
        // 무조건 왼쪽 자식만 존재한다는 이야기이므로 자식노드와 바꾼뒤 바꾸고 노드 체인지 종료
        if(right_index > heap->N) {
            // 단, 자식 노드의 크기가 자신보다 클 경우에만
            if(p_key < heap->nodeArray[left_index]->data){
                interChange(heap, p, left_index);
            }
            return;
        }
        

        // 이곳으로 왔다는 것은 오른쪽 자식과 왼쪽 자식 모두 유효하다는 이야기
        // 따라서 둘의 키 값에 대한 크기비교가 필요
        // 0. 자식노드가 자신보다 클(작을) 경우 교환을 위한 비교를 시작
        if(p_key < left->data || p_key < right->data){

            // 1. 왼쪽 자식의 키값이 더 크거나(작은) 같은 경우
            if(left->data >= right->data){
                interChange(heap, p, left_index);
                p = left_index;
            } else 
            // 2. 오른쪽 자식이 더 큰(작은) 경우
            {
                interChange(heap, p, right_index);
                p = right_index;
            }
        } else {
            // 자신보다 더 큰 자식노드가 존재하지 않을 경우 교환을 종료함
            return; 
        }
        // 갱신
        left_index = p*2;
        right_index = p*2+1;
    }
    
    return;
}

// 배열에 저장된 모든 원소 삭제 + 정렬된 결과 출력
void printSorting(Heap* heap){
    while(heap->N > 1) {
        // root node만 계속 삭제하면 정렬된 결과 출력
        deleteHeap(heap, 1);
    }
}

void printHeap(const Heap* heap){

    for(int i=1; heap->nodeArray[i] != NULL; i++){
        printf("%d의 key값 : %d\n", i, heap->nodeArray[i]->data);
    }
}




int main() {
    Heap* heap = makeHeap();
    int tempData[] = {5,4,6,2,4,1,6,7,5,3,2,8,7,6,7};

    makeHeapTree(heap, tempData, sizeof(tempData)/sizeof(int));
    printHeap(heap);

    printf("정렬해서 출력 : ");
    printSorting(heap);

    //printHeap(heap);
}
