#include <stdio.h>
#include <stdlib.h>

/*
��ü���� �Լ� ���� - postfix order ���� �ϸ� ����

�ϴ� ������ ��� ���� -> ���̻� ���� �� ���� ������ == ���Ұ� �ϳ� ���� ������
���� �ϳ������� ������ left �ε����� right �ε����� ��� ����� ����

leaf node - ��, ���Ұ� �ϳ� ���� ������ �������� internal node ��� - ��, �� child node�� �պ���
---

�Լ�

merge : ����
merge_sort : (���ҵ� ���� �պ�) ���ĵ� �� �迭�� ���ĵ� ���·� �պ��ϴ� �Լ�
---

����

int list[] : �����ϰ��� �ϴ� ���� �迭
left : ����-�����ϰ��� �ϴ� �κ��� ���� �ε���
right : ����-�����ϰ��� �ϴ� �κ��� �� �ε���

void merge_sort(list[] , left, right) {

    // left�� right�� ������ ������ ��� ȣ�� - �ϱ� ���� ���ǹ�
    if ( left�� right���� ������ ��� ȣ�� ) {
    
        int mid = left�� right ���� (�Ҽ��� ����)

        // mid�� �߽����� ���ʰ� ���������� ������ ��� ȣ��

        merge_sort(list[], left, mid)       // ����
        merge_sort(list[], mid+1, right)    // ������

        merge(list[], left, mid, right) // merge_sort ��Ͱ� ������ �պ� ����
    }
}


void merge(list[], left, mid, right) {

    // ���ĵ� �� �迭�� ���Ҹ� ���Ͽ� ���ʷ� sort �迭�� �߰�
    // �̷��� �߰��ϴٰ� ������ �� ���, �������� �̹� ���ĵ� �����̹Ƿ� �״�� �߰�

    i = left  // left �迭 ����
    j = mid+1 // right �迭 ����
        
    k = left // sort �迭�� ���ĵ��� ���� �κ��� ���� �ε���

    while( ���� �迭�� ���� �ٴٸ� ������ ) { 

        
        if( �������� : list[i]�� list[j] �̻��ΰ�? , �������� : list[i]�� list[j] �����ΰ�?) {

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

    // left �迭�� empty ������ left �迭�� �����ε����� i�� left�� �� �ε����� mid���� ū���� Ȯ��
    =>  " i > mid "

    // ���� �� ũ�ٸ�, �װ��� ���� �ݺ������� left �迭�� empty�� �Ǿ� Ż���ϰ� �� ����
    if( left �迭�� empty�� ��� ){
        right �迭�� �״�� sort�� �߰�
        for(int n = j; n <= right; k++, n++) {
            sort[k] = list[n]
        }

    }
    else
    if( right �迭�� empty�� ��� ){
        left �迭�� �״�� sort�� �߰�
        for(int n = i; n <= mid; k++, n++) {
            sort[k] = list[n]
        }
    }

    // �� ������ ���� �� �迭�� ������ �պ��Ͽ��� ��� 
    // ���� �迭 list�� ���ĵ� �迭 sort�� �����Ŵ

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