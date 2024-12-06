#ifndef __HEAP__
#define __HEAP__

#include <stdio.h>
#include <stdlib.h>

#define Buf_Size 20

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Heap {
    int N;
    TreeNode** nodeArray;
} Heap;



#endif
