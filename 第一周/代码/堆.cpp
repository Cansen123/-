#include<iostream>
using namespace std;

typedef struct HNode *MaxHeap;
struct HNode{
    ElementsType *Elements;
    int Size;
    int Capacity;
};

MaxHeap CreatHeap(int Maxsize)
{
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
    H->Elements = malloc((MaxSize +1) *sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxSize;
    return H;
}

void InsertHeap(MaxHeap H,ElementType item)
{
    int i;
    if(IsFull(H)){
        printf("FULL\n");
        return;
    }
    i = ++H->Size;
    for(; H->Elements[i/2] <item;i/=2){
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = item;
}

ElementType DeleteMax(MaxHeap H)
{
    int parent, child;
    ElementType MaxItem,temp;
    if(IsEmpty(H))
    {
        printf("Empty\n");
        return;
    }

    MaxItem = H->Elements[1];
    temp = H->Elements[Size];
    Size--;

    for(parent=1;parent *2<= H->Size; parent = child)
    {
        child = parent *2;
        if((child!=H->Size) && (H->Elements[child]<H->Elements[child+1]))
            child++;
        
        if(temp >= Elements[child]) break;
        else  H->Elements[parent] = H->Elements[child];
    }
    H->Elements[parent] = temp;
    return MaxItem;
}

void BuildHeap(MaxHeap H)
{
    int i;
    for(i = H->Size/2;i>0;i--)
        PercDown(H,i);
}

void PercDown(MaxHeap H , int p)
{
    int parent, child;

    X = H->Data[p];
    for(parent = p;parent * 2 <= H->Size; parent = child)
    {
        child = parent *2;
        if((child != H->Size)&& (H->Data[child]< H->Data[child+1])) child++;
        if(X > H->Data[child]) break;
        else  H->Data[parent] = H->Data[child];
    }
    H->Data[parent] = X;
}