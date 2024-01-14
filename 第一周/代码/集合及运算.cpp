#include<iostream>
using namespace std;

typedef struct{
    ElementType Data;
    int Parent;
}SetType;

int Find(SetType s[],ElementType X)
{
    int i;
    for(i=0; i<MaxSize&& s[i].Data != X;i++)
    {
        if(i >= MaxSize)  return -1;
    }
    for(; s[i].Parent >= 0;i = s[i].Parent);
    return i;
}

void Union(SetType s[],ElementType x1,ElementType x2)
{
    int Root1,Root2;
    Root1 = Find(s , x1);
    Root2 = Find(s , x2);
    if(Root1 != Root2)
        s[Root2].Parent = Root1;
}