#include<iostream>
using namespace std;
typedef struct TreeNode *HuffmanTree;
struct TreeNode{
    int weight;
    HaffmanTree left,right;
};

HuffmanTree Huffman(MidHeap H)
{
    int i;
    HuffmanTree T;
    BuildMinHeap(H);
    for(int i=1;i < H->Size; i++)
    {
        T = malloc(sizeof(struct TreeNode));
        T->left = DelteMin(H);
        T->right = DeleteMin(H);
        T->weight = T->left->weight + T->right->weight ;
        Insert(H,T);
    }
    T = DelteMin(H);
    return T;
}