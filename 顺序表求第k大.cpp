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
void CreateList(SqList*& L, ElemType a[], int n)  //��a�е�n��Ԫ�ؽ���˳���
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
    cout << "˳����ܳ���Ϊ��" << L->length << endl;
}
SqList* creat_sqlist(void)
{
    SqList* list = NULL;//��ʼ��Ϊ��
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
            cout << pivot << "�ǵ������Ԫ��" << endl;
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