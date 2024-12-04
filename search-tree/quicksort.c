#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int list[], int left, int right){

    int pivot = list[left]; // pivot
    int n = left; // 왼쪽 시작
    int k = right+1; // 오른쪽 시작
    
    if(left<right){
        do{
            do
            {
                n++;
            } while (list[n] < pivot);
            
            do
            {
                k--;
            } while (list[k] > pivot);
            if(n < k)
                swap(&list[n], &list[k]);

        }while( n < k );

        swap(&list[left], &list[k]);
        quickSort(list, left, k-1);
        quickSort(list, k+1, right);  
    }

    
}


int main(){

    int list[] = {5,4,3,8,4,1};
    
    quickSort(list,0,5);
    for(int i=0; i<6;i++){
        printf("%d  ", list[i]);
    }
    return 0;
}
