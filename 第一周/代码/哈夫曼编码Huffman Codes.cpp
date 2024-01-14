#include<iostream>
#include<cstring>
using namespace std;
#define MaxSize 65
#define ElementType HuffmanTree
#define ERROR NULL
#define INFINITY 1000

typedef struct HTNode *HuffmanTree;
struct HTNode{
    int weight;
    HuffmanTree left,Right;
};

typedef struct HNode *MinHeap;
struct HNode {
    ElementType *Data;
    int size;
    int Capacity;
};

HuffmanTree mini;

MinHeap CreateHeap(void)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType*)malloc((MaxSize +1) * sizeof(ElementType));
    H->size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = mini;
    return H;
}

bool IsHeapFull(MinHeap H)
{
    return (H->size == H->Capacity);
}

bool IsHeapEmpty(MinHeap H){
     return (H->size == 0);
}
void InsertMinHeap(MinHeap H, ElementType item)
{
    int i;
    if(IsHeapFull(H)){
        cout<<"FULL"<<endl;
        return;
    }
    i = ++H->size;

    for(; H->Data[i/2]->weight > item->weight;i /=2)
        H->Data[i] = H->Data[i/2];

    H->Data[i] = item;
}

ElementType DeleteMin(MinHeap H)
{
    int parent,child;
    ElementType MinItem,temp;
    if(IsHeapEmpty(H)){
        cout<<"Empty"<<endl;
        return ERROR;
    }

    MinItem = H->Data[1];
    temp = H->Data[H->size];
    H->size--;

    for(parent=1;parent*2 <= H->size; parent = child)
    {
        child = parent *2;

        if((child != H->size) && (H->Data[child]->weight > H->Data[child +1]->weight))
            child++;
        if(temp->weight <= H->Data[child]->weight) break;
        else  H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = temp;
    return MinItem;

}

void PerDown(MinHeap H , int p)
{
    int parent , child;
    ElementType X;

    X = H->Data[p];
    for(parent = p;parent*2 <= H->size ; parent = child)
    {
        child = parent *2;
        if((child != H->size) && (H->Data[child]->weight > H->Data[child +1]->weight)) child++;
        if(X->weight <= H->Data[child]->weight) break;
        else H->Data[parent] = H->Data[child];

    }
    H->Data[parent] = X;
}

void BuildMinHeap(MinHeap H)
{
    int i;
    for(i= H->size/2;i>0;i--)   PerDown(H,i);

}

HuffmanTree CreateHuffman()
{
    HuffmanTree HFT;
    HFT = (HuffmanTree)malloc(sizeof(struct HTNode));
    HFT->left = NULL;
    HFT->Right = NULL;
    return HFT;
}

HuffmanTree Huffman(MinHeap H)
{
    int i, N;
    HuffmanTree T;
    BuildMinHeap(H);
    N = H->size;
    for(i=1; i < N; i++)
    {
        T = (HuffmanTree)malloc(sizeof(struct HTNode));

        T->left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T ->weight = T->left->weight + T->Right->weight;
        InsertMinHeap(H,T);
    }
    T = DeleteMin(H);
    return T;
}


int WPL(HuffmanTree H, int depth)
{
    if(!H->left && !H->Right) return (depth * H->weight);
    else  return (WPL(H->left,depth+1)+ WPL(H->Right,depth +1));
}

int Min(int a, int b){
    return a<b ? a:b;
}

bool IsPrefix(char code[][MaxSize], int N)
{
    int length;
    for(int i = 1;i<N;i++)
    {
        for(int j= i +1; i<=N;j++)
        {
            length = Min(strlen(code[i]),strlen(code[j]));
            if(strncmp(code[i],code[j],length)==0)
                return false;
        }
    }
    return true;
}

bool check(char code[][MaxSize], int f[], int wpl, int N)
{
    int Len =0;
    for(int i=1;i<=N;i++)
    {
        Len += strlen(code[i]) * f[i];
    }
    if(Len != wpl) return false;
    else return IsPrefix(code,N);
}


int main(int argc, char const *argv[])
{
    int N,i,j,f[MaxSize],wpl,M;
    char c[MaxSize];
    char code[MaxSize][MaxSize];
    HuffmanTree HFT;
    mini = CreateHuffman();
    mini->weight = - INFINITY;
    MinHeap H = CreateHeap();
    cin>>N;
    H->size = N;
    for(i =1;i<=N;i++)
    {
        getchar();
        cin>>c[i]>>f[i];
        HFT = (HuffmanTree)malloc(sizeof(struct HTNode));
        HFT->left = NULL;
        HFT->Right = NULL;
        HFT->weight =  f[i];
        H->Data[i] = HFT;
    }

    HFT = Huffman(H);
    wpl = WPL(HFT,0);

    cin>>M;
    for(j=0;j<M;j++)
    {
        for(i=1;i<=N;i++)
        {
            getchar();
            cin>>c[i]>>code[i];
        }
        if(check(code,f,wpl,N))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}