#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define MaxSize 5
#define ElemType int
typedef struct
{
    ElemType data[MaxSize];
    int length;
}SqList;
void CreateList(SqList*& L, ElemType a[], int n)  //由a中的n个元素建立顺序表
{
    int i = 0, k = 0;
    L = (SqList*)malloc(sizeof(SqList));
    while (i < n)
    {
        L->data[k] = a[i];
        k++;
        i++;
    }
    L->length = k;
    cout << "顺序表总长度为：" << L->length << endl;
}
SqList* creat_sqlist(void)
{
    SqList* list = NULL;//初始化为空
    list = (SqList*)malloc(sizeof(SqList));
    return list;
}
void partitonl(SqList* L)
{
    int i = 0, j = L->length;
    for (int n = 0; n <= j; n++)
    {
        ElemType pivot = L->data[n];
        for (int d = 0; d <= j; d++)
        {
            if (pivot <= L->data[d])
            {
                i++;
            }
        }

        if (i == 3)
        {
            cout << pivot << "是第三大的元素" << endl;
        }
        i = 0;
    }
}
int main()
{
    int arrs[5] = { 6,5,1,8,2, };
    SqList* s1 = creat_sqlist();
    CreateList(s1, arrs, 5);
    partitonl(s1);
}