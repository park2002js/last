#include <stdio.h>
#include <stdlib.h>
#define M_Size 10

void insertHeap(int list[], int key){

    int size = list[0];
    int index = size+1;
    int parent;

    list[index] = key;
    list[0] = list[0]+1;

    while (index>=1)
    {
        if(index%2){
            parent = (index-1)/2;
        }else {
            parent = index/2;
        }
        // 변경조건
        // max heap : parent < child  || min heap : parent > child
        if(parent >=1 && list[parent] < list[index]){
            // swap
            int temp = list[parent];
            list[parent] = list[index];
            list[index] = temp;
            index = parent;
        } else {
            return;
        }
    }
    return;    
}

int deleteHeap(int list[]){
    int index = 1;
    int last = list[0];
    int return_value = list[1];

    if(last <= 0){
        printf("Is Empty!\n");
        return -1;
    }

    // 맨 끝 노드와 교환
    int temp = list[last];
    list[last] = list[index];
    list[index] = temp;

    list[last] = 0;
    list[0] = list[0]-1;

    int size = list[0];
    int left = index*2;  // right = left + 1
    while(left <= size){
        
        // right가 존재할 경우, 더 큰(작은) 값을 left 변수가 가리키도록 함
        if(left < size){  // =left+1 =right <= size
            // 변경조건
            // max heap : left < left+1=right  || min heap : left > left+1=right
            if( list[left] < list[left+1]){

                left = left+1; // right와 left 중 더 큰 key 값을 가진 노드의 인덱스로 변경 (default : left)
            }
            
        }

        // 변경조건
        // max heap : index=parent < left=child  || min heap : index > left
        if(list[index] < list[left] ){
            int temp = list[left];
            list[left] = list[index];
            list[index] = temp;

            // renew parent Index and child Index
            index = left;
            left = index*2;

        } else {
            // 변경 못할 시 반복 교환 종료
            break;
        }
    }
    return return_value;
}



int main(){
    int heap[M_Size] ={};
    int list[] = {5, 6, 8, 9, 4, 2,9,1,7,5};

    
    for(int i=0; i < M_Size; i++){
        printf("Insert : ");
        insertHeap(heap, list[i]);
        for(int n = 1; n <= heap[0]; n++){
            printf("%d  ", heap[n]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Sorted : ");
    int temp = 1;
    while(temp>0){
        temp = deleteHeap(heap);
        printf("%d  ", temp);
    }
}
