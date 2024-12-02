#include <stdio.h>
#include <stdlib.h>

/*
전체적인 함수 설명 - postfix order 생각 하면 편함

일단 반으로 계속 나눔 -> 더이상 나눌 수 없을 때까지 == 원소가 하나 뿐일 때까지
원소 하나인지의 판정은 left 인덱스와 right 인덱스의 대소 관계로 구분

leaf node - 즉, 원소가 하나 남을 때까지 나누고나면 internal node 출력 - 즉, 두 child node를 합병함
---

함수

merge : 분할
merge_sort : (분할된 것을 합병) 정렬된 두 배열을 정렬된 형태로 합병하는 함수
---

변수

int list[] : 정렬하고자 하는 원본 배열
left : 분할-정렬하고자 하는 부분의 시작 인덱스
right : 분할-정렬하고자 하는 부분의 끝 인덱스

void merge_sort(list[] , left, right) {

    // left와 right가 같아질 때까지 재귀 호출 - 하기 위한 조건문
    if ( left가 right보다 작으면 재귀 호출 ) {
    
        int mid = left와 right 사이 (소수점 버림)

        // mid를 중심으로 왼쪽과 오른쪽으로 나누어 재귀 호출

        merge_sort(list[], left, mid)       // 왼쪽
        merge_sort(list[], mid+1, right)    // 오른쪽

        merge(list[], left, mid, right) // merge_sort 재귀가 끝나면 합병 시작
    }
}


void merge(list[], left, mid, right) {

    // 정렬된 두 배열의 원소를 비교하여 차례로 sort 배열에 추가
    // 이렇게 추가하다가 한쪽이 빌 경우, 나머지는 이미 정렬된 내용이므로 그대로 추가

    i = left  // left 배열 시작
    j = mid+1 // right 배열 시작
        
    k = left // sort 배열의 정렬되지 않은 부분의 시작 인덱스

    while( 한쪽 배열이 끝에 다다를 때까지 ) { 

        
        if( 오름차순 : list[i]가 list[j] 이상인가? , 내림차순 : list[i]가 list[j] 이하인가?) {

            sort[k] = list[i]
            k++
            i++
        } 
        else 
        {  
            sort[k] = list[j]
            k++
            j++
        }
    }

    // left 배열의 empty 정보는 left 배열의 시작인덱스인 i가 left의 끝 인덱스인 mid보다 큰지를 확인
    =>  " i > mid "

    // 만약 더 크다면, 그것은 위의 반복문에서 left 배열이 empty가 되어 탈출하게 된 것임
    if( left 배열이 empty인 경우 ){
        right 배열을 그대로 sort에 추가
        for(int n = j; n <= right; k++, n++) {
            sort[k] = list[n]
        }

    }
    else
    if( right 배열이 empty인 경우 ){
        left 배열을 그대로 sort에 추가
        for(int n = i; n <= mid; k++, n++) {
            sort[k] = list[n]
        }
    }

    // 위 과정을 거쳐 두 배열을 완전히 합병하였을 경우 
    // 원본 배열 list에 정렬된 배열 sort를 적용시킴

    for(int n = left; n <= right; n++){
        list[n] = sort[n];
    }

}

*/

#define MAX_SIZE 10
//int temp[MAX_SIZE];

void merge(int list[], int left, int mid, int right){

    int temp[MAX_SIZE];
    int l = left;
    int r = mid+1;
    int s = left;

    while(l <= mid && r <= right){

        if(list[l] >= list[r]){
            temp[s] = list[l];
            s++;
            l++;
        } else {
            temp[s] = list[r];
            s++;
            r++;
        }
    }

    if(l > mid){
        for(int i=r; i<=right; s++, i++){
            temp[s] = list[i];
        }
    } else {
        for(int i=l; i<=mid; s++, i++){
            temp[s] = list[i];
        }
    }

    for(int i=left; i<=right; i++){
        list[i] = temp[i];
    }
}

void merge_sort(int list[] ,int left, int right) {

    if ( left < right ) {
    
        int mid = (left + right)/2;

        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);

        merge(list, left, mid, right);
    }
}

int main(){

    int i;
    int n = MAX_SIZE;
    int list[MAX_SIZE] = {21, 10, 12, 20, 13, 15, 22, 44, 13, 4};

    merge_sort(list, 0, n-1);

    for(i=0; i<n; i++){
        printf("%d\n", list[i]);
    }

}